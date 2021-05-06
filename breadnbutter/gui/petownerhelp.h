#ifndef PETOWNERHELP_H
#define PETOWNERHELP_H

#include <QMainWindow>

namespace Ui {
class petownerhelp;
}

class petownerhelp : public QMainWindow
{
    Q_OBJECT

public:
    explicit petownerhelp(QWidget *parent = 0);
    ~petownerhelp();

private slots:
    void on_actionLiked_triggered();

    void on_actionSearch_triggered();

    void on_actionLog_out_triggered();

private:
    Ui::petownerhelp *ui;
};

#endif // PETOWNERHELP_H
