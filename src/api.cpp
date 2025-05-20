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
    CURLcode res;
    std::string readBuffer;
    double price = 0.0;

    curl = curl_easy_init();
    if (curl) {
        // Формируем символ для Binance
        std::string symbol = cryptoId;
        std::transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
        symbol += "USDT";

        std::string url = "https://api.binance.com/api/v3/ticker/price?symbol=" + symbol;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // Таймаут 5 секунд

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        } else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            if (http_code != 200) {
                std::cerr << "HTTP Error: " << http_code << std::endl;
                std::cerr << "Response: " << readBuffer << std::endl;
            } else {
                try {
                    json data = json::parse(readBuffer);

                    // Проверяем структуру ответа
                    if (data.is_object() &&
                        data.contains("symbol") &&
                        data.contains("price") &&
                        data["price"].is_string())
                    {
                        price = std::stod(data["price"].get<std::string>());
                    } else {
                        std::cerr << "Invalid JSON structure: " << data.dump(2) << std::endl;
                    }
                } catch (const json::exception& e) {
                    std::cerr << "JSON parse error: " << e.what() << std::endl;
                    std::cerr << "Raw response: " << readBuffer << std::endl;
                }
            }
        }
        curl_easy_cleanup(curl);
    }
    return price;
}

double estimateLiquidation(Position& position){
    if (position.getIsLong()){
        if (position.getShoulder() == 1){
            return 0;
        }
        return position.getEntryPrice() * (100 - (100 / position.getShoulder())) / 100;
    } else{
        return position.getEntryPrice() * (100 + (100 / position.getShoulder())) / 100;
    }
}

bool checkLiquidation(Position& position){
    auto now = std::chrono::system_clock::now();
    time_t end = std::chrono::system_clock::to_time_t(now);

    CURL* curl;
    std::string readBuffer;

    std::string symbol;
    symbol = position.getTokenName()+"USDT";

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
