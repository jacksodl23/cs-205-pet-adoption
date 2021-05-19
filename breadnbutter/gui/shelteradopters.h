#ifndef SHELTERADOPTERS_H
#define SHELTERADOPTERS_H

#include <QMainWindow>
#include <QtSql>
#include "../backend/shelter.h"
#include <QMessageBox>

namespace Ui {
class ShelterAdopters;
}

class ShelterAdopters : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShelterAdopters(QWidget *parent = nullptr);
    ~ShelterAdopters();

    // sets which shelter to retrieve information from.
    void setShelter(Shelter *value);

private slots:
    // closes the program when the quit button is clicked.
    void on_actionQuit_triggered();

    // shows a dialog explaining the program.
    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::ShelterAdopters *ui;

    // the shelter owned by the currently logged in shelter owner.
    Shelter *shelter;

    // used to populate the table with adopters that have liked this shelter's pets.
    void populateTable();
};

#endif // SHELTERADOPTERS_H
