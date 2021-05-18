#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <fstream>
#include "pet.h"
#include "location.h"

class Location;

class User
{
public:
    User();
    User(QString email, QString password);
    virtual ~User();

    virtual bool insertInDB();
    virtual bool deleteFromDB();
    virtual bool existsInDB();

    virtual bool likePet(Pet p);

    bool attemptLogin();
    void logOut();

    int getID();

    QString getFirstName();

    bool getIs_adopter() const;

    QString getLastName() const;

    QString getEmail() const;

    QString getPhoneNumber() const;

    int getLocID() const;

protected:
    int id;
    int locID;

    QString firstName;
    QString lastName;
    QString phoneNumber;
    QString email;
    QString password;

    bool is_adopter;

    void chooseID();
};

#endif // USER_H
