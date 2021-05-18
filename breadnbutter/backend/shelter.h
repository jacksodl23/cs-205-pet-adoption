#ifndef SHELTER_H
#define SHELTER_H
#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
#include <cmath>
#include "pet.h"
#include "shelterowner.h"
#include "location.h"

class Shelter
{
public:
    Shelter(int id);
    Shelter(QString n, QString c, QString e);

    // accessor methods
    QString getName();
    QString getEmail();

    // mutator methods
    void setName(QString n);
    void setEmail(QString e);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();
    bool existsInDB();

    std::vector<Pet> getPets();

    ShelterOwner *getOwner() const;
    void setOwner(ShelterOwner *value);

    int getShelterID() const;

    void setShelterID(int value);

    int getLocID() const;

private:
    int shelterID;
    int locID;

    QString name;
    QString email;

    std::vector<Pet> pets;

    void fetchPets();
    ShelterOwner *owner;
    void fetchInfoFromID(int id);
};

#endif // SHELTER_H
