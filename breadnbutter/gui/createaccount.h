#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <fstream>
#include "../backend/petowner.h"
#include "../backend/simplecrypt.h"
#include "../backend/globals.h"
#include "../backend/shelterowner.h"
#include "../backend/shelter.h"
#include "../backend/user.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
    Q_OBJECT

public:
    // CreateAccount page constructor
    explicit CreateAccount(QWidget *parent = nullptr);
    // CreateAccount page destructor
    ~CreateAccount();

    // boolean for successful signup
    bool signUpSuccessful;

private slots:

    // slot method for handling the User's input data
    // from the CreateAccount form when they click
    // the Ok/Sign up button - creates necessary objects
    // and adds to database and config files
    void on_createOkay_clicked(QAbstractButton *button);

    // slot method to handle User input based off of
    // their selected role - Adopter/PetOwner or
    // Provider/ShelterOwner
    void on_roleBox_activated(const QString &arg1);

private:
    // private UI pointer
    Ui::CreateAccount *ui;

    // private method for writing a User's information
    // and encrypted ID to the User configuration file
    // allowing for use of the application without
    // repeated logging in
    void writeUserToFile(User newUser);

    // takes all necessary adopter/PetOwner information and
    //
    void signUpAdopter(QString firstName, QString lastName, QString location, QString email, QString phone, QString password);
    void linkShelterOwnerToShelter(Shelter s, QString location, QString firstName, QString email, QString phone, QString lastName, QString password);
};

#endif // CREATEACCOUNT_H
