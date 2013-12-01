#include "ExerciseStats.h"

//Stubs created.


int getFirstToLastWorkout(int user_id){
/*    QString command = "SELECT workout_name_id FROM workout_table WHERE workout_name == '" + name + "' AND user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed*/
    ;
}

int getWorkoutFrequency(int user_id);

int getTotalNumOfWorkouts(int user_id);

int getTotalNumOfSets(int user_id);

int getAvgSetsPerWorkout(int user_id);

int getAvgRepsPerSet(int user_id);
