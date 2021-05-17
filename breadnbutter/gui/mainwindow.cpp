#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setWelcomePhoto() {
    int numberOfPhotos = 8;

    srand(time(0));
    int photoNum = rand() % numberOfPhotos;

    QString photoString = QString::number(photoNum);

    QString tempPath(":/resources/imgs/petPhoto");
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
    openDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showPetDisplay()
{
    hide();
    petDisplay = new PetDisplay(this);
    petDisplay->setAttribute(Qt::WA_DeleteOnClose);
    petDisplay->show();
}

void MainWindow::showShelterDisplay()
{
    hide();
    shelterDisplay = new shelterProfile(this);
    shelterDisplay->setAttribute(Qt::WA_DeleteOnClose);
    shelterDisplay->show();
}

void MainWindow::on_loginButton_clicked()
{
    // hiding main window - figure out how to show after
    //hide();

    // on the stack - do we need to put it on the heap?
    // https://www.youtube.com/watch?v=VigUMAfE2q4&t=482s
    Login loginUI;
    loginUI.setModal(true);
    loginUI.exec();

    if (loginUI.loginSuccessful) {
        if (!currentUser.getIs_adopter())
            showShelterDisplay();
        else
            showPetDisplay();
    }

}

void MainWindow::on_createButton_clicked()
{
    // on the stack - do we need to put it on the heap?
    CreateAccount createUI;
    createUI.setModal(true);
    createUI.exec();

    if (createUI.signUpSuccessful) {
       if (!currentUser.getIs_adopter())
           showShelterDisplay();
       else
           showPetDisplay();
    }
}

void MainWindow::openDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    if (db.open()) {
        qDebug() << "Database opened successfully.";
    } else {
        qFatal("Error opening database.");
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_Bread_and_Butter_triggered()
{
   QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
                   "This application allows quick, efficient and effective services for those looking for pets!\n"
                   "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
