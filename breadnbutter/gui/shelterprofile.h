#ifndef SHELTERPROFILE_H
#define SHELTERPROFILE_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "../backend/globals.h"
#include "../backend/shelter.h"
#include "shelterupload.h"

namespace Ui {
class shelterProfile;
}

class shelterProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterProfile(QWidget *parent = 0);
    ~shelterProfile();

private slots:
    void on_actionUpload_triggered();

    void on_actionLog_out_triggered();

private:
    Ui::shelterProfile *ui;
    Shelter *currentShelter;

    void fetchShelter();
    void populatePetsTable();
    void logOutShelterOwner();
};

#endif // SHELTERPROFILE_H
