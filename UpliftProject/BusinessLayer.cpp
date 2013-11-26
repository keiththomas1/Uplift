//  TODO:
//  Are QSqlQuery objects automatically destructed?
//  How do we tell if an insert failed?
#include "BusinessLayer.h"

using namespace std;

//gets the workout_name_id from the name
//returns -1 for error
//!This function retrieves the id of the workout for other database queries.
//!/param name This string is the name of the corresponding workout.
int BusinessTier::GetWorkoutNameID(QString name) // DONE
{
    QString command = "SELECT rowid FROM workout_table WHERE workout_name == '" + name + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed
}
//gets the exercise_name_id from the name
//returns -1 for error
//!This funciton retrieves the id of the exercise for other database queries.
//!/param name This string represents the name of the exercise.
int BusinessTier::GetExerciseNameID(QString name) // DONE
{
    QString command = "SELECT rowid FROM exercise_table WHERE exercise_name == '" + name + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed
}
QStringList BusinessTier::GetExercisesInWorkout(QString workoutName)
{
    QString command = "SELECT exercise_name FROM workout_pairs WHERE workout_name == '" + workoutName + "'";
    QSqlQuery result = dt->executeQuery(command);
    QStringList exercisesList;
    while (result.next()) {
        exercisesList << result.value(0).toString();
    }
    return exercisesList;

}

void BusinessTier::UpdateWorkout(QString oldName, QString newName)
{
    QString command = "UPDATE workout_table "
            "SET workout_name='" + newName + "' "
            "WHERE workout_name='" + oldName + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
}
void BusinessTier::UpdateExercise(QString oldName, QString newName)
{
    //qDebug() << "oldName: " + oldName;
    //qDebug() << "newName: " + newName;
    QString command = "UPDATE exercise_table "
            "SET exercise_name='" + newName + "' "
            "WHERE exercise_name='" + oldName + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
}

//!This function retrieves the id of the user for other database queries.
//!/param username This string represents the username.
int BusinessTier::GetUserID(QString username)
{
    QString command = "SELECT rowid FROM user_table WHERE username == '" + username + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed

}

//returns true if the exercise already exists
//!This function checks to see if an exercise exists and returns a boolean value.
//!/param name This string represents the name of the exercise.
bool BusinessTier::DoesExerciseExist(QString name) // DONE
{
    int ID = GetExerciseNameID(name);
    //qDebug() << "name: " << name << "ID: " << ID;
    if (ID < 0) {
        //qDebug() << "exerciseNameID doesn't exist";
        return false;
    }
    else {
        //qDebug() << "exerciseNameID exists";
        return true;
    }
}
//returns true if the workout already exists
//!This function checks to see if a workout exists before adding it to the databse, and returns a boolean value.
//!/param name This represents the workout that is to be added to the database.
bool BusinessTier::DoesWorkoutExist(QString name) // DONE
{
    if (GetWorkoutNameID(name) < 0) {
        //qDebug() << "workoutNameID doesn't exists";
        return false;
    }
    //qDebug() << "workoutNameID exists";
    return true;
}
bool BusinessTier::DoesPairExist(QString workoutName, QString exerciseName)
{
    QString command = "SELECT exercise_name FROM workout_pairs WHERE workout_name == '" + workoutName + "' AND exercise_name == '" + exerciseName + "'";
    QSqlQuery result = dt->executeQuery(command);
    if (result.next()) return true;
    return false;
}

//!This function checks to see if a user exists for login or addition purposes and returns a boolean value.
//!/param username This string represents the desired or login username.
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
//!This function adds a new exercise to the database and returns an int: 1 success, 0 if already exists.
//!/param name This string represents the name of the exercise to be added to the database.
int BusinessTier::AddExercise(QString name) // PENDING TODO
{
    if (DoesExerciseExist(name)) return 0;

    //if it doesn't already exist, add it
    //int id = m_NextExerciseNameID++;
    QString command = "INSERT INTO exercise_table VALUES (NULL, \"" + name + "\")";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}
