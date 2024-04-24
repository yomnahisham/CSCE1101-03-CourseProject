#ifndef ALLUSERS_H
#define ALLUSERS_H

#include <QString>


class AllUsers{
public:
    AllUsers();
    static void addUser(const QString& username, const QString& password);
    static bool search(const QString& username);
    static void showLeaderboard();
    static bool authenticateUser(const QString& username, const QString& password);
    static int getScore(const QString& username);
    static void updateScoreInDropbox(const QString& username, int score);

private:
    static void saveUserDataToDropbox(const QString& username, const QString& password, int score);
    static bool isTokenExpired();
    static void refreshToken();
    static qint64 tokenExpirationTimestamp; //very excessively long int (qint64)
};

#endif // ALLUSERS_H
