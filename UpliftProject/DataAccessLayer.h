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
        success = query.exec("CREATE TABLE IF NOT EXISTS exercise_table (exercise_name_id INT PRIMARY KEY, exercise_name TEXT)");
        if (!success) {
            qDebug("Error creating exercise_table");
            qDebug("%s", qPrintable(db.lastError().text()));
            exit(0);
        }
        query.exec("CREATE TABLE IF NOT EXISTS workout_table (workout_name_id INT PRIMARY KEY, workout_name TEXT)");
        query.exec("CREATE TABLE IF NOT EXISTS workout_pairs (workout_name TEXT, exercise_name TEXT, workout_order INT)");
        query.exec("CREATE TABLE IF NOT EXISTS user_table (user_id INT PRIMARY KEY, username TEXT, password TEXT)");
        query.exec("CREATE TABLE IF NOT EXISTS workout_log (workout_id INT PRIMARY KEY, workout_name_id, timestamp datetime default current_timestamp)");
        query.exec("CREATE TABLE IF NOT EXISTS exercise_set_log (exercise_set_log_id INT PRIMARY KEY, workout_id INT, user_id INT, timestamp datetime default current_timestamp, reps INT, weight INT)");
        //query.exec("CREATE TABLE IF NOT EXISTS id_table (NextWorkoutID INT, NextWorkoutNameID INT, NextExerciseID INT, NextExerciseSetID INT, NextExerciseNameID INT, NextUserID INT)");
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
