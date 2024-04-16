#ifndef ALLUSERS_H
#define ALLUSERS_H

#include <QtSql>
//#include "user.h"

class AllUsers{
public:
    AllUsers();
    static void addUser(const QString& username, const QString& password);
    void showLeaderboard();
    bool authenticateUser(const QString& username, const QString& password);
    bool search(const QString& username);

private:
    QSqlDatabase db;
};

#endif // ALLUSERS_H
