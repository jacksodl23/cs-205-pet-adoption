#ifndef PETDISPLAY_H
#define PETDISPLAY_H

#include <QMainWindow>
#include <QDebug>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QtSql>
#include "../backend/globals.h"
#include "../backend/petowner.h"
#include "../backend/pet.h"
#include "../backend/location.h"
#include "petprofile.h"
#include "petliked.h"
#include "petownerhelp.h"

namespace Ui {
class PetDisplay;
}

class PetDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetDisplay(QWidget *parent = nullptr);
    ~PetDisplay();

private slots:
    void on_typeBox_activated(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_profileButton_clicked();

    void on_button_like_clicked();

    void on_button_dislike_clicked();

    void on_actionLog_out_triggered();

    void on_actionLiked_triggered();

    void on_actionHelp_triggered();

    void on_minAgeSlider_valueChanged(int value);

    void on_maxAgeSlider_valueChanged(int value);

    void on_minWeightSlider_valueChanged(int value);

    void on_maxWeightSlider_valueChanged(int value);

    void on_actionQuit_triggered();

    void on_searchRangeSlider_valueChanged(int value);

    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::PetDisplay *ui;
    PetProfile *profileUI;

    QSqlQuery query;

    QStringList dogImageList;
    QStringList catImageList;
    QPixmap petPic;
    std::vector<Pet> pets;
    int currentPos;

    void fetchPets();
    void displayPet(Pet p);
    void getCurrentUser();
    void updateBar();
};

#endif // PETDISPLAY_H
