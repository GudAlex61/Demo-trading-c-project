#include <iostream>
#include "MakingAPosition.h"
#include <vector>
#include "api.h"

double calculatePnL(Positon& position){
    double currentPrice = getCryptoPrice(position.getTokenName());
    return position.getMargin() * (((currentPrice / position.getEnrtyPrice()) - 1) * position.getShoulder());
}

int main(){
    std::vector<Positon> positions;
    while(true){
        int choice;
        std::cout << "Выберите действие: " << std::endl;
        std::cout << "1. Создать новую позицию" << std::endl;
        std::cout << "2. Вывод существующих позиций" << std::endl;
        std::cout << "3. Закрытие позиции" << std::endl;
        std::cout << "4. Выход из программы" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1: {
            Positon insertPos = MakingPosition();
            if (insertPos.getTokenName() == "invalid"){
                std::cout << "В процессе создания позиции были введены неверные данные, позиция не создана." << std::endl;
            } else{
                positions.push_back(insertPos);
            }
            break;
        }
        case 2:
            for (int i = 0; i < positions.size(); i++){
                Positon position = positions[i];
                if (checkLiquidation(position)){
                    std::cout << "Ликвидированна позиция: ";
                    std::cout << position << "\n";
                    positions.erase(positions.begin()+i);
                }
            }
            std::cout << "\n";
            std::cout << "Действующие позиции: " << std::endl;
            for (Positon& position : positions){
                std::cout << position << "\n";
            }
            std::cout << "\n";
            break;
        case 3:
            for (int i = 0; i < positions.size(); i++){
                Positon position = positions[i];
                if (checkLiquidation(position)){
                    std::cout << "Ликвидированна позиция: ";
                    std::cout << position << "\n";
                    positions.erase(positions.begin()+i);
                }
            }
            std::cout << "\n";
            std::cout << "Введите номер позиции, которую хотите закрыть или 0, чтобы вернуться в меню." << std::endl;
            for (int i = 0; i < positions.size(); i++){
                Positon position = positions[i];
                std::cout << i + 1 << ". " << position << " " << "P&L(" << calculatePnL(position) << "$)\n";
            }
            int index;
            std::cin >> index;
            if (index == 0){
                break;
            } else if (index < 0 || index > positions.size() + 1){
                std::cout << "Было введено некорректное число, возврат в меню.";
                break;
            }
            std::cout << "Позиция была закрыта. P&L(" << calculatePnL(positions[index-1]) << ")\n";
            positions.erase(positions.begin()+index-1);
            break;
        case 4:
            exit(0);
            break;
        default:
            std::cout << "Введено неверное число. " << std::endl;
            break;
        }
    }
    return 0;
}
