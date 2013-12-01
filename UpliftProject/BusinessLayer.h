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
        //ValidateBusinessTier();
    }
    //!This is the destructor.
    virtual ~BusinessTier() {}

    int AddExercise     (QString, int user_id);
    int AddWorkout      (QString, int user_id);
    int AddWorkoutPair  (QString, QString, int user_id, int order); // don't know why order is on here.
    int AddUser         (QString, QString);
    int AddSet          (int userID, QString workout, QString exercise, int weight, int reps);
    void AddWorkoutLog   (QString workoutName, int userID);
    int RemoveExercise  (QString, int user_id);
    int RemoveWorkout   (QString, int user_id);
    int RemoveWorkoutPair (QString, QString, int user_id);
    int RemoveUser      (QString, QString);
    int RemoveSet(int user_id);
    int ModifySet(int user_id); //not sure how to implement this
    void UpdateWorkout   (QString, QString, int user_id);
    void UpdateExercise  (QString, QString, int user_id);
    void CloseDB();
    int GetWorkoutNameID(QString, int user_id);
    int GetExerciseNameID(QString, int user_id);
    int GetUserID(QString);
    QStringList GetExercisesInWorkout(QString workoutName, int user_id);
    QStringList GetExerciseHistory(QString exercise, int user_id, QString sortBy);
    QStringList GetWorkoutHistory(QString workout, int user_id);
    QStringList GetWorkoutList(int user_id);
    QStringList GetExerciseList(int user_id);
    QStringList GetUserList();
    void ValidateBusinessTier();
    bool DoesUserExist(QString);
    bool ValidateUser(QString user, QString pass);

    //stats functions
    QString getFirstWorkoutDate(int user_id);
    QString getLastWorkoutDate(int user_id);
    int getTotalWeight(int user_id);
    int getTotalNumOfReps(int user_id);
    int getAvgVolumePerWorkout(int user_id);

    //!This function returns the time in days from the first to most recent workout.  Returns -1 on fail.
    //!/param user_id this tracks the current user.
    int getFirstToLastWorkout(int user_id);

    //!This function returns the frequency of workouts per day for a user.  Returns -1 on fail.
    //!/param user_id this tracks the current user.
    int getWorkoutFrequency(int user_id);

    //!This function returns the total number of workouts for a user.  Returns -1 on fail.
    //!/param user_id this tracks the current user.
    int getTotalNumOfWorkouts(int user_id);

    //!This function returns the total number of sets for a user.  Returns -1 on fail.
    //!/param user_id this tracks the current user.
    int getTotalNumOfSets(int user_id);

    //!This function returns the average sets per workout a user has done.  Returns -1 on fail.
    //!/param user_id this tracks the current user.
    int getAvgSetsPerWorkout(int user_id);

    //!This function returns the average reps per set for a user.  Returns -1 on fail.
    //!/param user_id this tracks the current user.
    int getAvgRepsPerSet(int user_id);

private:
    bool DoesExerciseExist(QString, int user_id);
    bool DoesWorkoutExist(QString, int user_id);
    bool DoesPairExist(QString, QString, int user_id);
    int OneRepMax(double reps, double weight);
    DBaseMan *dt; //SHOULD BE PRIVATE, PUBLIC FOR TESTING
};

#endif // BUSINESSLAYER_H
