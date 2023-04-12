#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <fstream>
#include "pet.h"

/**
 * @brief The User class.
 * Superclass of both ShelterOwner and PetOwner.
 * Stores shared variables and method implementation.
 */

class User
{
public:
    User();
    User(QString email, QString password);
    virtual ~User();

    // inserts user into database.
    virtual bool insertInDB();

    // deletes user from database.
    virtual bool deleteFromDB();

    // checks if user already exists in database.
    virtual bool existsInDB();

    // likes a given pet.
    virtual bool likePet(Pet p);

    // logs in the user.
    bool attemptLogin();

    // logs out the user.
    void logOut(std::string rootPath);

    // returns the user's ID.
    int getID();

    // returns the user's first name.
    QString getFirstName();

    // returns if the user is an adopter.
    bool getIs_adopter() const;

    // returns the user's last name.
    QString getLastName() const;

    // returns the user's email.
    QString getEmail() const;

    // returns the user's phone number.
    QString getPhoneNumber() const;

    // gets the ID of the user's Location record.
    int getLocID() const;

protected:
    // the user's ID.
    int id;

    // the ID of the user's Location record.
    int locID;

    // the user's first name.
    QString firstName;

    // the user's last name.
    QString lastName;

    // the user's phone number.
    QString phoneNumber;

    // the user's email.
    QString email;

    // the user's password.
    QString password;

    // tracks if the user is an adopter.
    bool is_adopter;

    // chooses the ID that should be used prior to insertion.
    void chooseID();
};

#endif // USER_H
