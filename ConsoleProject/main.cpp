#include <QCoreApplication>
#include "exercise.h"
#include "coreds.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int menuOption;
    CoreDS *core_ds = new CoreDS();
    while (1) {
        cout << "Choose an option: " << endl;
        cout << "1. Create Exercise" << endl;
        cout << "2. Show Exercises" << endl;

        cout << "-> ";

        cin >> menuOption;

        if (menuOption == 1) {
            string exercise_name;
            int reps, weight;
            cout << "Enter an exercise name: ";
            cin >> exercise_name; //this is garbage
            cout << exercise_name << endl;
            cout << "Enter number of reps: ";
            cin >> reps;
            cout << reps << endl;
            cout << endl;
            cout << "Enter weight: ";
            cin >> weight;
            cout << endl;

            Exercise *ex = new Exercise(exercise_name, reps, weight, core_ds->GetNextExerciseID());
            core_ds->AddExercise(ex);
        }
        else if (menuOption == 2) {
            core_ds->PrintExercises();
        }
    }
    //Exercise *ex = core_ds->GetExercise(0);
    //printf("%s\n", ex->GetName().c_str());


    return 0;
    //return a.exec();
}
