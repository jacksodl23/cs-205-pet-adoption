#ifndef SHELTEROWNER_H
#define SHELTEROWNER_H

#include <QString>
#include <QtSql>
#include "user.h"

class ShelterOwner : public User
{
public:
    ~ShelterOwner();
    ShelterOwner(QString email, QString password);
    ShelterOwner(int id);
    ShelterOwner(QString fn, QString ln, QString loc, QString e, QString p);

    bool insertInDB();
    bool deleteFromDB();
    bool existsInDB();
};

#endif // SHELTEROWNER_H
