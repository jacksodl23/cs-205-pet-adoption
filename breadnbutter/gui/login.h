#ifndef LOGIN_H
#define LOGIN_H

#include <fstream>
#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QPushButton>
#include "petdisplay.h"
#include "../backend/simplecrypt.h"
#include "../backend/globals.h"
#include "../backend/petowner.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    bool loginSuccessful;

private slots:
    void on_loginOkay_accepted();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
