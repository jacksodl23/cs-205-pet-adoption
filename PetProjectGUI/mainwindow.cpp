#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setWelcomePhoto() {
    int numberOfPhotos = 8;

    srand(time(0));
    int photoNum = rand() % numberOfPhotos;

    QString photoString = QString::number(photoNum);

    QString tempPath("../../../../CoverPhoto");
    tempPath.append(photoString);
    QString filePath = tempPath.append(".jpg");
    qDebug() << filePath;

    welcomePic.load(filePath);
    int width = ui->labelPic->width();
    int height = ui->labelPic->height();
    ui->labelPic->setPixmap(welcomePic.scaled(width, height, Qt::KeepAspectRatio));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWelcomePhoto();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    // hiding main window - figure out how to show after
    // hide();

    // on the stack - do we need to put it on the heap?
    // https://www.youtube.com/watch?v=VigUMAfE2q4&t=482s
    Login loginUI;
    loginUI.setModal(true);
    loginUI.exec();
}

void MainWindow::on_createButton_clicked()
{
    // hiding main window
    //    hide();

    // on the stack - do we need to put it on the heap?
    CreateAccount createUI;
    createUI.setModal(true);
    createUI.exec();
}
