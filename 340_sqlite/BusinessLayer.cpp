#include <iostream>
#include <string.h>
#include <string>
#include <QString>
#include <QtSql>

//gets the workout_name_id from the name
//returns -1 for error

int GetWorkoutNameID(string name) {
    string query = "SELECT workout_name_id FROM workout_table WHERE workout_name == " + name;
}
//gets the exercise_name_id from the name
//returns -1 for error
int GetExerciseNameID(string name) {
    string query = "SELECT exercise_name_id FROM exercise_table WHERE exercise_name == " + name;
}
//returns true if the exercise already exists
bool DoesExerciseExist(string name) {
    if (GetExerciseNameID(name) < 0) {
        return false;
    }
    else return true;
}
//returns true if the workout already exists
bool DoesWorkoutExist(string name) {
    if (GetWorkoutNameID(name) < 0) {
        return false;
    }
    else return true;
}
//add an exercise to the exercise table
int AddExercise(Exercise*) {

}
//add a workout to the workout table
int AddWorkout(Workout*) {

}
//add a user to the user table
int AddUser(User*) {

}
//adds an exercise_set to the exercise_set_log
int AddSet(Exercise_Set*) {

}
int ModifySet(); //not sure how to implement this

/***************** CONVERSIONS ********************/

//NEED TO KNOW WHAT TYPE OF OBJECT WILL BE RETURNED FROM DB
List <Workout> ConvertToWorkoutList();
List <Exercise_Set> ConvertToExerciseList();
List <string> ConverToStringList();

/***************** STATISTICS ********************/


//returns a list of all occurences of a specified workout
List <Workout> GetWorkoutHistory(string name) {
    int name_id = GetWorkoutNameID(name);
    string query = "SELECT * FROM workout_log WHERE workout_name_id == " + name_id;
    //result = ExecuteQuery(query);
    List <Workout> = ConvertToWorkoutList();
}

//returns a list of all sets performed of a specified exercise
List <Exercise_Set> GetExerciseHistory(string name) {
    int name_id = GetExerciseNameID(name);
    string query = "SELECT * FROM exercise_set_log WHERE exercise_name_id == " + name_id;
    //result = ExecuteQuery(query);
    List <Exercise_Set> = ConvertToExerciseList();

}

//returns a list of all exercises
List <string> DisplayExercises() {

}

//returns a list of all workouts
List <string> DisplayWorkouts() {

}
