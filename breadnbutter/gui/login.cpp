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
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();

    User user(email, password);
    loginSuccessful = user.attemptLogin();

    if (loginSuccessful) {
        QSqlQuery query;
        query.prepare("select is_adopter from User where user_id = ?");
        query.addBindValue(user.getID());

        if (query.exec()) {
            if (query.next()) {
                int is_adopter = query.value(0).toInt();

                if (is_adopter == 1) {
                    currentUser = PetOwner(user.getID());
                    writeUserToFile(currentUser);
                }
                else if (is_adopter == 0) {
                    currentUser = ShelterOwner(user.getID());
                    writeUserToFile(currentUser);
                }
            }
        } else {
            qDebug() << "Error determining if user is adopter:" << query.lastError().text();
        }
    } else {
        QMessageBox::critical(this, "Error Logging In", "Something went wrong when logging in. Please try again.");
    }
}

void Login::writeUserToFile(User user)
{
    std::ofstream config("currentuser.config");

    SimpleCrypt crypto(CRYPTO_KEY);
    QString id = QString::number(user.getID());
    QString encoded = crypto.encryptToString(id);

    config << encoded.toStdString();
    config.close();
}
