#pragma once
#include <string>
#include <iostream>
class Positon
{
private:
    std::string tokenName;
    int shoulder;
    double margin;
    double entryPrice;
    time_t start;
    bool isLong;
public:
    Positon(std::string tokenName, int shoulder, double margin, bool isLong, time_t start, double entryPrice);
    Positon();
    ~Positon();
    std::string getTokenName();
    int getShoulder();
    double getMargin();
    double getEnrtyPrice();
    time_t getStart();
    bool getIsLong();
    friend std::ostream& operator<<(std::ostream& os,  const Positon& position);

};

Positon MakingPosition();

std::string chooseToken();
int chooseShoulder();
double chooseMargin();
bool chooseLong();
