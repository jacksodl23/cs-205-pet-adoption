#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pet.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openDB();

    /* QSqlQuery query;
    query.exec("select * from pet");
    int fieldNo= query.record().indexOf("name");

    while (query.next()) {
        QString name = query.value(fieldNo).toString();
        qDebug() << "Pet name: " + name + "\n";
    } */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite"); // Temp in-memory db until actual database is created.

    if (!db.open()) {
        std::cerr << "Error opening database: " << db.lastError().text().toStdString() << std::endl;
        exit(-1);
    } else {
        qDebug() << "Database opened successfully.\n";

        /* QSqlQuery query;
        query.exec("drop table if exists pet");

        buildTable(); // Create the needed tables. Temporary until database is created. */
    }
}

void MainWindow::buildTable()
{
    QSqlQuery query;
    query.exec("create table pet (pet_id integer primary key autoincrement, "
               "name char not null)");
    if (query.exec()) {
        qDebug() << "Table created successfully.\n";
    } else {
        std::cerr << "Error with query: " << query.lastError().text().toStdString() << std::endl;
    }
}
