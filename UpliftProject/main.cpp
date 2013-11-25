#include "widget.h"
#include <QApplication>
#include <iostream>
#include "BusinessLayer.h"
#include <QSqlQuery>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    BusinessTier *bt = new BusinessTier();
    bt->AddExercise("Squat");
    bt->AddExercise("bench press");
    bt->RemoveExercise("Squat");
    bt->RemoveExercise("bench press");
    bt->AddUser("erikboyle", "pass123");
    bt->RemoveUser("erikboyle", "pass123");

    bt->AddWorkout("All pro");
    bt->AddWorkout("Chest/Back A");

    bt->GetWorkoutList();
    */

    Widget w;
    w.show();

    return a.exec();
}
