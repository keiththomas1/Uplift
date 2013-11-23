#ifndef BUSINESSLAYER_H
#define BUSINESSLAYER_H
#include <ctime>
#include <vector>
#include <QString>
#include "exercise.h"
#include "exercise_set.h"
#include "workout.h"
#include "user.h"
#include "DataAccessLayer.h"

using namespace std;

class BusinessTier
{
public:
    BusinessTier()
    {
        dt = new DBaseMan();

        //seed all the ID counters with 0
        m_NextWorkoutID = 0;
        m_NextWorkoutNameID = 0;
        m_NextExerciseID = 0;
        m_NextExerciseSetID = 0;
        m_NextExerciseNameID = 0;
        m_NextUserID = 0;
    }
    virtual ~BusinessTier() {}

    int GetTime()               { return (int)time(NULL);}
    int AddExercise(QString);
    int AddWorkout(QString);
    int AddUser(User*);
    int AddSet(Exercise_Set*);
    int ModifySet(); //not sure how to implement this

    vector <Workout> GetWorkoutHistory(QString);
    vector <Exercise_Set> GetExercise(QString);
    vector <QString> DisplayExercises();
    vector <QString> DisplayWorkouts();
DBaseMan *dt;
private:


    int m_NextWorkoutID;
    int m_NextWorkoutNameID;
    int m_NextExerciseID;
    int m_NextExerciseSetID;
    int m_NextExerciseNameID;
    int m_NextUserID;

    bool DoesExerciseExist(QString);
    bool DoesWorkoutExist(QString);
    int GetWorkoutNameID(QString);
    int GetExerciseNameID(QString);

    //all take some sqlobject param
    vector <Workout> ConvertToWorkoutList();
    vector <Exercise_Set> ConvertToExerciseList();
    vector <QString> ConverToStringList();
};


#endif // BUSINESSLAYER_H
