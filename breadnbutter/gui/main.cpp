#include "mainwindow.h"
#include "petdisplay.h"
#include "../backend/globals.h"
#include <QApplication>
#include <fstream>

int getCurrentUser() {
    std::string line;
    std::ifstream config("currentuser.config");

    if (config.is_open()) {
        while (getline(config, line)) {
            SimpleCrypt crypto(CRYPTO_KEY);

            QString lineString = QString::fromStdString(line);
            QString decrypted = crypto.decryptToString(lineString);
            int theID = decrypted.toInt();
            currentUserID = theID;

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
    else
        w.showPetDisplay();
    return a.exec();
}
