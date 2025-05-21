#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include "MakingAPosition.h"
#include "api.h"
Position MakingPosition(std::string tokenName, bool isLong, int shoulder, double margin){
    auto now = std::chrono::system_clock::now();
    time_t start = std::chrono::system_clock::to_time_t(now);
    double price = getCryptoPrice(tokenName);
    if (shoulder == -1 || margin == -1 || price == 0){
        Position newPosition("invalid", 0, 0, 0, 0, 0);
        return newPosition;
    }
    Position newPosition(tokenName, shoulder, margin, isLong, start, price);
    std::cout << "Позиция успешно создана!" << std::endl << std::endl;
    return newPosition;
}

double Position::calculatePnL(){
     double currentPrice = getCryptoPrice(tokenName);
    if (currentPrice <= 0) {
        std::cerr << "Ошибка: не удалось получить цену для " << tokenName << std::endl;
        return 0.0;
    }
    double priceChange;

    if (isLong) {
        priceChange = (currentPrice / entryPrice - 1.0);
    } else {
        priceChange = (1.0 - currentPrice / entryPrice);
    }
    
    return margin * priceChange * shoulder;
}

Position::Position(std::string tokenName, int shoulder, double margin, bool isLong, time_t start, double entryPrice){
    this->tokenName = tokenName;
    this->shoulder = shoulder;
    this->margin = margin;
    this->isLong = isLong;
    this->start = start;
    this->entryPrice = entryPrice;
}

Position::Position(){
    this->tokenName = "default";
    this->shoulder = 0;
    this->margin = 0;
    this->isLong = true;
    this->start = 0;
    this->entryPrice = 0;
}

Position::~Position()
{
}

std::ostream& operator<<(std::ostream& os,  const Position& position){
    std::tm* locale_time = std::localtime(&position.start);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", locale_time);
    std::string isLong;
    if (position.isLong){
        isLong = "Long";
    } else {
        isLong = "Short";
    }
    os << "Время открытия: "<< buffer << " Название монеты: " << position.tokenName << " Цена входа: " << position.entryPrice << "$ " << isLong << " Маржа: " << position.margin << "$ Плечо: " << position.shoulder;
    return os;
}
int Position::getShoulder(){
    return shoulder;
}
std::string Position::getTokenName(){
    return tokenName;
}

double Position::getEntryPrice(){
    return entryPrice;
}

time_t Position::getStart(){
    return start;
}

double Position::getMargin(){
    return margin;
}

bool Position::getIsLong(){
    return isLong;
}
