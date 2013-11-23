//  TODO:
//  Are QSqlQuery objects automatically destructed?
//  How do we tell if an insert failed?
#include "BusinessLayer.h"

using namespace std;

//gets the workout_name_id from the name
//returns -1 for error
int BusinessTier::GetWorkoutNameID(QString name) // DONE
{
    QString command = "SELECT workout_name_id FROM workout_table WHERE workout_name == '" + name + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed
}
//gets the exercise_name_id from the name
//returns -1 for error
int BusinessTier::GetExerciseNameID(QString name) // DONE
{
    QString command = "SELECT exercise_name_id FROM exercise_table WHERE exercise_name == '" + name + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed
}
//returns true if the exercise already exists
bool BusinessTier::DoesExerciseExist(QString name) // DONE
{
    if (GetExerciseNameID(name) < 0) {
        //qDebug() << "exerciseNameID doesn't exist";
        return false;
    }
    else {
        //qDebug() << "exerciseNameID exists";
        return true;
    }
}
//returns true if the workout already exists
bool BusinessTier::DoesWorkoutExist(QString name) // DONE
{
    if (GetWorkoutNameID(name) < 0) {
        //qDebug() << "workoutNameID doesn't exists";
        return false;
    }
    //qDebug() << "workoutNameID exists";
    else return true;
}
//adds an exercise to the exercise table
//returns 0 if already exists, and 1 on success
//TODO: how to tell if it failed?
int BusinessTier::AddExercise(QString name) // PENDING TODO
{
    if (DoesExerciseExist(name)) return 0;

    //if it doesn't already exist, add it
    int id = m_NextExerciseNameID++;
    QString command = "INSERT INTO exercise_table VALUES (" + QString::number(id) + ", '" + name + "')";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//add a workout to the workout table
//TODO: how to tell if it failed?
int BusinessTier::AddWorkout(QString name) // PENDING TODO
{
    if (DoesWorkoutExist(name)) return 0;

    //if id doesn't already exist, add it
    int id = m_NextWorkoutNameID++;
    QString command = "INSERT INTO workout_table VALUES (" + QString::number(id) + ", '" + name + "')";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}
/*
//add a user to the user table
int BusinessTier::AddUser(User*)
{
    return 0;
}
//adds an exercise_set to the exercise_set_log
int BusinessTier::AddSet(Exercise_Set*)
{
    return 0;
}
int BusinessTier::ModifySet()
{
    //not sure how to implement yet
}

/***************** CONVERSIONS ********************/

//NEED TO KNOW WHAT TYPE OF OBJECT WILL BE RETURNED FROM DB
list <Workout> ConvertToWorkoutList();
list <Exercise_Set> ConvertToExerciseList();
list <QString> ConverToStringList();

/***************** STATISTICS ********************/

/*
//returns a list of all occurences of a specified workout
list <Workout> GetWorkoutHistory(QString name) {
    int name_id = GetWorkoutNameID(name);
    //QString query = "SELECT * FROM workout_log WHERE workout_name_id == " + name_id;
    //result = ExecuteQuery(query);
    list <Workout> workoutHistoryList = ConvertToWorkoutList();
}

//returns a list of all sets performed of a specified exercise
list <Exercise_Set> GetExerciseHistory(QString name) {
    int name_id = GetExerciseNameID(name);
    //QString query = "SELECT * FROM exercise_set_log WHERE exercise_name_id == " + name_id;
    //result = ExecuteQuery(query);
    list <Exercise_Set> exerciseHistoryList = ConvertToExerciseList();

}

//returns a list of all exercises
list <QString> DisplayExercises() {

}

//returns a list of all workouts
list <QString> DisplayWorkouts() {

}
*/