//IN PROGRESS: waiting on GetID to work
int BusinessTier::AddSet(int currUserID, int currWorkoutID, int weight, int reps)
{
    QString command = "INSERT INTO exercise_set_log VALUES (NULL, " +
           QString::number(currUserID) + ", " + QString::number(currWorkoutID) +
            ", NULL, " + QString::number(reps) + ", " + QString::number(weight) + ")";
    qDebug() << "Addset: " << command;
}

//add a workout to the workout table
//TODO: how to tell if it failed?
//!This function adds a new workout to the database and returns an int: 1 on success, 0 on already exists.
//!/param name This string represents the name of the workout to be added to the database.
int BusinessTier::AddWorkout(QString name) // PENDING TODO
{
    if (DoesWorkoutExist(name)) return 0;

    //if id doesn't already exist, add it
    //int id = m_NextWorkoutNameID++;
    QString command = "INSERT INTO workout_table VALUES (NULL, \"" + name + "\")";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}
//IN PROGRESS: waiting on GetID to work
//TODO: make sure the workoutPair doesn't already exist
int BusinessTier::AddWorkoutPair(QString workoutName, QString exerciseName, int workoutOrder)
{
    if (DoesPairExist(workoutName, exerciseName)) return 0;
    QString command = "INSERT INTO workout_pairs VALUES ('" + workoutName + "', '" + exerciseName + "', NULL)";
    //qDebug() << "AddWorkoutPair: " << command;
    QSqlQuery result = dt->executeQuery(command);
}

//add a user to the user table
//!This function adds a user to the database and returns an int: 1 on success, 0 on already exists.
//!/param username This is the username to be added.
//!/param password This is the new user's desired password.
int BusinessTier::AddUser(QString username, QString password)
{
    if (DoesUserExist(username)) return 0;

    //if user doesn't exist, add them
    //int id = m_NextUserID++;
    //QString command = "INSERT INTO user_table VALUES (" + QString::number(id) + ", '" + username + "', '" + password + "')";
    QString command = "INSERT INTO user_table VALUES (NULL, \"" + username + "\", \"" + password + "\")";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function removes an exercise from the database, and returns an int: 1 on success, 0 on already exists.
//!/param name This string represents the name of the exercise to be removed.
int BusinessTier::RemoveExercise(QString name)
{
    if (!DoesExerciseExist(name)) return 0; //can't remove, doesn't exist

    //if it exists, remove it
    QString command = "DELETE FROM exercise_table WHERE exercise_name == \"" + name + "\"";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function removes a workout from the database.
//!/param name This string represents the name of the workout.
int BusinessTier::RemoveWorkout(QString name)
{
    if (!DoesWorkoutExist(name)) return 0; //can't remove, doesn't exist

    //if it exists, remove it
    QString command = "DELETE FROM workout_table WHERE workout_name == \"" + name + "\"";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

int BusinessTier::RemoveWorkoutPair(QString workoutName, QString exerciseName)
{
    if (!DoesPairExist(workoutName, exerciseName)) return 0;
    QString command = "DELETE FROM workout_pairs WHERE workout_name == '" + workoutName + "' AND exercise_name == '" + exerciseName + "'";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function removes a user from the database and returns an int: 1 on successful removal, 0 on failure.
//!/param username This string contains the username to be removed.
//!/param password This string contains the password to be removed.
int BusinessTier::RemoveUser(QString username, QString password)
{
    //TODO: temporarly store the user_id number, so all of his info can be killed off from the other tables.
    //TODO: create commands which kill off the deleted user's stats from the other tables.

    if (!DoesUserExist(username)) return 0; //can't remove, doesn't exist

    //if user exists, remove them
    QString command = "DELETE FROM user_table WHERE username == \"" + username + "\" AND password == \"" + password + "\"";
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
//!This function retreives the workout list from the database for display, and returns a QStringList object.
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

//!This function retreives the exercise list from the database for display, and returns a QStringList object.
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

//This function is defunct.
//!This function was once used for managing a separate primary key management table, which was replaced with better functionality.
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

void BusinessTier::CloseDB() {
    dt->closeDatabase();
}
