#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <fstream>
#include <QMainWindow>
#include <QPixmap>
#include <ctime>
#include <typeinfo>
#include <cstring>
#include <QString>
#include <QDebug>
#include <QtSql>
#include "login.h"
#include "createaccount.h"
#include "petdisplay.h"
#include "shelterupload.h"
#include "../backend/simplecrypt.h"
#include "../backend/globals.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setWelcomePhoto();
    void showPetDisplay();
    void showShelterDisplay();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

    void on_createButton_clicked();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap welcomePic;

    void openDB();

    PetDisplay *petDisplay;
    shelterUpload *shelterDisplay;
};
#endif // MAINWINDOW_H
