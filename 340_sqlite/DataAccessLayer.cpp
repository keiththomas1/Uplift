#include "dbaseman.h"

using namespace std;

//depreciated - constructor handles this one.
/*
void DBaseMan::openDatabase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dtabase.db");

    if(!db.open()){
        qDebug("Failed to connect.");
    }
    else{
        qDebug("Connected.");
    }
}
*/

//!This function sets up the database upon creation.
//!This function should only be called after verifying that no database currently exists.
void DBaseMan::setupDatabase(){
    //queryPtr->exec("drop table stuff");
    queryPtr->exec("CREATE TABLE exercise_table (exercise_name_id int primary key, exercise_name varchar(255))");
    queryPtr->exec("CREATE TABLE workout_table (workout_name_id int primary key, workout_name varchar(255))");
    queryPtr->exec("CREATE TABLE workout_pairs (workout_name_id int, exercise_name_id int, workout_order int)");
    queryPtr->exec("CREATE TABLE user_table (user_id int primary key, username varchar(255), password varchar(255))");
    queryPtr->exec("CREATE TABLE workout_log (workout_id int primary key, workout_name_id, timestamp datetime default current_timestamp)");
    queryPtr->exec("CREATE TABLE exercise_set_log (exercise_set_log_id int primary key, workout_id int, user_id int, timestamp datetime default current_timestamp, reps int, weight int)");
    //qDebug() << command.lastError();
}

//!This function is a debugging function used to test that the datbase is working properly.
void DBaseMan::testDatabase(){
    queryPtr->exec("INSERT INTO crap (crap_id, crapNum) VALUES (NULL, 55)");
    //qDebug() << command.lastError();
    queryPtr->exec("SELECT * FROM crap");
    //qDebug() << queryPtr->lastError();
}

//!This function is supposed to print the query to standard output.  This is mostly a debugging function.
void DBaseMan::printQuery(){
    while(queryPtr->next()){
        QString stuff = queryPtr->value(1).toString();
        cout << "We should have crap here: " << stuff.toStdString() << endl;
    }
}

//!This is used to close the database on exit of the program.
void DBaseMan::closeDatabase(){
    db.close();
}
