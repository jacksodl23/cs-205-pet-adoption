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

    void setShelter(Shelter *value);

private slots:
    void on_typeBox_currentTextChanged(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

    void on_cancelButton_clicked();

    void on_addButton_clicked();

    void on_actionProfile_triggered();

    void on_actionHelp_triggered();

    void on_actionLog_out_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::shelterUpload *ui;

    Shelter *shelter;

    void fetchDogBreeds();
    void fetchBreedColors();
    void fetchHairLengths();
};

#endif // SHELTERUPLOAD_H
