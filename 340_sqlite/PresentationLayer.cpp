#include <iostream>
#include <QCoreApplication>
#include <QSql>
#include <QDebug>
#include <QFile>

//TODO

/*
 *Probably will make objects out of all of these things and put them in a header,
 *but, let's get this thing up and runnig in a single source file, first.
 */

//#include "databaseHeader.h"  //this will be for interfacing with the main API.
using namespace std;

//something for now: I just need an object to work with.
//! This is the struct which the database receives and parses from the main API.
struct db_command{
    char command[256];
    int reps;
    char exercise[256];
};

//! This function parses the received command.
void database_command(QSqlDatabase *db, struct command){

}

void setupDatabase(SqlDatabase *db){
    //create basic tables, etc.
    QSqlQuery query("CREATE TABLE exercises (ExerciseID int, Name varchar(255), Type int", *db);
    QSqlQuery query("CREATE TABLE users (UserID int, username varchar(255), password varchar(255)", *db);

    //I need a datetime object in this thing to clean this up.
    QSqlQuery query("CREATE TABLE logs (UserID int, ExerciseID int, weight int, reps int, year int, month int, day int, minute int, second int)", *db);

}

//! Upon opening the program, this either opens an existing database, or creates a new one.
void init_database(QSqlDatabase *db){
    bool newDatabase = false;

    //check to see if the database file exists.
    if(/*need to find something here*/){
        newDatabase = true;
    }

    *db = QSqlDatabase::addDatabase("QSQLITE");
    (*db).setDatabaseName("database.db");
    bool ok = (*db).open();

    if(!ok){
        cout << "Failed to open or create database.";
    }

    if(newDatabase){
        setupDatabase(db);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase *db;

    void init_database(db);

    //this will receive an object from the main API, and execute it accordingly.
    void database_command(struct db_command);
}

//why isn't this pushing to git?

//old code

/*
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("Netflix.sqlite");
bool ok = db.open();
if (!ok) {
    cout << "Error opening database" << endl;
    exit(1);
}

QSqlQuery query(db);
ok = query.exec("SELECT Count(*) FROM Movies");
if (!ok) {
    cout << "exec error" << endl;
    exit(1);
}
query.next();
int count = query.value(0).toInt();
cout << "count = " << count << endl;
/*
while (query.next()) {
    //QString name = query.value(0).toString();
    int count = query.value(0).toInt();
    cout << "count = " << count << endl;
    //int salary = query.value(1).toInt();
    //qDebug() << name << salary;
}
*/
/*
return a.exec();
*/
