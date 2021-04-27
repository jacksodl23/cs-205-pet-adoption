#include "petliked.h"
#include "ui_petliked.h"

petliked::petliked(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::petliked)
{
    ui->setupUi(this);
}

petliked::~petliked()
{
    delete ui;
}
