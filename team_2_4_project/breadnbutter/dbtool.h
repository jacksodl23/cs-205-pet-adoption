#ifndef DBTOOL_H
#define DBTOOL_H

#include <iostream>
#include <QtSql>

/**
 * @brief The Database management tool
 *
 * This object represents the running sqlite3 database
 * instance, which is run as part of a library.  This
 * is the class that loads the sqlite file and will
 * allow for the basic tools for manipulating that object.
 * The Database object is essentally a specialized engine
 * that implements the primary features of a SQL relational
 * database as a local instance.
 */

class DBTool {

private:

    /// Name of the database.
    std::string db_name;

    /// Location of the database in the file structure.
    std::string db_location;

    QSqlDatabase *curr_db;

public:

    // Constructor that if called will cause the program to exit
    // indicating that more information should be provided.
    DBTool();

    // Constructors for loading a database file in the current
    // working directory.
    DBTool(std::string name);
    DBTool(const char* name);

    // Constructors for loading a database file in a specified
    // directory location.
    DBTool(std::string location, std::string name);
    DBTool(const char* location, const char* name);

    // Destructor that will cause the database to be closed storing
    // the updated contents of the sqlite file.
    ~DBTool();

    // Used to manually open the file, and called by each of the
    // constructors.
    int open_db();

    // prints state of database
    void print(std::ostream &sout);

    // provides a state check to determine if database is available
    bool db_open() { return curr_db ? true : false; }

    void runQuery(QString str);

    // Returns a pointer to the current database, only
    // used when absolutely necessary!
    QSqlDatabase * db_ref()  { return curr_db; }
};

#endif // DBTOOL_H

