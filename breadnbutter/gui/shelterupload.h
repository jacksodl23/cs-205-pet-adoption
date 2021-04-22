#ifndef SHELTERUPLOAD_H
#define SHELTERUPLOAD_H

#include <QMainWindow>
#include "../backend/pet.h"

namespace Ui {
class shelterUpload;
}

class shelterUpload : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterUpload(QWidget *parent = 0);
    ~shelterUpload();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_comboBox_4_activated(const QString &arg1);

    void on_comboBox_5_activated(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::shelterUpload *ui;
    QString type;
    QString breed;
    float weight;
    int age;
    QString hairLength;
    QString color;
    QString allergy;
    QString origin;
    QString description;
    QString name;
};

#endif // SHELTERUPLOAD_H
