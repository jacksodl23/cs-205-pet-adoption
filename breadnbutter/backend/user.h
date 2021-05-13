#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <fstream>

class User
{
public:
    User();
    User(QString email, QString password);
    virtual ~User();

    virtual bool insertInDB();
    virtual bool deleteFromDB();
    virtual bool existsInDB();

    bool attemptLogin();
    void logOut();

    int getID();

    QString getFirstName();

    bool getIs_adopter() const;

    QString getLastName() const;

    QString getEmail() const;

    QString getPhoneNumber() const;

protected:
    int id;
    QString firstName;
    QString lastName;
    QString location;
    QString phoneNumber;
    QString email;
    QString password;

    bool is_adopter;

    void chooseID();
};

#endif // USER_H
