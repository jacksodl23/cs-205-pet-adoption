#include "mainwindow.h"
#include "../backend/globals.h"
#include "../backend/petowner.h"
#include "../backend/shelterowner.h"
#include <QApplication>
#include <QtSql>
#include <fstream>
#include <cstring>

/*
 * the getCurrentUser() method
 * allows for auto login for verified users
 * who have selected the Stay Logged In option
 * on the Login page
 * This method checks to see what the ID of the
 * currentUser is for a given instance of the
 * application on a machine with the User
 * configuration file
 * If the method returns -1 then there is no
 * currentUser logged into the system, and the
 * main window with Login and CreateAccount options
 * should open
 */
int getCurrentUser() {
    std::string line;
    std::ifstream config("currentuser.config");

    if (config.is_open()) {
        while (getline(config, line)) {
            SimpleCrypt crypto(CRYPTO_KEY);

            QString lineString = QString::fromStdString(line);
            QString decrypted = crypto.decryptToString(lineString);
            int theID = decrypted.toInt();

            QSqlQuery query;
            query.prepare("select is_adopter from User where user_id = ?");
            query.addBindValue(theID);

            if (query.exec()) {
                if (query.next()) {
                    int is_adopter = query.value(0).toInt();

                    if (is_adopter == 1)
                        currentUser = PetOwner(theID);
                    else if (is_adopter == 0)
                        currentUser = ShelterOwner(theID);
                } else {
                    qDebug() << "No valid user could be found.";
                    return -1;
                }
            } else {
                qDebug() << "Error getting user:" << query.lastError().text();
                return -1;
            }

            return theID;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if (getCurrentUser() == -1)
        w.show();
    else {
        if (!currentUser.getIs_adopter())
            w.showShelterDisplay();
        else
            w.showPetDisplay();
    }
    return a.exec();
}
