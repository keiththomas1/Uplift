#ifndef DATAACCESSLAYER_H
#define DATAACCESSLAYER_H

#include <QCoreApplication>
#include <iostream>
#include <string.h>
#include <QString>
#include <QSqlQuery>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

//TODO:
/*
 *FUNCTIONS NEEDED:
 *dynamic prepare statements for different queries (take parameters)
 */

using namespace std;

//!This class manages the fundamentals of the database storage of the information.
class DBaseMan{

    //!This variable manages the database connection on the stack.
    QSqlDatabase db;
    //!This variable manages the database query results dynamically on the heap.
    QSqlQuery* queryPtr;

public:
    //!This constuctor makes a persisting instance of the database.
    DBaseMan() : db(QSqlDatabase::addDatabase("QSQLITE")),queryPtr(0)
    {
        db.setDatabaseName("database.db");
        if(!db.open())
            return;
        queryPtr = new QSqlQuery(db);
    }
    //!This deconstructor frees up the query information which is kept on the heap.
    ~DBaseMan()
    {
        delete queryPtr; queryPtr = 0;
    }

/*
 *I've definitely got some more functions to add here, but this thing should sucessfully build the basic database.
 *Don't ask me to add and query for stuff yet.
 */

//public function list
    //!This function sets up a new, non-existing database.
    void setupDatabase();
    //void openDatabase();
    //!This function is a debugging function, used to test that queries are being retreived from the database.
    void printQuery();
    //!This function closes the database connection.
    void closeDatabase();

//debug functions
public:
    //!This function is a debugging function which runs queries on the database to test its functionality.
    void testDatabase();
};

#endif // DATAACCESSLAYER_H
