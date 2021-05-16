#ifndef SHELTERADOPTERS_H
#define SHELTERADOPTERS_H

#include <QMainWindow>
#include <QtSql>
#include "../backend/shelter.h"

namespace Ui {
class ShelterAdopters;
}

class ShelterAdopters : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShelterAdopters(QWidget *parent = nullptr);
    ~ShelterAdopters();

    void setShelter(Shelter *value);

private slots:
    void on_actionQuit_triggered();

private:
    Ui::ShelterAdopters *ui;
    Shelter *shelter;

    void populateTable();
};

#endif // SHELTERADOPTERS_H
