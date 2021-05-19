/*
 * The Pet class handles all Pet information as data members
 * within a given Pet object. The Pet class takes care of
 * inserting Pet information into the database and deleting
 * Pets from the database. The Pet class has getter methods
 * for all Pet attributes
 */

#ifndef PET_H
#define PET_H

#include <iostream>
#include <QString>
#include <QtSql>

class Pet
{
public:
    // default constructor - not recommended
    Pet();
    // constructor for pulling Pet info from
    // the database with the Pet ID
    Pet(int id);
    // constructor for initializing all Pet
    // information as arguments - sans database
    Pet(bool is_cat, QString name, int age, QString breed, QString color, QString hairLength, float weight, QString origin, bool hypoallergenic, QString description);

    /*
     * insertIntoDB() uses an insert SQL statement
     * to insert a Pet object's information/data members into the
     * application database
     */
    bool insertIntoDB(int shelterID);
    // deletes this Pet object's info from the database
    bool deleteFromDB();

    // simple getter that returns this Pet's name
    QString getName();
    // simple getter that returns this Pet's age
    int getAge() const;
    // simple getter that returns this Pet's breed
    QString getBreed() const;
    // simple getter that returns this Pet's color
    QString getColor() const;
    // simple getter that returns this Pet's
    // hypoallergenic status - yes or no, 1 or 0
    bool getHypoallergenic() const;
    // simple getter that returns this Pet's ID number
    int getPet_id() const;
    // simple getter that returns this Pet's cat status
    // yes or no - true or false
    bool getIs_cat() const;
    // simple getter that returns this Pet's origin
    // Shelter, Breeder, Rescue
    QString getOrigin() const;
    // simple getter that returns this Pet's description
    QString getDescription() const;
    // simple getter method that returns this Pet's weight
    float getWeight() const;
    // simple getter that returns this Pet's hair length
    // no hair, short, medium, long
    QString getHairLength() const;

private:
    // this Pet's ID number for the database
    int pet_id;

    // this Pet's cat status - true or false
    bool is_cat;

    // this Pet's name as a QString
    QString name;
    // this Pet's age as an integer
    int age;
    // this Pet's breed as a QString
    QString breed;

    // this Pet's hair color as a QString
    QString color;
    // this Pet's hair length as a QString
    QString hairLength;
    // this Pet's hypoallergenic status - true or false
    bool hypoallergenic;

    // this Pet's weight as a float/decimal
    float weight;

    // this Pet's origin as a QString
    // Shelter, Breeder, Rescue
    QString origin;

    // this Pet's description as a QString
    QString description;
};

#endif // PET_H
