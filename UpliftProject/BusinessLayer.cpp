//  TODO:
//  Are QSqlQuery objects automatically destructed?
//  How do we tell if an insert failed?

#include "BusinessLayer.h"

using namespace std;

//!This function retrieves the id of the workout for other database queries.
//!/param name This string is the name of the corresponding workout.
int BusinessTier::GetWorkoutNameID(QString name, int user_id) // DONE
{
    QString command = "SELECT workout_name_id FROM workout_table WHERE workout_name == '" + name + "' AND user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed
}

//!This funciton retrieves the id of the exercise for other database queries.
//!/param name This string represents the name of the exercise.
int BusinessTier::GetExerciseNameID(QString name, int user_id) // DONE
{
    QString command = "SELECT exercise_name_id FROM exercise_table WHERE exercise_name == '" + name + "' AND user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed
}

//!This function returns a list of exercises that belong to the user specified workout.
//!/param workoutName This string is the name of the specific workout the exercises exist in.
QStringList BusinessTier::GetExercisesInWorkout(QString workoutName, int user_id)
{
    int workout_id = GetWorkoutNameID(workoutName, user_id);
    QString command = "SELECT exercise_name "
                      "FROM workout_pairs as p JOIN exercise_table as e "
                      "ON p.exercise_id=e.exercise_name_id "
                      "WHERE p.workout_id == \"" + QString::number(workout_id) + "\" "
                      "AND e.user_id == \"" + QString::number(user_id) + "\"";
    QSqlQuery result = dt->executeQuery(command);
    QStringList exercisesList;
    while (result.next()) {
        exercisesList << result.value(0).toString();
    }
    return exercisesList;

}

//!This function changes the name of the workout upon request.
//!/param oldName This string represents the old workout name.
//!/param newMan This string represents the name to which the workout is being changed.
void BusinessTier::UpdateWorkout(QString oldName, QString newName, int user_id)
{
    QString command = "UPDATE workout_table "
            "SET workout_name='" + newName + "' "
            "WHERE workout_name='" + oldName + "'"
            "AND user_id='" + QString::number(user_id) + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
}

//!This function updates the name of the exercise.
//!/param oldName This string represents the old exercise name.
//!/param newMan This string represents the name to which the exercise is being changed.
void BusinessTier::UpdateExercise(QString oldName, QString newName, int user_id)
{
    //qDebug() << "oldName: " + oldName;
    //qDebug() << "newName: " + newName;
    QString command = "UPDATE exercise_table "
            "SET exercise_name='" + newName + "' "
            "WHERE exercise_name='" + oldName + "' "
            "AND user_id='" + QString::number(user_id) + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
}

//!This function retrieves the id of the user for other database queries.
//!/param username This string represents the username.
int BusinessTier::GetUserID(QString username)
{
    QString command = "SELECT user_id FROM user_table WHERE username == '" + username + "'";
    QSqlQuery result = dt->executeQuery(command);

    if (result.next()) {
        return result.value(0).toInt();
    }
    return -1; //failed

}

