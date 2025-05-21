#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "MakingAPosition.h"
#include <iomanip>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t total_size = size * nmemb;
    buffer->append((char*)contents, total_size);
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

double estimateLiquidation(Position& position) {
    double leverage = static_cast<double>(position.getShoulder());
    if (leverage < 1.0) {
        std::cerr << "Некорректное значение плеча: " << leverage << std::endl;
        return 0.0;
    }
    
    if (position.getIsLong()) {
        return position.getEntryPrice() * (1.0 - 1.0 / leverage);
    } else {
        return position.getEntryPrice() * (1.0 + 1.0 / leverage);
    }
}

bool checkLiquidation(Position& position) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    bool result = false;

    if (!curl) {
        std::cerr << "Ошибка инициализации CURL" << std::endl;
        return false;
    }

    try {
        // Формирование параметров запроса
        auto now = std::chrono::system_clock::now();
        time_t end = std::chrono::system_clock::to_time_t(now);
        
        std::string symbol = position.getTokenName() + "USDT";
        std::string interval = "1m";
        std::string url = "https://api.binance.com/api/v3/klines?symbol=" + symbol +
                        "&interval=" + interval +
                        "&startTime=" + std::to_string(static_cast<uint64_t>(position.getStart()) * 1000) +
                        "&endTime=" + std::to_string(static_cast<uint64_t>(end) * 1000);

        // Настройка CURL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        // Выполнение запроса
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw std::runtime_error("CURL error: " + std::string(curl_easy_strerror(res)));
        }

        // Парсинг JSON
        json data = json::parse(readBuffer);
        
        // Валидация структуры ответа
        if (!data.is_array()) {
            throw std::runtime_error("Invalid response format. Expected array.");
        }

        double extremum = position.getIsLong() 
            ? std::numeric_limits<double>::max()
            : std::numeric_limits<double>::lowest();

        // Обработка свечей
        for (const auto& candle : data) {
            if (!candle.is_array() || candle.size() < 12) {
                std::cerr << "Invalid candle format: " << candle.dump() << std::endl;
                continue;
            }

            try {
                if (position.getIsLong()) {
                    double low = std::stod(candle[3].get<std::string>());
                    extremum = std::min(extremum, low);
                } else {
                    double high = std::stod(candle[2].get<std::string>());
                    extremum = std::max(extremum, high);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing candle: " << e.what() << std::endl;
            }
        }

        // Проверка ликвидации
        double liquidationPrice = estimateLiquidation(position);
        result = position.getIsLong() 
            ? (extremum <= liquidationPrice)
            : (extremum >= liquidationPrice);

    } catch (const json::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
        std::cerr << "Response data: " << readBuffer << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    curl_easy_cleanup(curl);
    return result;
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
