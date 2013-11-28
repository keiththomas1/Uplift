#ifndef BUSINESSLAYER_H
#define BUSINESSLAYER_H
#include <ctime>
#include <vector>
#include <QString>
#include <QStringList>
#include "exercise.h"
#include "exercise_set.h"
#include "workout.h"
#include "user.h"
#include "DataAccessLayer.h"

using namespace std;


//TODO: clean up this class, delete the obsolete parts of the constructor.
//!This class is the second-level of the database, and deals with the custom queries needed specifically for the exercise application API.
class BusinessTier
{
public:
    //!This constructor creates a DBaseMan (database manager) object which sends customized queries to the Data Access Layer.
    BusinessTier()
    {
        //!This is the instance of the database manager object, DBaseMan.
        dt = new DBaseMan();
        ValidateBusinessTier();
    }
    //!This is the destructor.
    virtual ~BusinessTier() {}

    int AddExercise     (QString);
    int AddWorkout      (QString);
    int AddWorkoutPair  (QString, QString, int order); // don't know why order is on here.
    int AddUser         (QString, QString);
    int AddSet          (int userID, QString workout, QString exercise, int weight, int reps);
    int RemoveExercise  (QString);
    int RemoveWorkout   (QString);
    int RemoveWorkoutPair (QString, QString);
    int RemoveUser      (QString, QString);
    int RemoveSet();
    int ModifySet(); //not sure how to implement this
    void UpdateWorkout   (QString, QString);
    void UpdateExercise  (QString, QString);
    void CloseDB();
    int GetWorkoutNameID(QString);
    int GetExerciseNameID(QString);
    int GetUserID(QString);
    QStringList GetExercisesInWorkout(QString workoutName);
    QStringList GetExerciseHistory(QString exercise);
    QStringList GetWorkoutList();
    QStringList GetExerciseList();
    QStringList GetUserList();
    void ValidateBusinessTier();

    DBaseMan *dt; //SHOULD BE PRIVATE, PUBLIC FOR TESTING
private:
    bool DoesExerciseExist(QString);
    bool DoesWorkoutExist(QString);
    bool DoesUserExist(QString);
    bool DoesPairExist(QString, QString);

};


#endif // BUSINESSLAYER_H
