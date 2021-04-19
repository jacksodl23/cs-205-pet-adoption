#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include "../backend/petowner.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

    bool signUpSuccessful;

private slots:
    void on_createOkay_accepted();

private:
    Ui::CreateAccount *ui;
};

#endif // CREATEACCOUNT_H
