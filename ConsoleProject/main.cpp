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

    //need to catch the user login: new_user() or user_login()
    //A separate function can take care of this.

    int menuOption;
    CoreDS *core_ds = new CoreDS();
    /*
    ex = new Exercise("Squat", 15, 180, core_ds->GetNextExerciseID());
    core_ds->AddExercise(ex);
    ex = new Exercise(exercise_name, reps, weight, core_ds->GetNextExerciseID());
    core_ds->AddExercise(ex);
    ex = new Exercise(exercise_name, reps, weight, core_ds->GetNextExerciseID());
    core_ds->AddExercise(ex);
    ex = new Exercise(exercise_name, reps, weight, core_ds->GetNextExerciseID());
    core_ds->AddExercise(ex);
    ex = new Exercise(exercise_name, reps, weight, core_ds->GetNextExerciseID());
    core_ds->AddExercise(ex);
    */
    string exercise_name;
    int reps, weight;
    while (1) {
        cout << endl;
        cout << "Choose an option: " << endl;
        cout << "1. Create New Exercise" << endl;
        cout << "2. Display Exercise List" << endl;
        cout << "3. Log a set of an exercise" << endl;
        cout << "4. Display exercise history" << endl;

        cout << "-> ";
        cin >> menuOption;
        cout << endl;
        switch(menuOption) {
        case 1: {
            cout << "Enter an exercise name: ";
            std::getline(cin, exercise_name);
            std::getline(cin, exercise_name);
            core_ds->AddToExercisesList(exercise_name); //Doesn't check case of the string
            break;
        }
        case 2: {
            core_ds->PrintExerciseList();
            break;
        }
        case 3: {
            core_ds->PrintExerciseList();
            cout << "Enter a exercise to perform a set of" << endl;
            std::getline(cin, exercise_name);
            std::getline(cin, exercise_name);
            int ID = core_ds->GetExerciseIDFromName(exercise_name);
            if (ID == -1) {
                cout << exercise_name << " is not a valid exercise" << endl;
                continue;
            }
            cout << "Enter # reps: ";
            cin >> reps;
            cout << "Enter weight: ";
            cin >> weight;
            Exercise *ex = new Exercise(exercise_name, reps, weight, core_ds->GetNextExerciseID());
            core_ds->AddExercise(ex);
            break;
        }
        case 4: {
            core_ds->PrintExerciseObjects();
            break;
        }
        }
    }
    //Exercise *ex = core_ds->GetExercise(0);
    //printf("%s\n", ex->GetName().c_str());


    return 0;
    //return a.exec();
}
