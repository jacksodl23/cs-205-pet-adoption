#ifndef PETDISPLAY_H
#define PETDISPLAY_H

#include <QMainWindow>

namespace Ui {
class PetDisplay;
}

class PetDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetDisplay(QWidget *parent = nullptr);
    ~PetDisplay();

private:
    Ui::PetDisplay *ui;
};

#endif // PETDISPLAY_H
