#include "mainwindow.h"
#include "../backend/globals.h"
#include "../backend/petowner.h"
#include "../backend/shelterowner.h"
#include <QApplication>
#include <QtSql>
#include <fstream>
#include <typeinfo>
#include <cstring>

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

    if(getCurrentUser() == -1)
        w.show();
    else {
        const char *typeName = typeid(currentUser).name();
        if (strcmp(typeName, "4User") == 0)
            w.showShelterDisplay();
        else
            w.showPetDisplay();
    }
    return a.exec();
}
