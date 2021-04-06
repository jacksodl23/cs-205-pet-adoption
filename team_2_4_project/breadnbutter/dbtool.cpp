#include "dbtool.h"

DBTool::DBTool() {
    std::cerr << "Name must be provided to DBTool Class "
              << "during creation.\n";
    exit(-1);
}

DBTool::DBTool(std::string name) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        std::cerr << "Unable to load database this demo needs the SQLITE driver" <<std::endl;
        exit(-1);
    }

    db_name     = name;
    db_location = ".";

    open_db();
}


DBTool::DBTool(const char* name) {
    //std::cerr << "constructing object 2\n";

    db_name     = name;
    db_location = ".";

    open_db();
}

DBTool::DBTool(const char* location, const char* name) {
    //std::cerr << "constructing object 3\n";

    db_name     = name;
    db_location = location;

    open_db();
}


DBTool::DBTool(std::string location, std::string name) {
    //std::cerr << "constructing object 4\n";

    db_name     = name;
    db_location = location;

    open_db();
}


DBTool::~DBTool() {

    //std::cerr << "closing object\n";

    curr_db->close();
    curr_db = NULL;
}


/** Method that will open the provided database.
 */
int DBTool::open_db() {

    int retCode = 0;

    std::string full_name =db_location + "/" + db_name;

    // open the database --------------------

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(full_name));
    //    db.setDatabaseName(":memory:"); use to create temporary in-memory db

    if(!db.open()){
        std::cerr << "Database does not open -- "
                  << db.lastError().text().toStdString()
                  << std::endl;

        std::cerr << "  File -- " << full_name << std::endl;
        exit(0);
    }else{
        std::cerr << "Opened database successfully\n";
    }

    return retCode;
}


void DBTool::print(std::ostream &sout) {

    sout << "DB Name : " << db_name     << std::endl;
    sout << "DB Loc  : " << db_location << std::endl;

    sout << "Status  : "
         << ( db_open() ? "open" : "closed" )
         << std::endl;
}

void DBTool::runQuery(QString str){
    QSqlQuery qry;
    if(!qry.exec(str)){
        qDebug()<<"error running query";
    }
}

