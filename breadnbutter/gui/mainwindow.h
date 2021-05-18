/*
 * This MainWindow class handles all of the information handling
 * and functionality needed for the MainWindow GUI, including opening
 * the Login GUI and CreateAccount GUI when necessary
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
    void showPetDisplay();
    void showShelterDisplay();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

    void on_createButton_clicked();

    void on_actionQuit_triggered();

    void on_actionAbout_Bread_and_Butter_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap welcomePic;

    void openDB();
    void setWelcomePhoto();

    PetDisplay *petDisplay;
    shelterProfile *shelterDisplay;
};
#endif // MAINWINDOW_H
