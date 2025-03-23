#include <string>
#include <iostream>
class Positon
{
private:
    std::string tokenName;
    int shoulder;
    double margin;
    double entryPrice;
public:
    Positon(std::string tokenName, int shoulder, double margin, double entryPrice);
    Positon();
    ~Positon();
    std::string getTokenName();
    int getShoulder();
    double getMargin();
    double getEnrtyPrice();

};

Positon MakingPosition();

std::string chooseToken();
int chooseShoulder();
double chooseMargin();