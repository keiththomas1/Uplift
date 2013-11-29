#ifndef DATAACCESSLAYER_H
#define DATAACCESSLAYER_H

#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

using namespace std;

//!This class manages the fundamentals of the database storage of the information.
class DBaseMan
{
public:
    //!This constuctor makes a persisting instance of the database.
    DBaseMan()
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "Connection");
        db.setDatabaseName("uplift.db");
        if(!db.open()) {
            qDebug("Error opening database");
            qDebug("%s", qPrintable(db.lastError().text())); //qPrintable for formatted output
            exit(0);
        }

        //create tables if they don't already exist
        QSqlQuery tmp(db);
        query = tmp;
        bool success;

        //This table is the only place that the exercise name needs to exist.  All other locations should only have the id number (in case of edits to the name).
        success = query.exec("CREATE TABLE IF NOT EXISTS exercise_table (exercise_name_id INTEGER PRIMARY KEY, exercise_name TEXT)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        success = query.exec("CREATE TABLE IF NOT EXISTS workout_table (workout_name_id INTEGER PRIMARY KEY, workout_name TEXT)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        success = query.exec("CREATE TABLE IF NOT EXISTS workout_pairs (workout_id INTEGER, exercise_id INTEGER, workoutOrder INTEGER)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        success = query.exec("CREATE TABLE IF NOT EXISTS user_table (user_id INTEGER PRIMARY KEY, username TEXT, password TEXT)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        //--->insert volume into here eventually?
        //Not necessarily.  We can just run a count query on the numebr of logs, selecting by user_id.
        success = query.exec("CREATE TABLE IF NOT EXISTS workout_log (workout_instance_id INTEGER PRIMARY KEY, user_id INTEGER, workout_name_id INTEGER, time timestamp default (strftime('%s', 'now')))");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        //don't pass in anything for set_id or time (especially not NULL). It will auto inc set_id and stamp time by default
        success = query.exec("CREATE TABLE IF NOT EXISTS exercise_set_log (set_id INTEGER PRIMARY KEY, workout_id INTEGER, exercise_id INTEGER, user_id INTEGER, time timestamp default (strftime('%s', 'now')), reps INTEGER, weight INTEGER, one_rep_max INTEGER)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
    }

    //!This destructor frees up the query information which is kept on the heap.
    ~DBaseMan() {}

    //!This function is a debugging function which runs queries on the database to test its functionality.
    void testDatabase();
    //!This function executes a given database query and returns the result.
    QSqlQuery executeQuery(QString);
    //!This function closes the database connection.
    void closeDatabase();
    //UNUSED: database currently managing IDs
    void StoreIDs(int, int, int, int, int, int);

private:
    //!This variable manages the database connection on the stack.
    QSqlDatabase db; //change name to m_db
    //!This variable manages the database query results
    QSqlQuery query; //change name to m_query

};

#endif // DATAACCESSLAYER_H
