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

int BusinessTier::GetUserID(QString username)
{
    QString command = "SELECT user_id FROM user_table WHERE username == '" + username + "'";
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
    return true;
}

bool BusinessTier::DoesUserExist(QString username)
{
    if (GetUserID(username) < 0) {
        return false;
    }
    return true;
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

//add a user to the user table
int BusinessTier::AddUser(QString username, QString password)
{
    if (DoesUserExist(username)) return 0;

    //if user doesn't exist, add them
    int id = m_NextUserID++;
    QString command = "INSERT INTO user_table VALUES (" + QString::number(id) + ", '" + username + "', '" + password + "')";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

int BusinessTier::RemoveExercise(QString name)
{
    if (!DoesExerciseExist(name)) return 0; //can't remove, doesn't exist

    //if it exists, remove it
    QString command = "DELETE FROM exercise_table WHERE exercise_name == '" + name + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

int BusinessTier::RemoveWorkout(QString name)
{
    if (!DoesWorkoutExist(name)) return 0; //can't remove, doesn't exist

    //if it exists, remove it
    QString command = "DELETE FROM workout_table WHERE workout_name == '" + name + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

int BusinessTier::RemoveUser(QString username, QString password)
{
    if (!DoesUserExist(username)) return 0; //can't remove, doesn't exist

    //if user exists, remove them
    QString command = "DELETE FROM user_table WHERE username == '" + username + "' AND password == '" + password + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

/*
//adds an exercise_set to the exercise_set_log
int BusinessTier::AddSet(Exercise_Set*)
{
    return 0;
}
int BusinessTier::ModifySet()
{
    //not sure how to implement yet
}
*/

/***************** LISTS ********************/
QStringList BusinessTier::GetWorkoutList()  //DO I NEED TO FREE LIST OBJECT SOMEWHERE?
{
    QString command = "SELECT workout_name FROM workout_table";
    QSqlQuery result = dt->executeQuery(command);
    QStringList workoutList;
    while (result.next()) {
        workoutList << result.value(0).toString();
    }
    //qDebug() << workoutList;
    return workoutList;

}
QStringList BusinessTier::GetExerciseList() //DO I NEED TO FREE LIST OBJECT SOMEWHERE?
{
    QString command = "SELECT exercise_name FROM exercise_table";
    QSqlQuery result = dt->executeQuery(command);
    QStringList exerciseList;
    while (result.next()) {
        exerciseList << result.value(0).toString();
    }
    //qDebug() << exerciseList;
    return exerciseList;

}
void BusinessTier::StoreIDs() {
    //qDebug() << "m_NextWorkoutNameID: " << m_NextWorkoutNameID;
    //qDebug() << "m_NextExerciseNameID: " << m_NextExerciseNameID;
    dt->StoreIDs(m_NextWorkoutID, m_NextWorkoutNameID, m_NextExerciseID,
                 m_NextExerciseSetID, m_NextExerciseNameID, m_NextUserID);
}

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
