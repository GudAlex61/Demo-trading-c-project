#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include "MakingAPosition.h"
#include "api.h"
Positon MakingPosition(){
    std::string tokenName = chooseToken();
    bool isLong = chooseLong();
    int shoulder = chooseShoulder();
    double margin = chooseMargin();
    auto now = std::chrono::system_clock::now();
    time_t start = std::chrono::system_clock::to_time_t(now);
    double price = getCryptoPrice(tokenName);
    if (shoulder == -1 || margin == -1 || price == 0){
        Positon newPosition("invalid", 0, 0, 0, 0, 0);
        return newPosition;
    }
    Positon newPosition(tokenName, shoulder, margin, isLong, start, price);
    std::cout << "Позиция успешно создана!" << std::endl << std::endl; 
    return newPosition;
}

Positon::Positon(std::string tokenName, int shoulder, double margin, bool isLong, time_t start, double entryPrice){
    this->tokenName = tokenName;
    this->shoulder = shoulder;
    this->margin = margin;
    this->isLong = isLong;
    this->start = start;
    this->entryPrice = entryPrice;
}

Positon::Positon(){
    this->tokenName = "default";
    this->shoulder = 0;
    this->margin = 0;
    this->isLong = true;
    this->start = 0;
    this->entryPrice = 0;
}

Positon::~Positon()
{
}

std::ostream& operator<<(std::ostream& os,  const Positon& position){
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
int Positon::getShoulder(){
    return shoulder;
}
std::string Positon::getTokenName(){
    return tokenName;
}

double Positon::getEnrtyPrice(){
    return entryPrice;
}

time_t Positon::getStart(){
    return start;
}

double Positon::getMargin(){
    return margin;
}

bool Positon::getIsLong(){
    return isLong;
}

std::string chooseToken(){
    std::cout << "Выберите токен:" << std::endl;
    std::cout << "1. BTC" << std::endl;
    std::cout << "2. ETF" << std::endl;
    std::cout << "3. SOL" << std::endl;
    std::cout << "4. XRP" << std::endl;
    std::cout << "5. PEPE" << std::endl;

    int token;
    std::string tokenName;
    std::cin >> token;
    switch (token)
    {
    case 1:
        tokenName = "bitcoin";
        return tokenName;
        break;
    case 2:
        tokenName = "ethereum";
        return tokenName;
        break;
    case 3:
        tokenName = "solana";
        return tokenName;
        break;
    case 4:
        tokenName = "xrp";
        return tokenName;
        break;
    case 5:
        tokenName = "pepe";
        return tokenName;
        break;
    default:
        std::cout << "Введено неправильное число! \n\n";
        tokenName = chooseToken();
        return tokenName;
        break;
    }
}

int chooseShoulder(){
    std::cout << "Введите кредитное плечо 1-100: ";
    int shoulder;
    std::cin >> shoulder;
    if (shoulder >= 1 && shoulder <= 1000){
        return shoulder;
    }
    return -1;
}

double chooseMargin(){
    std::cout << "Введите маржу позиции (не больше чем кол-во денег на вашем аккаунте): ";
    double margin;
    std::cin >> margin;
    if (margin >= 1 && margin <= 1000000){
        return margin;
    }
    return -1;
}

bool chooseLong(){
    std::cout << "Long или short?(1/0)" << std::endl;
    int isLong;
    std::cin >> isLong;
    if (isLong == 0){
        return false;
    }
    else{
        return true;
    }
}
