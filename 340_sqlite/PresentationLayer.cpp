#include <iostream>
#include <QCoreApplication>
#include <QtSql>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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
    return a.exec();
}

//why isn't this pushing to git?
