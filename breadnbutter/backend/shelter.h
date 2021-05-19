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

    std::vector<Pet> getPets(); // accessor method that fetches all pets in the shelter

    ShelterOwner *getOwner() const; // accessor method that fetches shelter's owner
    void setOwner(ShelterOwner *value); // mutator method that sets shelter's owner

    int getShelterID() const; // accessor method that fetches shelter's ID

    void setShelterID(int value); // mutator method that sets shelter's ID

    int getLocID() const; // accessor method that fetches shelter's location ID

private:
    int shelterID; // shelter ID
    int locID; // location ID

    QString name; // shelter's name
    QString email; // shelter's email

    std::vector<Pet> pets; // shelter's pets vector

    void fetchPets(); // method to fetch all shelter's pets
    ShelterOwner *owner;
    void fetchInfoFromID(int id); // method to fetch information about shelter based on its ID
};

#endif // SHELTER_H
