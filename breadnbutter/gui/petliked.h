#ifndef PETLIKED_H
#define PETLIKED_H

#include <QMainWindow>
#include <QtSql>
#include <QString>
#include <vector>
#include "../backend/globals.h"
#include "../backend/pet.h"

namespace Ui {
class petliked;
}

class PetLiked : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetLiked(QWidget *parent = 0);
    ~PetLiked();

private slots:
    void on_button_next_clicked();

    void on_button_prev_clicked();

private:
    Ui::petliked *ui;

    int currentPos;

    std::vector<Pet> pets;
    void fetchLikedPets();

    void displayPet(Pet p);
};

#endif // PETLIKED_H
