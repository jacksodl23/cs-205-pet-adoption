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

    void on_colorBox_activated(const QString &arg1);

    void on_hairLenBox_activated(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

    void on_hypoBox_currentTextChanged(const QString &arg1);

    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::shelterUpload *ui;
    QString type;
    QString breed;
    float weight;
    int age;
    QString hairLength;
    QString color;
    bool hypoallergenic;
    QString origin;
    QString description;
    QString name;
    bool is_cat;

    bool upload;

    Shelter *shelter;

};

#endif // SHELTERUPLOAD_H
