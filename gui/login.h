#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <petdisplay.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginOkay_accepted();

private:
    Ui::Login *ui;
    //PetDisplay *petDisplay;
};

#endif // LOGIN_H
