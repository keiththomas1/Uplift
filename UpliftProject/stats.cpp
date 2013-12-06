#include "BusinessLayer.h"

///Gets the date of the first workout performed by a user
///\param user_id the current user
QString BusinessTier::getFirstWorkoutDate(int user_id){
    QString command = "SELECT datetime((SELECT time FROM workout_log WHERE user_id == '" + QString::number(user_id) + "' ORDER BY time DESC LIMIT 1), 'unixepoch', 'localtime')";
    QSqlQuery result = dt->executeQuery(command);
    if (result.next()) {
        return ((result.value(0).toString()));
    }
    //return -1; //failed*/
}

///Gets the date of the last workout performed by a user
///\param user_id the current user
QString BusinessTier::getLastWorkoutDate(int user_id){
    QString command = "SELECT datetime((SELECT time FROM workout_log WHERE user_id == '" + QString::number(user_id) + "' ORDER BY time ASC LIMIT 1), 'unixepoch', 'localtime')";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return ((result.value(0).toString()));
    }
    //return -1; //failed*/
}
//!Gets the time in days from the first to most recent workout.  Returns -1 on fail.
//!\param user_id this tracks the current user.
int BusinessTier::getFirstToLastWorkout(int user_id){
    QString command = "SELECT (SELECT time FROM workout_log WHERE user_id == '" + QString::number(user_id) + "' ORDER BY time DESC LIMIT 1) - (SELECT time FROM workout_log WHERE user_id == '" + QString::number(user_id) + "' ORDER BY time ASC LIMIT 1)";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return ((result.value(0).toInt())/60/60/24);
    }
    return -1; //failed*/
}
//!Gets the total number of workouts for a user.  Returns -1 on fail.
//!\param user_id this tracks the current user.
int BusinessTier::getTotalNumOfWorkouts(int user_id){
    QString command = "SELECT count(*) FROM workout_log WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        return result.value(0).toInt();
    }
    return -1; //failed*/
}
//!Gets the frequency of workouts per day for a user.  Returns -1 on fail.
//!\param user_id this tracks the current user.
int BusinessTier::getWorkoutFrequency(int user_id){
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
//!Gets the total number of sets for a user.  Returns -1 on fail.
//!\param user_id this tracks the current user.
int BusinessTier::getTotalNumOfSets(int user_id){
    QString command = "SELECT count(*) FROM exercise_set_log WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        return result.value(0).toInt();
    }
    return -1; //failed*/
}

//!Gets the average sets per workout a user has done.  Returns -1 on fail.
//!\param user_id this tracks the current user.
int BusinessTier::getAvgSetsPerWorkout(int user_id){
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

//!Gets the total number of reps completed in the lifetime of a user.
//!\param user_id the current user
int BusinessTier::getTotalNumOfReps(int user_id){
    QString command = "SELECT SUM(reps) FROM exercise_set_log WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        return result.value(0).toInt();
    }
    return -1;  //failed*/
}
//!Gets the average reps per set for a user.  Returns -1 on fail.
//!\param user_id this tracks the current user.
int BusinessTier::getAvgRepsPerSet(int user_id){
    int setNum = getTotalNumOfSets(user_id);
    int repNum = getTotalNumOfReps(user_id);
    if (setNum < 0){
        return -1;  //setNum failure.
    }
    if(repNum < 0){
        return -1;  //repNum failure.
    }
    if(setNum > 0){  //avoid divide by zero error
        return repNum/setNum;
    }
    return -1; //failed*/
}

//!Gets the total weight lifted in the lifetime of a user
//!\param user_id the current user
int BusinessTier::getTotalWeight(int user_id){
    QString command = "SELECT SUM(weight) FROM exercise_set_log WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()){
        return (result.value(0).toInt());
    }
    return -1;  //failed*/
}

///Gets the avg volume per workout over the lifetime of a user
///\param user_id the current user
int BusinessTier::getAvgVolumePerWorkout(int user_id){

    int workoutNum = getTotalNumOfWorkouts(user_id);
    if(workoutNum < 0){  //workoutNum failure
        return -1;
    }
    if(workoutNum == 0){
        return 0;
    }
    int workoutVolTotal = 0;
    QString command = "SELECT weight, reps FROM exercise_set_log WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    while(result.next()){
        workoutVolTotal += ((result.value(0).toInt())*(result.value(1).toInt()));
    }
    return workoutVolTotal/workoutNum;

    return -1; //failed*/
}

///Gets the total workout volume (weight*reps) for a specific workout instance
///\param workout_instance_id the id of the workout instance
int BusinessTier::GetWorkoutVolume(int workout_instance_id) {
    QString command = "SELECT weight, reps FROM exercise_set_log WHERE workout_instance_id == "
            + QString::number(workout_instance_id);
    QSqlQuery result = dt->executeQuery(command);

    int workoutVolume = 0;
    int tmp1, tmp2;
    while (result.next()) {
        tmp1 = result.value(0).toInt();
        tmp2 =result.value(1).toInt();
        workoutVolume += (tmp1*tmp2);
    }
    return workoutVolume;

}
