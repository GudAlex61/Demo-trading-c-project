#include <string>
#include <iostream>
#include "MakinAPosition.h"
Positon MakingPosition(){
    std::string tokenName = chooseToken();
    int shoulder = chooseShoulder();
    double margin = chooseMargin();
    double price=0;
    Positon newPosition(tokenName, shoulder, margin, price);
    return newPosition;
}


Positon::Positon(std::string tokenName, int shoulder, double margin, double entryPrice){
    this->tokenName = tokenName;
    this->shoulder = shoulder;
    this->margin = margin;
    this->entryPrice = entryPrice;
}

Positon::Positon(){
    this->tokenName = "default";
    this->shoulder = 0;
    this->margin = 0;
    this->entryPrice = 0;
}

Positon::~Positon()
{
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

double Positon::getMargin(){
    return margin;
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
        tokenName = "btc";
        return tokenName;
        break;
    case 2:
        tokenName = "etf";
        return tokenName;
        break;
    case 3:
        tokenName = "sol";
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
        std::cout << "Введено неправильное число!";
        tokenName = "Error";
        return tokenName;
        break;
    }
}

int chooseShoulder(){
    std::cout << "Введите кредитное плечо 1-100: ";
    int shoulder;
    std::cin >> shoulder;
    if (shoulder >= 1 && shoulder <= 100){
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
    return 0;
}