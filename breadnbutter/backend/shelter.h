#ifndef SHELTER_H
#define SHELTER_H
#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
#include "pet.h"
#include "shelterowner.h"

class Shelter
{
public:
    Shelter(int id);
    Shelter(QString n, QString l, QString e);

    // accessor methods
    QString getName();
    QString getLocation();
    QString getEmail();

    // mutator methods
    void setName(QString n);
    void setLocation(QString l);
    void setEmail(QString e);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();
    bool existsInDB();

    std::vector<Pet> getPets();

    ShelterOwner *getOwner() const;
    void setOwner(ShelterOwner *value);

    int getShelterID() const;

private:
    int shelterID;
    QString name;
    QString location;
    QString email;

    std::vector<Pet> pets;

    void fetchPets();
    ShelterOwner *owner;
};

#endif // SHELTER_H
