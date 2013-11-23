#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "BusinessLayer.h"
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();  // Should automatically fit to any mobile window size.

    BusinessTier *bt = new BusinessTier();

    return a.exec();
}
