#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QPixmap>
#include <ctime>
#include <QString>
#include <QDebug>
#include "login.h"
#include "createaccount.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setWelcomePhoto();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

    void on_createButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap welcomePic;
};
#endif // MAINWINDOW_H
