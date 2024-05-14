#ifndef ALLUSERS_H
#define ALLUSERS_H

#include <QString>
#include <QSqlDatabase>

class AllUsers {
public:
    AllUsers();
    static void initializeDatabase();
    static void addUser(const QString& username, const QString& password);
    static void showLeaderboard();
    static bool authenticateUser(const QString &username, const QString &password);
    static bool search(const QString& username);

private:
    static QSqlDatabase db;
    static QSqlDatabase getDatabaseConnection();
};

#endif // ALLUSERS_H
