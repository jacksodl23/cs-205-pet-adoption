#ifndef PETLIKED_H
#define PETLIKED_H

#include <QMainWindow>

namespace Ui {
class petliked;
}

class petliked : public QMainWindow
{
    Q_OBJECT

public:
    explicit petliked(QWidget *parent = 0);
    ~petliked();

private:
    Ui::petliked *ui;
};

#endif // PETLIKED_H
