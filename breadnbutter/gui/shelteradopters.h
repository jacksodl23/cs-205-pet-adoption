#ifndef SHELTERADOPTERS_H
#define SHELTERADOPTERS_H

#include <QMainWindow>

namespace Ui {
class ShelterAdopters;
}

class ShelterAdopters : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShelterAdopters(QWidget *parent = nullptr);
    ~ShelterAdopters();

private:
    Ui::ShelterAdopters *ui;
};

#endif // SHELTERADOPTERS_H
