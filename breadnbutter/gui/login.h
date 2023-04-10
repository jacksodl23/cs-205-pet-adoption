/*
 * This Login class is for handling all information
 * and functionality associated with the Login GUI
 * The Login class can check for valid User information
 * and write to the User configuration file to allow
 * for auto login for Users who choose to do so
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <fstream>
#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QPushButton>
#include "petdisplay.h"
#include "../backend/globals.h"
#include "../backend/petowner.h"
#include "../backend/shelterowner.h"
#include "../backend/user.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    // Login constructor
    explicit Login(QWidget *parent = nullptr);
    // Login destructor
    ~Login();

    // boolean variable for successful logins
    // used for error checking
    bool loginSuccessful;

private slots:
    // private slot method for handling
    // User information including email and password
    // verification, and the Stay Logged In
    // functionality when the Login/Ok button
    // is selected
    void on_loginOkay_accepted();

private:
    // private pointer to the Login UI
    Ui::Login *ui;

    // private method used for writing User
    // information to the User configuration file
    // for auto login functionality
    void writeUserToFile(User user);
};

#endif // LOGIN_H
