#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->loginOkay->button(QDialogButtonBox::Ok)->setText("Login");
    loginSuccessful = false;
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginOkay_accepted()
{
    // where should we store user information?
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();
    QString welcomeMessage = "Welcome ";

    PetOwner owner(email, password);
    loginSuccessful = owner.attemptLogin();

    if (loginSuccessful) {
        currentUserID = owner.getID();

        std::ofstream config("currentuser.config");

        SimpleCrypt crypto(CRYPTO_KEY);
        QString id = QString::number(owner.getID());
        QString encoded = crypto.encryptToString(id);

        config << encoded.toStdString();
        config.close();
    }
}
