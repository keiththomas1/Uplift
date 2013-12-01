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
}

int getTotalNumOfWorkouts(int user_id){
    QString command = "SELECT count(*) FROM workout_log WHERE user_id == '" + QString::number(user_id) + "')";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        return result.value(0).toInt();
    }
    return -1; //failed*/
}

int getWorkoutFrequency(int user_id){
    int workoutNum = getTotalNumOfWorkouts(user_id);
    int dayNum = getFirstToLastWorkout(user_id);

    if(workoutNum < 0){
        return -1;  //workoutNum failure.
    }
    if(dayNum < 0){
        return -1;  //dayNum failure.
    }

    if (dayNum > 0){  //avoid divide by zero errors.
        return workoutNum/dayNum;
    }
    return -1; //failed*/
}

int getTotalNumOfSets(int user_id){
    QString command = "SELECT count(*) FROM exercise_set_log WHERE user_id == '" + QString::number(user_id) + "')";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        return result.value(0).toInt();
    }
    return -1; //failed*/
}

int getAvgSetsPerWorkout(int user_id){
    int setNum = getTotalNumOfSets(user_id);
    int workoutNum = getTotalNumOfWorkouts(user_id);

    if(setNum < 0){
        return -1; //setNum failed.
    }
    if(workoutNum < 0){
        return -1; //workoutNum failed.
    }

    if(workoutNum > 0) {  //avoid divide by zero problems.
        return setNum/workoutNum;
    }
    return -1; //failed*/
}

int getAvgRepsPerSet(int user_id){
    int setNum = getTotalNumOfSets(user_id);
    if (setNum < 0){
        return -1;  //setNum failure.
    }
    QString command = "SELECT SUM(reps) FROM exercise_set_log WHERE user_id == '" + QString::number(user_id) + "')";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        if(setNum > 0){  //avoid divide by zero error
            return (result.value(0).toInt())/setNum;
        }
    }
    return -1; //failed*/
}
