#ifndef PETDISPLAY_H
#define PETDISPLAY_H

#include <QMainWindow>
#include <QDebug>
#include <vector>
#include <string>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>

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
    void on_actionQuit_triggered();

    void on_typeBox_activated(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::PetDisplay *ui;
    QPixmap petPic;
};

#endif // PETDISPLAY_H
