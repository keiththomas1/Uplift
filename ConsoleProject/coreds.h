#ifndef COREDS_H
#define COREDS_H
#include "exercise.h"
#include <map>
typedef std::map<int, Exercise*> ExerciseIDMap;
typedef std::pair<int, Exercise*> ExerciseIDPair;
typedef std::map<string, Exercise*> ExerciseStringMap;
typedef std::pair<string, Exercise*> ExerciseStringPair;

class CoreDS
{
public:
    CoreDS() :
        m_next_workout_id(0), m_next_exercise_id(0)
    {
    }
    virtual ~CoreDS() {}

    int GetNextWorkoutID() { return m_next_workout_id++;}
    int GetNextExerciseID() { return m_next_exercise_id++;}
    void AddExercise(Exercise *ex);
    Exercise* GetExercise(int ID);

    void PrintExercises();


    //Exercise* GetExercise(string name);
    //Exercise* GetExercise(int timestamp);

private:
    int m_next_workout_id;
    int m_next_exercise_id;
    ExerciseIDMap m_exercise_id_map;
    ExerciseStringMap m_exercise_string_map;
    //std::map<(timestamp), Exercise*> m_exercise_timestamp_map;

};

#endif // COREDS_H
