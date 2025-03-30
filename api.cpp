#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

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

int main() {
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
