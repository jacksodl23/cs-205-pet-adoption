#ifndef SHELTEROWNER_H
#define SHELTEROWNER_H

#include <QString>
#include <QtSql>

class ShelterOwner
{
public:
    ShelterOwner();
    ShelterOwner(int id);
    ShelterOwner(QString fn, QString ln, QString loc, QString e, QString p);

    bool insertInDB();
    bool deleteFromDB();
    bool existsInDB();
    bool attemptLogin();
private:
    int ownerID;
    QString firstName;
    QString lastName;
    QString location;
    QString email;
    QString password;

    void chooseID();
};

#endif // SHELTEROWNER_H
