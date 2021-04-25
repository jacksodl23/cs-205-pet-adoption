#ifndef SHELTEROWNER_H
#define SHELTEROWNER_H

#include <QString>
#include <QtSql>
#include "user.h"

class ShelterOwner : public User
{
public:
    ~ShelterOwner();
    ShelterOwner(int id);
    ShelterOwner(QString fn, QString ln, QString loc, QString e, QString p);

    bool insertInDB();
    bool deleteFromDB();
    bool existsInDB();
    bool attemptLogin();
private:
    void chooseID();
};

#endif // SHELTEROWNER_H