//!This function checks to see if an exercise exists and returns a boolean value - true if exercise exists.
//!/param name This string represents the name of the exercise.
bool BusinessTier::DoesExerciseExist(QString name, int user_id) // DONE
{
    int ID = GetExerciseNameID(name, user_id);
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
bool BusinessTier::DoesWorkoutExist(QString name, int user_id) // DONE
{
    if (GetWorkoutNameID(name, user_id) < 0) {
        return false;
    }
    return true;
}

//!This function checks to see if an exercise pair and workout exists in the pair table.  It returns a boolean value.
//!/param workoutName This string represents the name of the workout.
//!/param exerciseName This string represents the name of the exercise.
bool BusinessTier::DoesPairExist(QString workoutName, QString exerciseName, int user_id)
{
    int workout_name_id = GetWorkoutNameID(workoutName, user_id);
    int exercise_name_id = GetExerciseNameID(exerciseName, user_id);
    QString command = "SELECT workout_id FROM workout_pairs WHERE workout_id == " + QString::number(workout_name_id) + " AND exercise_id == " + QString::number(exercise_name_id) + "";
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

//!This function adds a new exercise to the database and returns an int: 1 success, 0 if already exists.
//!/param name This string represents the name of the exercise to be added to the database.
int BusinessTier::AddExercise(QString name, int user_id)
{
    if (DoesExerciseExist(name, user_id)) return 0;
    QString command = "INSERT INTO exercise_table VALUES (NULL, '" + name + "', '" + QString::number(user_id) + "')";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function logs a set of an exercise within a workout for a specific user
//!/param userID int holding the user ID of the user performing the set
//!/param workout string holding the name of the workout the exercise is part of
//!/param exercise string holding the name of the exercise the user is logging a set of
//!/param reps int holding the number of repetitions performed of the exercise
//!/param weight int holding the weight per repetition of the exercise
int BusinessTier::AddSet(int user_id, QString workout, QString exercise, int reps, int weight)
{
    int workout_name_id = GetWorkoutNameID(workout, user_id);
    int exercise_name_id = GetExerciseNameID(exercise, user_id);
    int max = OneRepMax(reps, weight);
    QString command = "INSERT INTO exercise_set_log (set_id, workout_id, exercise_id, user_id, reps, weight, one_rep_max) "
            "VALUES (NULL, " + QString::number(workout_name_id) + ", " + QString::number(exercise_name_id) + ", " + QString::number(user_id) +
            ", " + QString::number(reps) + ", " + QString::number(weight) + ", " + QString::number(max) + ")";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}


//!This function adds a new workout to the database and returns an int: 1 on success, 0 on already exists.
//!/param name This string represents the name of the workout to be added to the database.
int BusinessTier::AddWorkout(QString name, int user_id)
{
    if (DoesWorkoutExist(name, user_id)) return 0;
    QString command = "INSERT INTO workout_table VALUES (NULL, '" + name + "', '" + QString::number(user_id) + "')";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function adds an exercise to a specific workout (if it doesn't already exist in the workout)
//!/param workoutName string containing the name of the workout the exercise is being added to
//!/param exerciseName string containing the name of the exercise to be added to the workout
//!/param order an integer containing the order the exercise should appear in the workout
int BusinessTier::AddWorkoutPair(QString workoutName, QString exerciseName, int user_id, int)  //don't know what last parameter is for.
{
    int workout_name_id = GetWorkoutNameID(workoutName, user_id);
    int exercise_name_id = GetExerciseNameID(exerciseName, user_id);
    if (DoesPairExist(workoutName, exerciseName, user_id)) return 0;
    QString command = "INSERT INTO workout_pairs "
                      "VALUES (" + QString::number(workout_name_id) + ", " + QString::number(exercise_name_id) + ", 999)";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

void BusinessTier::AddWorkoutLog(QString workoutName, int userID) {
    int workoutNameID = GetWorkoutNameID(workoutName, userID);
    QString command = "INSERT INTO workout_log (user_id, workout_name_id) "
            "VALUES (" + QString::number(userID) + ", " + QString::number(workoutNameID) + ")";
    //qDebug() << command;
    dt->executeQuery(command);
}

//!This function adds a user to the database and returns an int: 1 on success, 0 on already exists.
//!/param username This is the username to be added.
//!/param password This is the new user's desired password.
int BusinessTier::AddUser(QString username, QString password)
{
    if (DoesUserExist(username)) return 0;
    QString command = "INSERT INTO user_table VALUES (NULL, '" + username + "', '" + password + "')";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function removes an exercise from the database, and returns an int: 1 on success, 0 on already exists.
//!/param name This string represents the name of the exercise to be removed.
int BusinessTier::RemoveExercise(QString name, int user_id)
{
    if (!DoesExerciseExist(name, user_id)) return 0; //can't remove, doesn't exist
    QString command = "DELETE FROM exercise_table WHERE exercise_name == \"" + name + "\" AND user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function removes a workout from the database.
//!/param name This string represents the name of the workout.
//NEEDS TO CHECK FOR USER ID.
int BusinessTier::RemoveWorkout(QString name, int user_id)
{
    if (!DoesWorkoutExist(name, user_id)) return 0; //can't remove, doesn't exist
    QString command = "DELETE FROM workout_table WHERE workout_name == \"" + name + "\" AND user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);
    return 1;
}

//!This function removes an exercise from a workout
//!/param workoutName string that holds the name of the workout to remove the exercise from
//!/param exerciseName string that holds the name of the exercise to remove from the workout
int BusinessTier::RemoveWorkoutPair(QString workoutName, QString exerciseName, int user_id)
{
    int workout_name_id = GetWorkoutNameID(workoutName, user_id);
    int exercise_name_id = GetExerciseNameID(exerciseName, user_id);
    if (!DoesPairExist(workoutName, exerciseName, user_id)) return 0;
    QString command = "DELETE FROM workout_pairs WHERE workout_id == '" + QString::number(workout_name_id) + "' AND exercise_id == '" + QString::number(exercise_name_id) + "'";
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
    //TODO: create commands which kill off the deleted user's exercises and workouts from the other tables.

    if (!DoesUserExist(username)) return 0; //can't remove, doesn't exist
    int user_id = GetUserID(username);

    //delete all of their stuff;

    //workout_pairs
    QString command = "SELECT exercise_name_id FROM exercise_table WHERE user_id == \"" + QString::number(user_id) + "\" GROUP BY exercise_name_id";
    QSqlQuery result = dt->executeQuery(command);
    while(result.next()) {
        QString deleteExerciseCommand = "DELETE FROM workout_pairs WHERE exercise_id == \"" + QString::number(result.value(0).toInt()) + "\"";
        dt->executeQuery(deleteExerciseCommand);
    }
    command = "SELECT workout_name_id FROM workout_table WHERE user_id == \"" + QString::number(user_id) + "\" GROUP BY workout_name_id";
    result = dt->executeQuery(command);
    while(result.next()) {
        QString deleteWorkoutCommand = "DELETE FROM workout_pairs WHERE workout_id == \"" + QString::number(result.value(0).toInt()) + "\"";
        dt->executeQuery(deleteWorkoutCommand);
    }

    //exercise_table
    command = "DELETE FROM exercise_table WHERE user_id == \"" + QString::number(user_id) + "\"";
    result = dt->executeQuery(command);
    //workout_table
    command = "DELETE FROM workout_table WHERE user_id == \"" + QString::number(user_id) + "\"";
    result = dt->executeQuery(command);
    //workout_log
    command = "DELETE FROM workout_log WHERE user_id == \"" + QString::number(user_id) + "\"";
    result = dt->executeQuery(command);
    //exercise_set_log
    command = "DELETE FROM exercise_set_log WHERE user_id == \"" + QString::number(user_id) + "\"";
    result = dt->executeQuery(command);

    //finally, kill off the user
    command = "DELETE FROM user_table WHERE username == \"" + username + "\" AND password == \"" + password + "\"";
    result = dt->executeQuery(command);

    return 1;
}


/***************** LISTS ********************/
//!This function retreives the workout list from the database for display, and returns a QStringList object.
QStringList BusinessTier::GetWorkoutList(int user_id)  //DO I NEED TO FREE LIST OBJECT SOMEWHERE?
{
    QString command = "SELECT workout_name FROM workout_table WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);
    QStringList workoutList;
    while (result.next()) {
        workoutList << result.value(0).toString();
    }
    //qDebug() << workoutList;
    return workoutList;

}

//!This function retreives the exercise list from the database for display, and returns a QStringList object.
QStringList BusinessTier::GetExerciseList(int user_id) //DO I NEED TO FREE LIST OBJECT SOMEWHERE?
{
    QString command = "SELECT exercise_name FROM exercise_table WHERE user_id == '" + QString::number(user_id) + "'";
    QSqlQuery result = dt->executeQuery(command);
    QStringList exerciseList;
    while (result.next()) {
        exerciseList << result.value(0).toString();
    }
    //qDebug() << exerciseList;
    return exerciseList;
}

//!This function returns a list holding the history of a specific exercise (date, weight, and reps)
//!/param exercise string holding the name of the exercise to retrieve history for
//!/param user_id int holding the user to get history for
//!/param sortBy string holding the column to sort by (date, reps, weight, 1RM)
QStringList BusinessTier::GetExerciseHistory(QString exercise, int user_id, QString sortBy)
{
    int exerciseID = GetExerciseNameID(exercise, user_id);
    QString command;
    if (sortBy == "date") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY time DESC" ;
    }
    else if (sortBy == "reps") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY reps DESC" ;
    }
    else if (sortBy == "weight") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY weight DESC" ;
    }
    else if (sortBy == "1RM") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY one_rep_max DESC" ;
    }
    QSqlQuery result = dt->executeQuery(command);
    QStringList historyList;
    QString name, weight, reps, date, oneRepMax;
    while (result.next()) {
        reps = result.value(1).toString();
        weight = result.value(2).toString();
        date = result.value(3).toString();
        oneRepMax = result.value(4).toString();

        historyList << date + "\t    " + weight + " x " + reps + "\t    " + oneRepMax + " (1RM)";
    }
    return historyList;
}

QStringList BusinessTier::GetWorkoutHistory(QString workout, int user_id){
    int workoutID = GetWorkoutNameID(workout, user_id);
    QString command;
    //if (sortBy == "date") {
        command = "SELECT workout_instance_id, t.workout_name, date(time, 'unixepoch', 'localtime') as datetime "
                  "FROM workout_log as w JOIN workout_table as t ON w.workout_name_id = t.workout_name_id "
                  "WHERE w.workout_name_id == '" + QString::number(workoutID) + "' AND w.user_id == '" + QString::number(user_id) + "'"
                  "ORDER BY time DESC";
    //}
    //more sorting options can go here.

    QSqlQuery result = dt->executeQuery(command);
    QStringList historyList;
    QString name, date;
    while (result.next()) {
        name = result.value(1).toString();
        date = result.value(2).toString();

        historyList << "Exercise Name: " + name + "\tDate:" + date;
    }
    return historyList;
}

/*
 * WORKOUT HISTORY FUNCTION
//TODO: get volume from specific workout
//!This function returns a list holding the history of a specific workout (date, weight, and reps)
//!/param exercise string holding the name of the workout to retrieve history for
//!/param user_id int holding the user to get history for
//!/param sortBy string holding the column to sort by (date, volume, sets)
QStringList BusinessTier::GetWorkoutHistory(QString exercise, int user_id, QString sortBy)
{
    int exerciseID = GetExerciseNameID(exercise, user_id);
    QString command;
    if (sortBy == "date") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY time DESC" ;
    }
    else if (sortBy == "reps") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY reps ASC" ;
    }
    else if (sortBy == "weight") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY weight ASC" ;
    }
    else if (sortBy == "1RM") {
        command = "SELECT exercise_id, reps, weight, date(time, 'unixepoch', 'localtime') as datetime, one_rep_max FROM exercise_set_log "
            "WHERE exercise_id == '" + QString::number(exerciseID) + "' AND user_id == '" + QString::number(user_id) + "' ORDER BY one_rep_max DESC" ;
    }
    QSqlQuery result = dt->executeQuery(command);
    QStringList historyList;
    QString name, weight, reps, date, oneRepMax;
    while (result.next()) {
        reps = result.value(1).toString();
        weight = result.value(2).toString();
        date = result.value(3).toString();
        oneRepMax = result.value(4).toString();

        historyList << date + "\t" + weight + " x " + reps + "\t" + oneRepMax + " (1RM)";
    }
    return historyList;
}
*/

//!This function returns a list of all usernames currently in the database
QStringList BusinessTier::GetUserList()
{
    QString command = "SELECT username FROM user_table";
    QSqlQuery result = dt->executeQuery(command);
    QStringList userList;
    while (result.next()) {
        userList << result.value(0).toString();
    }
    //qDebug() << userList;
    return userList;
}
//!This function returns an estimate one rep max for the given reps and weight
//!/param reps double holding the number of reps
//!/param weight double holding the weight
int BusinessTier::OneRepMax(double reps, double weight) {
     double max = weight * (1 + (reps/30));
     return (int)(max + 0.5); //+0.5 will properly round after truncate
}
bool BusinessTier::ValidateUser(QString user, QString pass) {
    QString command = "SELECT username FROM user_table WHERE"
            " username == '" + user + "' AND password == '" + pass + "'";
    //qDebug() << command;
    QSqlQuery result = dt->executeQuery(command);
    if (result.next()) return true;
    else return false;
}

//!This function closes the database connection
void BusinessTier::CloseDB() {
    dt->closeDatabase();
}

/***************** TESTING ********************/
//!This function validates the functionality by printing 'true' for all functions that perform as expected, 'false' otherwise
void BusinessTier::ValidateBusinessTier() {

    /* '//' MEANS TESTED BELOW, ELSE UNTESTED
    //int AddUser         (QString, QString);
    //int AddExercise     (QString);
    //int AddWorkout      (QString);
    //int AddWorkoutPair  (QString, QString, int order); // don't know why order is on here.
    int AddSet          (int userID, QString workout, QString exercise, int weight, int reps);

    //int GetWorkoutNameID(QString);
    //int GetExerciseNameID(QString);
    //int GetUserID(QString);
    //QStringList GetExercisesInWorkout(QString workoutName);
    QStringList GetExerciseHistory(QString exercise);
    //QStringList GetWorkoutList();
    //QStringList GetExerciseList();
    //QStringList GetUserList();

    //bool DoesExerciseExist(QString);
    //bool DoesWorkoutExist(QString);
    //bool DoesUserExist(QString);
    //bool DoesPairExist(QString, QString);
    //int RemoveExercise  (QString);
    //int RemoveWorkout   (QString);
    //int RemoveWorkoutPair (QString, QString);
    //int RemoveUser      (QString, QString);
    int RemoveSet();
    int ModifySet(); //not sure how to implement this
    //void UpdateWorkout   (QString, QString);
    //void UpdateExercise  (QString, QString);
    */


    //USER TESTS
    //AddUser()
    //GetUserID()
    //GetUserList()
    //DoesUserExist()
    bool userTest1 = false, userTest2 = false, userTest3 = false, userRemoveTest = false;
    AddUser("user1", "password1");
    AddUser("user2", "password2");
    QStringList userList = GetUserList();
    int userID = GetUserID("user2");
    if (userID > 0) userTest1 = true;
    if (userList.value(1) == "user2") userTest2 = true;
    userTest3 = DoesUserExist("user2");

    //test remove
    RemoveUser("user1", "password1");
    if (!RemoveUser("user1", "password1")) userRemoveTest = true;

    // EXERCISE TESTS
    //AddExercise()
    //GetExerciseNameID()
    //GetExerciseList()
    //DoesExerciseExist()
    bool exerTest1 = false, exerTest2 = false, exerTest3 = false, exerTest4 = false, removeExerciseTest = false;
    AddExercise("test_exercise1", 1);
    AddExercise("test_exercise2", 1);
    UpdateExercise("test_exercise1", "test_exercise3", 1);
    QStringList exerList = GetExerciseList(1);
    int exerID = GetExerciseNameID("test_exercise2", 1);
    if (exerID > 0) exerTest1 = true;
    if (exerList.value(1) == "test_exercise2") exerTest2 = true;
    if (exerList.value(0) == "test_exercise3") exerTest4 = true;
    exerTest3 = DoesExerciseExist("test_exercise2",1);


    //exercise remove
    RemoveExercise("test_exercise2",1);
    if (!RemoveExercise("test_exercise2",1)) removeExerciseTest = true;


    //  WORKOUT TESTS
    //AddWorkout()
    //GetWorkoutNameID()
    //GetWorkoutList()
    //DoesWorkoutExist()
    bool workoutTest1 = false, workoutTest2 = false, workoutTest3 = false, workoutTest4 = false, removeWorkoutTest = false;
    AddWorkout("test_workout1",1);
    AddWorkout("test_workout2",1);
    UpdateWorkout("test_workout1", "test_workout3",1);
    QStringList workoutList = GetWorkoutList(1);
    int workoutID = GetWorkoutNameID("test_workout2",1);
    if (workoutID > 0) workoutTest1 = true;
    if (workoutList.value(1) == "test_workout2") workoutTest2 = true; //add workout
    if (workoutList.value(0) == "test_workout3") workoutTest4 = true; //update workout
    workoutTest3 = DoesWorkoutExist("test_workout2",1);


    //workout remove
    RemoveWorkout("test_workout2",1);
    if (!RemoveWorkout("test_workout2",1)) removeWorkoutTest = true;


    // WORKOUT PAIRS TESTS
    bool pairTest1 = false, pairTest2 = false, pairRemoveTest = false;
    AddWorkout("workout_pair",1);
    AddExercise("exercise_pair",1);
    AddWorkoutPair("workout_pair", "exercise_pair",1,1);
    pairTest2 = DoesPairExist("workout_pair", "exercise_pair",1);
    QStringList pairsList = GetExercisesInWorkout("workout_pair",1);
    if (pairsList.value(0) == "exercise_pair") pairTest1 = true;

    RemoveWorkoutPair("workout_pair", "exercise_pair",1);
    if (!RemoveWorkoutPair("workout_pair", "exercise_pair",1)) pairRemoveTest = true;

    /*
    //set testing
    AddWorkout("set_workout");
    AddExercise("set_exercise");
    AddSet(0, "set_workout", "set_exercise", 999, 999);
    QStringList exerciseHistory = GetExerciseHistory("set_exercise");
    if (exerciseHistory.value(0) == )
    */

    //remove all added users, exercises, and workouts
    RemoveUser("user1", "password1");
    RemoveUser("user2", "password2");
    RemoveExercise("test_exercise1",1);
    RemoveExercise("test_exercise2",1);
    RemoveExercise("test_exercise3",1);
    RemoveExercise("exercise_pair",1);
    RemoveWorkout("test_workout1",1);
    RemoveWorkout("test_workout2",1);
    RemoveWorkout("test_workout3",1);
    RemoveWorkout("workout_pair",1);
    RemoveWorkoutPair("workout_pair", "exercise_pair",1);



    //print results
    qDebug() << "GetUserID:         " << userTest1;
    qDebug() << "AddUser:           " << userTest2;
    qDebug() << "DoesUserExist:     " << userTest3;
    qDebug() << "RemoveUser:        " << userRemoveTest;
    qDebug() << "GetExerciseNameID: " << exerTest1;
    qDebug() << "AddExercise:       " << exerTest2;
    qDebug() << "DoesExerciseExist: " << exerTest3;
    qDebug() << "UpdateExercise:    " << exerTest4;
    qDebug() << "RemoveExercise:    " << removeExerciseTest;
    qDebug() << "GetWorkoutNameID:  " << workoutTest1;
    qDebug() << "AddWorkout:        " << workoutTest2;
    qDebug() << "DoesWorkoutExist:  " << workoutTest3;
    qDebug() << "UpdateWorkout:     " << workoutTest4;
    qDebug() << "RemoveWorkout:    " << removeWorkoutTest;
    qDebug() << "AddWorkoutPair:    " << pairTest1;
    qDebug() << "DoesPairExist:     " << pairTest2;
    qDebug() << "RemoveWorkoutPair: " << pairRemoveTest;



}

