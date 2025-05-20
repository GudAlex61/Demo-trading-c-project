#pragma once
#include <string>
#include <iostream>
class Position
{
private:
    std::string tokenName;
    int shoulder;
    double margin;
    double entryPrice;
    time_t start;
    bool isLong;
public:
    Position(std::string tokenName, int shoulder, double margin, bool isLong, time_t start, double entryPrice);
    Position();
    ~Position();
    std::string getTokenName();
    int getShoulder();
    double getMargin();
    double getEntryPrice();
    time_t getStart();
    bool getIsLong();
    double calculatePnL(Position& position);
    friend std::ostream& operator<<(std::ostream& os,  const Position& position);

};

Position MakingPosition(std::string tokenName, bool isLong, int shoulder, double margin);

std::string chooseToken();
int chooseShoulder();
double chooseMargin();
bool chooseLong();
