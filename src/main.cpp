#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include "MakingAPosition.h"
#include <vector>
#include "api.h"
#include "sqlite3.h"
#include "sql.h"

double calculatePnL(Positon& position) {

    double currentPrice = getCryptoPrice(position.getTokenName());
    if (currentPrice <= 0) {
        std::cerr << "Ошибка: не удалось получить цену для " << position.getTokenName() << std::endl;
        return 0.0;
    }
    double priceChange;

    if (position.getIsLong()) {
        priceChange = (currentPrice / position.getEntryPrice() - 1.0);
    } else {
        priceChange = (1.0 - currentPrice / position.getEntryPrice());
    }

    return position.getMargin() * priceChange * position.getShoulder();
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QMainWindow window;
    QPushButton button("Click me", &window);

    window.setGeometry(100, 100, 300, 200);
    button.setGeometry(50, 50, 100, 30);
    QObject::connect(&button, &QPushButton::clicked, []() {
        qDebug() << "Button clicked!";
    });

    window.show();
    return app.exec();
    
    AuthManager Users("UsersDB");

    int UserID;
    double balance;


    while (true){
        int choice;
        std::cout << "Выберите действие: " << std::endl;
        std::cout << "1. Зарегистрироваться" << std::endl;
        std::cout << "2. Авторизоваться" << std::endl;
        std::cin >> choice;

        std::string email;
        std::cout << "Введите почту: ";
        std::cin >> email;

        std::string password;
        std::cout << "Введите пароль: ";
        std::cin >> password;
        int result;
        if (choice == 2){
            result = Users.loginUser(email, password, balance, UserID);
        }
        else {
            result = Users.registerUser(email, password, balance, UserID);
        }
        if (result){
            break;
        }
    }

    std::cout << std::endl << "Ваш баланс: " << balance << std::endl;


    std::vector<Positon> positions;

    Users.getTrades(UserID, positions);

    while(true){
        int choice;
        std::cout << "Выберите действие: " << std::endl;
        std::cout << "1. Создать новую позицию" << std::endl;
        std::cout << "2. Вывод существующих позиций" << std::endl;
        std::cout << "3. Закрытие позиции" << std::endl;
        std::cout << "4. Вывести баланс" << std::endl;
        std::cout << "5. Выход из программы" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1: {
            Positon insertPos = MakingPosition();
            if (insertPos.getTokenName() == "invalid" || insertPos.getMargin() > balance){
                std::cout << "В процессе создания позиции были введены неверные данные, позиция не создана." << std::endl;
            } else{
                balance -= insertPos.getMargin();
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
            double PnL;
            PnL = calculatePnL(positions[index-1]);
            balance += PnL+positions[index-1].getMargin();
            std::cout << "Позиция была закрыта. P&L(" << PnL << ")\n";
            positions.erase(positions.begin()+index-1);
            break;
        case 4:
            std::cout << "Текущий баланс: " << balance << std::endl;
            break;
        case 5:
            Users.saveTrades(UserID, positions);
            Users.saveBalance(UserID, balance);
            exit(0);
            break;
        default:
            std::cout << "Введено неверное число. " << std::endl;
            break;
        }
    }
    return 0;
}
