#ifndef BUSINESSLAYER_H
#define BUSINESSLAYER_H
#include <ctime>
using namespace std;

class BusinessTier
{
public:
    BusinessTier()  //should only be called once
    {
        m_NextWorkoutID = 0;
        m_NextWorkoutNameID = 0;
        m_NextExerciseID = 0;
        m_NextExerciseSetID = 0;
        m_NextExerciseNameID = 0;
        m_NextUserID = 0;
    }
    virtual ~BusinessTier() {}

    //ID management
    int GetNextWorkoutID()      { return m_NextWorkoutID++;}
    int GetNextWorkoutNameID()  { return m_NextWorkoutNameID++;}
    int GetNextExerciseID()     { return m_NextExerciseID++;}
    int GetNextExerciseSetID()  { return m_NextExerciseSetID++;}
    int GetNextExerciseNameID() { return m_NextExerciseNameID++;}
    int GetNextUserID()         { return m_NextUserID++;}

    int GetTime()               { return (int)time(NULL);}
    int AddExercise(Exercise*);
    int AddWorkout(Workout*);
    int AddUser(User*);
    int AddSet(Exercise_Set*);
    int ModifySet(); //not sure how to implement this
    List <Workout> GetWorkoutHistory(string);
    List <Exercise_Set> GetExercise(string);
    List <string> DisplayExercises();
    List <string> DisplayWorkouts();

private:
    int m_NextWorkoutID;
    int m_NextWorkoutNameID;
    int m_NextExerciseID;
    int m_NextExerciseSetID;
    int m_NextExerciseNameID;
    int m_NextUserID;

    bool DoesExerciseExist(string);
    bool DoesWorkoutExist(string);
    int GetWorkoutNameID(string);

    //all take some sqlobject param
    List <Workout> ConvertToWorkoutList();
    List <Exercise_Set> ConvertToExerciseList();
    List <string> ConverToStringList();
};


#endif // BUSINESSLAYER_H
