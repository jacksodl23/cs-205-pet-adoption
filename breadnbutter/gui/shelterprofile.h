#ifndef SHELTERPROFILE_H
#define SHELTERPROFILE_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "../backend/globals.h"
#include "../backend/shelter.h"

namespace Ui {
class shelterProfile;
}

class shelterProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterProfile(QWidget *parent = 0);
    ~shelterProfile();

private:
    Ui::shelterProfile *ui;
    Shelter *currentShelter;

    void fetchShelter();
};

#endif // SHELTERPROFILE_H
