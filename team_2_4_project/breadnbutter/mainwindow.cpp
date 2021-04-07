#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:"); // Temp in-memory db until actual database is created.

    if (!db.open()) {
        std::cerr << "Error opening database: " << db.lastError().text().toStdString() << std::endl;
        exit(-1);
    } else {
        qDebug() << "Database opened successfully.\n";
    }
}
