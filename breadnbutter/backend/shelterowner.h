#ifndef SHELTEROWNER_H
#define SHELTEROWNER_H

#include <QString>
#include <QtSql>
#include "user.h"

class ShelterOwner : public User
{
public:
    ~ShelterOwner();

    // constructor given email and password.
    ShelterOwner(QString email, QString password);

    // constructor given an id.
    ShelterOwner(int id);

    // constructor given fields.
    ShelterOwner(QString fn, QString ln, QString city, QString e, QString ph, QString p);

    // inserts this instance into the database.
    bool insertInDB();

    // deletes this instance from the database.
    bool deleteFromDB();

    // checks if this instance already exsists in the database.
    bool existsInDB();
};

#endif // SHELTEROWNER_H
