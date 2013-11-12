#ifndef COREDS_H
#define COREDS_H
#include "exercise.h"
#include <map>
typedef std::map<int, Exercise*> ExerciseIDMap;
typedef std::pair<int, Exercise*> ExerciseIDPair;
typedef std::map<string, Exercise*> ExerciseStringMap;
typedef std::pair<string, Exercise*> ExerciseStringPair;
typedef std::map<string, int> ExerciseNameIDMap;
typedef std::pair<string, int> ExerciseNameIDPair;

//typedef std::vector<Exercise*> ExerciseVector;

class CoreDS
{
public:
    CoreDS() :
        m_next_workout_id(0), m_next_exercise_id(0), m_next_exercise_name_id(0)
    {
    }
    virtual ~CoreDS() {}

    int GetNextWorkoutID() { return m_next_workout_id++;}
    int GetNextExerciseID() { return m_next_exercise_id++;}
    int GetNextExerciseNameID() { return m_next_exercise_name_id++;}
    int GetPrevExerciseNameID() { return m_next_exercise_name_id--;}
    void AddExercise(Exercise *ex);
    void AddToExercisesList(string name);
    Exercise* GetExercise(int ID);
    int GetExerciseIDFromName(string name);

    void PrintExerciseList();
    void PrintExerciseObjects();

    //Exercise* GetExercise(string name);
    //Exercise* GetExercise(int timestamp);

private:
    int m_next_workout_id;
    int m_next_exercise_id;
    int m_next_exercise_name_id;
    ExerciseIDMap m_exercise_id_map;
    ExerciseStringMap m_exercise_string_map;
    ExerciseNameIDMap m_exerciseName_id_map;
    //std::map<(timestamp), Exercise*> m_exercise_timestamp_map;

};

#endif // COREDS_H
