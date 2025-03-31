#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "MakingAPosition.h"
#include <iomanip>

using json = nlohmann::json;

int WriteCallback(char* contents, int size, int nmemb, std::string* output) {
    int total_size = size * nmemb;
    if (output && contents) {
        output->append(contents, total_size);
    }
    return total_size;
}

double getCryptoPrice(const std::string& cryptoId) {
    CURL* curl;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" +
                         cryptoId + "&vs_currencies=usd";

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Ошибка CURL: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json data = json::parse(readBuffer);
                if (data.contains(cryptoId) && data[cryptoId].contains("usd")) {
                    return data[cryptoId]["usd"];
                } else {
                    std::cerr << "Криптовалюта не найдена" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return 0.0;
}

double estimateLiquidation(Positon& position){
    if (position.getIsLong()){
        if (position.getShoulder() == 1){
            return 0;
        }
        return position.getEnrtyPrice() * (100 - (100 / position.getShoulder())) / 100;
    } else{
        return position.getEnrtyPrice() * (100 + (100 / position.getShoulder())) / 100;
    }
}

bool checkLiquidation(Positon& position){
    auto now = std::chrono::system_clock::now();
    time_t end = std::chrono::system_clock::to_time_t(now);

    CURL* curl;
    std::string readBuffer;

    std::string symbol;
    if (position.getTokenName() == "bitcoin"){
        symbol = "BTCUSDT";
    } else if (position.getTokenName() == "ethereum"){
        symbol = "ETHUSDT";
    } else if (position.getTokenName() == "solana"){
        symbol = "SOLUSDT";
    } else if (position.getTokenName() == "xrp"){
        symbol = "XRPUSDT";
    } else if (position.getTokenName() == "pepe"){
        symbol = "PEPEUSDT";
    }

    char interval = 's';
    if (end-position.getStart() > 960){
        interval = 'm';
    } else if (end-position.getStart() > 60000){
        interval = 'h';
    }

    double extremum = position.getIsLong() ? 100000 : 0;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://www.binance.com/api/v3/klines?symbol=" + symbol + "&interval=1" + interval + "&limit=1000&startTime=" + std::to_string(position.getStart()*1000) + "&endTime=" + std::to_string(end*1000);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Ошибка CURL: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json data = json::parse(readBuffer);
                for(const auto& candle : data) {
                    if (position.getIsLong()){
                        double candleMin = std::stod(candle[3].get<std::string>());
                        if (candleMin < extremum){
                            extremum = candleMin;
                        }
                    } else {
                        double candleMax = std::stod(candle[2].get<std::string>());
                        if (candleMax > extremum){
                            extremum = candleMax;
                        }
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    if (position.getIsLong()){
        if (extremum < estimateLiquidation(position)){
            return true;
        }
    } else{
        if (extremum > estimateLiquidation(position)){
            return true;
        }
    }
    return false;

}

int mainGreg() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    std::string cryptoName;
    std::cout << "Введите название криптовалюты (например, bitcoin): ";
    std::cin >> cryptoName;

    double price = getCryptoPrice(cryptoName);
    if (price > 0.0) {
        std::cout << "Текущая цена " << cryptoName << ": $" << price << std::endl;
    } else {
        std::cout << "Не удалось получить цену" << std::endl;
    }

    curl_global_cleanup();
    return 0;
}
