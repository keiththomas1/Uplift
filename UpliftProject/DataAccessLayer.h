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


///The DBaseMan class manages the sqlite database and executes queries on it.
class DBaseMan
{
public:
    //!A constuctor that makes a persisting instance of the database.
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
        success = query.exec("CREATE TABLE IF NOT EXISTS exercise_table (exercise_name_id INTEGER PRIMARY KEY, exercise_name TEXT, user_id INTEGER)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        success = query.exec("CREATE TABLE IF NOT EXISTS workout_table (workout_name_id INTEGER PRIMARY KEY, workout_name TEXT, user_id INTEGER)");
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
        success = query.exec("CREATE TABLE IF NOT EXISTS exercise_set_log (set_id INTEGER PRIMARY KEY, workout_name_id INTEGER, workout_instance_id INTEGER, exercise_id INTEGER, user_id INTEGER, time timestamp default (strftime('%s', 'now')), reps INTEGER, weight INTEGER, one_rep_max INTEGER)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }

        //Added tables
        success = query.exec("CREATE TABLE IF NOT EXISTS exercise_user_pairs (user_id INTEGER, exercise_id INTEGER)");
        if (!success) {
            qDebug("Error creating exercise_user_pairs");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
        success = query.exec("CREATE TABLE IF NOT EXISTS workout_user_pairs (user_id INTEGER, workout_id INTEGER)");
        if (!success) {
            qDebug("Error creating workout_user_pairs");
            qDebug("%s", qPrintable(db.lastError().text()));
            //exit(0);
        }
    }

    //!A destructor
    ~DBaseMan() {}

    QSqlQuery executeQuery(QString);
    void closeDatabase();


private:
    //!Manages the database connection on the stack.
    QSqlDatabase db;
    //!Manages the database query results
    QSqlQuery query;

};

#endif // DATAACCESSLAYER_H
