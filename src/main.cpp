#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include "MakingAPosition.h"
#include <vector>
#include "api.h"
#include "sqlite3.h"


class AuthManager {
    sqlite3* db;

public:
    AuthManager(const char* db_name) {
        if (sqlite3_open(db_name, &db) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        const char* sql =
            "CREATE TABLE IF NOT EXISTS Users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "email TEXT UNIQUE NOT NULL,"
            "password_hash TEXT NOT NULL,"
            "balance REAL NOT NULL DEFAULT 10000);";

        char* err = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
            std::string error = err;
            sqlite3_free(err);
            throw std::runtime_error(error);
        }

        const char* sql2 =
            "CREATE TABLE IF NOT EXISTS trades ("
            "trade_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER,"
            "tokenName TEXT NOT NULL,"
            "shoulder INTEGER,"
            "margin REAL,"
            "isLong INTEGER,"
            "start INTEGER,"
            "entryPrice REAL);";

        char* err2 = nullptr;
        if (sqlite3_exec(db, sql2, nullptr, nullptr, &err2) != SQLITE_OK) {
            std::string error = err2;
            sqlite3_free(err2);
            throw std::runtime_error(error);
        }
    }

    ~AuthManager() {
        sqlite3_close(db);
    }

    void getTrades(int& UserID, std::vector<Positon>& positions){
        try {
            sqlite3_stmt* stmt;
            const char* sql = "SELECT tokenName, shoulder, margin, isLong, start, entryPrice FROM trades WHERE user_id = ?;";

            if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                std::cout << "DataBase error getting trades" << std::endl;
            } else{
                sqlite3_bind_int(stmt, 1, UserID);

                while (sqlite3_step(stmt) == SQLITE_ROW){
                    positions.emplace_back(
                    reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)), // tokenName
                    sqlite3_column_int(stmt, 1),     // shoulder
                    sqlite3_column_double(stmt, 2),  // margin
                    sqlite3_column_int(stmt, 3),     // isLong
                    sqlite3_column_int64(stmt, 4),   // start
                    sqlite3_column_double(stmt, 5)   // entryPrice
                    );
                }
            }

            sqlite3_finalize(stmt);


        } catch(const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    void saveBalance(int& UserID, double& balance) {
        sqlite3_stmt* stmt = nullptr;
        const char* sql = "UPDATE Users SET balance = ? WHERE id = ?;";

        if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        sqlite3_bind_double(stmt, 1, balance);
        sqlite3_bind_int(stmt, 2, UserID);

        if(sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка обновления баланса: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    void saveTrades(int& UserID, std::vector<Positon>& positions){
        try {
            sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr);

            const char* deleteTradesSQL = "DELETE FROM trades WHERE user_id = ?;";


            sqlite3_stmt* stmt;
            char* errMsg = nullptr;

            if(sqlite3_prepare_v2(db, deleteTradesSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, UserID);
                if(sqlite3_step(stmt) != SQLITE_DONE) {
                    std::cerr << "Ошибка удаления трейдов: " << sqlite3_errmsg(db) << std::endl;
                }
                sqlite3_finalize(stmt);
            }



            for (int i = 0; i < positions.size(); i++){
                Positon pos = positions[i];

                sqlite3_stmt* stmt;
                const char* sql = "INSERT INTO trades (user_id, tokenName, shoulder, margin, isLong, start, entryPrice) VALUES (?, ?, ?, ?, ?, ?, ?);";
                if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                    std::cout << "Error while registering" << std::endl;
                }

                if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                    sqlite3_bind_int(stmt, 1, UserID);
                    sqlite3_bind_text(stmt, 2, pos.getTokenName().c_str(), -1, SQLITE_TRANSIENT);
                    sqlite3_bind_int(stmt, 3, pos.getShoulder());
                    sqlite3_bind_double(stmt, 4, pos.getMargin());
                    sqlite3_bind_int(stmt, 5, pos.getIsLong());
                    sqlite3_bind_int64(stmt, 6, pos.getStart());
                    sqlite3_bind_double(stmt, 7, pos.getEntryPrice());

                    if(sqlite3_step(stmt) != SQLITE_DONE) {
                        std::cerr << "Trade save error: " << sqlite3_errmsg(db) << std::endl;
                    }
                    sqlite3_finalize(stmt);
                }
            }
            sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);

        } catch(const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    int registerUser(std::string email, std::string password, double& balance, int& UserID) {
        try {

            sqlite3_stmt* stmt;

            const char* sql = "INSERT INTO Users (email, password_hash) VALUES (?, ?);";
            if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                std::cout << "Error while registering" << std::endl;
                return 0;
            }

            sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

            if(sqlite3_step(stmt) != SQLITE_DONE) {
                std::string error = sqlite3_errmsg(db);
                sqlite3_finalize(stmt);
                std::cout << "Email exists" << std::endl;
                return 0;
            }

            UserID = sqlite3_last_insert_rowid(db);
            balance = 10000;
            sqlite3_finalize(stmt);
            std::cout << "Registered!" << std::endl;
            return 1;

        } catch(const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    int loginUser(std::string email, std::string password, double& balance, int& UserID) {
        try {
            sqlite3_stmt* stmt;
            const char* sql = "SELECT id, password_hash, balance FROM Users WHERE email = ?;";

            if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                std::cout << "DataBase error" << std::endl;
                return 0;
            }

            sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

            if(sqlite3_step(stmt) != SQLITE_ROW) {
                sqlite3_finalize(stmt);
                std::cout << "Invalid credentials" << std::endl;
                return 0;
            }

            UserID = sqlite3_column_int(stmt, 0);
            balance = sqlite3_column_double(stmt, 2);

            std::string stored_hash(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            sqlite3_finalize(stmt);

            if(password == stored_hash){
                std::cout << "Logged in!" << std::endl;
                return 1;
            } else {
                std::cout << "Invalid credentials" << std::endl;
                return 0;
            }

        } catch(const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
};

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
