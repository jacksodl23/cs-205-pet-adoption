/*
 * This MainWindow class handles all of the information handling
 * and functionality needed for the MainWindow GUI, including opening
 * the Login GUI and CreateAccount GUI when necessary and opening
 * the application's database to write and read Users from the file
 * The MainWindow will also handling opening the default PetOwner and
 * ShelterOwner pages when the User has logged in
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <fstream>
#include <QMainWindow>
#include <QPixmap>
#include <ctime>
#include <cstring>
#include <QString>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include "login.h"
#include "createaccount.h"
#include "petdisplay.h"
#include "shelterprofile.h"
#include "../backend/simplecrypt.h"
#include "../backend/globals.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // default MainWindow constructor
    MainWindow(QWidget *parent = nullptr);
    // MainWindow destructor
    ~MainWindow();

    // method to open the PetDisplay page for
    // adopters/PetOwners who have logged in
    void showPetDisplay();
    // method to open the shetlerProfile page
    // for providers/ShelterOwners who have
    // logged in
    void showShelterDisplay();

private slots:
    // slot method for opening the Login page
    void on_loginButton_clicked();
    // slot method for opening the CreateAccount page
    void on_createButton_clicked();

    // slot method for quit menu item
    // quits the BreadnButter application
    void on_actionQuit_triggered();
    // slot method for opening About BreadnButter
    // dialog window
    void on_actionAbout_Bread_and_Butter_triggered();

private:
    // private MainWindow UI pointer
    Ui::MainWindow *ui;

    // QPixmap for the welcome photo on the MainWindow
    // QPixmap is a QT class that allows for easy use
    // of images
    QPixmap welcomePic;

    // private method for opening the application's
    // database of Users, Pets, Shelters, and more
    void openDB();

    // setting the welcome photo and our icon
    // on the MainWindow/main page
    void setWelcomePhoto();

    // PetDisplay pointer to reference the pet search
    // page named petDisplay
    // this is the default page for PetOwner
    PetDisplay *petDisplay;
    // shelterProfile pointer to reference the shelter
    // profile page name shelterDisplay
    // this is the default page for ShelterOwner
    shelterProfile *shelterDisplay;
};
#endif // MAINWINDOW_H
