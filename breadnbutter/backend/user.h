#ifndef USER_H
#define USER_H

#include <QString>
#include <iostream>

class User
{
public:
    User();
    virtual ~User();

   virtual bool insertInDB();
   virtual bool deleteFromDB();
   virtual bool existsInDB();
   virtual bool attemptLogin();

    int getID();

    QString getFirstName();

protected:
    int id;
    QString firstName;
    QString lastName;
    QString location;
    QString email;
    QString password;

    virtual void chooseID();
};

#endif // USER_H
