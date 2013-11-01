#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //This creates an instance of the database object
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    MainWindow w;
    w.show();  // Should automatically fit to any mobile window size.

    return a.exec();
}
