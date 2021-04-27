#ifndef SHELTER_H
#define SHELTER_H
#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
#include "pet.h"

class Shelter
{
public:
    Shelter();
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

    std::vector<Pet> getPets();

private:
    int shelterID;
    QString name;
    QString location;
    QString email;
    int phoneNumber;
    std::vector<Pet> pets;

    void fetchPets();
};

#endif // SHELTER_H
