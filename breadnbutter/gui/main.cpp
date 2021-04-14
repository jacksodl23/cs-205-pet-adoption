#include "mainwindow.h"

#include <QApplication>
#include <fstream>
#include <string>

int getCurrentUserID() {
    std::ifstream configStream("currentuserid");

    if (!configStream.is_open()) {
        std::cerr << "Error opening config file." << std::endl;
    }

    std::string line;

    while (getline(configStream, line)) {
        int id = std::stoi(line);

        return id;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
