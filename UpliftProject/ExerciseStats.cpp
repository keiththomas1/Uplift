#include "ExerciseStats.h"
#include <QString>
#include <QSqlQuery>

//Stubs created.


int getFirstToLastWorkout(int user_id){
    QString command = "SELECT (SELECT time FROM workout_log WHERE user_id == '" + QString::number(user_id) + "' ORDER BY time DESC LIMIT 1) - (SELECT time FROM workout_log WHERE user_id == '" + QString::number(user_id) + "' ORDER BY time ASC LIMIT 1)";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return ((result.value(0).toInt())/60/60/24);
    }
    return -1; //failed*/
    ;
}

int getWorkoutFrequency(int user_id);

int getTotalNumOfWorkouts(int user_id);

int getTotalNumOfSets(int user_id);

int getAvgSetsPerWorkout(int user_id);

int getAvgRepsPerSet(int user_id);
