#ifndef SQL_H
#define SQL_H

#include "sqlite3.h"
#include "MakingAPosition.h"
#include <vector>
#include <string>
#include <stdexcept>

class AuthManager {
    sqlite3* db;

public:
    AuthManager(const char* db_name);
    ~AuthManager();

    void getTrades(int& UserID, std::vector<Positon>& positions);
    void saveBalance(int& UserID, double& balance);
    void saveTrades(int& UserID, std::vector<Positon>& positions);
    int registerUser(std::string email, std::string password, double& balance, int& UserID);
    int loginUser(std::string email, std::string password, double& balance, int& UserID);
};

#endif // SQL_H
