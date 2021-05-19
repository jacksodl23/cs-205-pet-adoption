#ifndef SHELTERUPLOAD_H
#define SHELTERUPLOAD_H

#include <QMainWindow>
#include <QMessageBox>
#include "../backend/pet.h"
#include "../backend/shelter.h"

namespace Ui {
class shelterUpload;
}

class shelterUpload : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterUpload(QWidget *parent = 0);
    ~shelterUpload();

    // sets the current shelter.
    void setShelter(Shelter *value);

private slots:
    // handles when cat or dog has been changed.
    void on_typeBox_currentTextChanged(const QString &arg1);

    // handles when a breed has been selected.
    void on_breedBox_activated(const QString &arg1);

    // handles when cancel button has been clicked.
    void on_cancelButton_clicked();

    // handles when upload button has been clicked.
    void on_addButton_clicked();

    // handles when the profile menu item has been clicked.
    void on_actionProfile_triggered();

    // handles when the help menu item has been clicked.
    void on_actionHelp_triggered();

    // handles when the log out menu item has been clicked.
    void on_actionLog_out_triggered();

    // handles when the quit menu item has been clicked.
    void on_actionQuit_triggered();

    // handles when the about menu item has been clicked.
    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::shelterUpload *ui;

    // tracks the shelter to upload the pet to.
    Shelter *shelter;

    // fetches a list of dog breeds from the database.
    void fetchDogBreeds();

    // fetches a list of colors from the database.
    void fetchBreedColors();

    // fetches a list of hair lengths from the database.
    void fetchHairLengths();
};

#endif // SHELTERUPLOAD_H
