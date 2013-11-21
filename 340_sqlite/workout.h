#ifndef WORKOUT_H
#define WORKOUT_H
#include <string>
using namespace std;

class Workout
{
public:
    Workout(string p_WorkoutName, int p_WorkoutID) :
        m_WorkoutName(p_WorkoutName), m_WorkoutID(p_WorkoutID)
    {
    }
    virtual ~Workout() {}

    string GetWorkoutName() { return m_WorkoutName;}
    int GetWorkoutID()      { return m_WorkoutID;}
    int GetWorkoutTime()    { return m_Timestamp;}

private:
    string m_WorkoutName;
    int m_WorkoutID;
    int m_Timestamp;
};

#endif // WORKOUT_H
