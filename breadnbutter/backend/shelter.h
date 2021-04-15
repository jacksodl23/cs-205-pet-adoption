#ifndef SHELTER_H
#define SHELTER_H
#include <QString>
#include <QtSql>
#include <iostream>

class Shelter
{
public:
    Shelter(int id);
    Shelter(QString n, QString l, int p, QString e);

    // accessor methods
    int getPhoneNumber();
    QString getName();
    QString getLocation();
    QString getEmail();

    // mutator methods
    void setPhoneNumber(int p);
    void setName(QString n);
    void setLocation(QString l);
    void setEmail(QString e);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();
    bool existsInDB();

private:
    int shelterID;
    QString name;
    QString location;
    QString email;
    int phoneNumber;
};

#endif // SHELTER_H
