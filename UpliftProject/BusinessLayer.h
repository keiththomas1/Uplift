#ifndef BUSINESSLAYER_H
#define BUSINESSLAYER_H
#include <ctime>
#include <vector>
#include <QString>
#include <QStringList>
#include "DataAccessLayer.h"

using namespace std;

/*! \brief The BusinessTier class is acts as an API between the GUI and the database.
 *
 *   Provides all functionality required by the GUI.
 *   Builds queries, passes them to the database, and formats the results for the GUI.
 */
class BusinessTier
{
public:
    //!Creates a DBaseMan (database manager) object for interaction with the database.
    BusinessTier()
    {
        dt = new DBaseMan();
    }
    //!A destructor.
    virtual ~BusinessTier() {}

    //Add functions
    int AddExercise(QString, int user_id);
    int AddWorkout(QString, int user_id);
    int AddWorkoutPair(QString, QString, int user_id, int order); // don't know why order is on here.
    int AddUser(QString, QString);
    int AddSet(int userID, int workoutInstanceID, QString workout, QString exercise, int weight, int reps);
    void AddWorkoutLog(QString workoutName, int userID);

    //Remove functions
    int RemoveExercise(QString, int user_id);
    int RemoveWorkout(QString, int user_id);
    int RemoveWorkoutPair(QString, QString, int user_id);
    int RemoveUser(QString, QString);
    int RemoveSet(int user_id);
    int ModifySet(int user_id); //not sure how to implement this

    //Update functions
    void UpdateWorkout(QString, QString, int user_id);
    void UpdateExercise(QString, QString, int user_id);

    //Get functions
    int GetWorkoutNameID(QString, int user_id);
    int GetExerciseNameID(QString, int user_id);
    int GetWorkoutInstanceID();
    int GetUserID(QString);
    int GetWorkoutVolume(int workout_instance_id);
    QStringList GetExercisesInWorkout(QString workoutName, int user_id);
    QStringList GetExerciseHistory(QString exercise, int user_id, QString sortBy);
    QStringList GetWorkoutHistory(QString workout, int user_id, QString sortBy);
    QStringList GetWorkoutList(int user_id);
    QStringList GetExerciseList(int user_id);
    QStringList GetUserList();

    //stats functions
    QString getFirstWorkoutDate(int user_id);
    QString getLastWorkoutDate(int user_id);
    int getTotalWeight(int user_id);
    int getTotalNumOfReps(int user_id);
    int getAvgVolumePerWorkout(int user_id);
    int getFirstToLastWorkout(int user_id);
    int getWorkoutFrequency(int user_id);
    int getTotalNumOfWorkouts(int user_id);
    int getTotalNumOfSets(int user_id);
    int getAvgSetsPerWorkout(int user_id);
    int getAvgRepsPerSet(int user_id);

    //helper functions
    void CloseDB();
    void ValidateBusinessTier();
    bool DoesUserExist(QString);
    bool ValidateUser(QString user, QString pass);


private:
    bool DoesExerciseExist(QString, int user_id);
    bool DoesWorkoutExist(QString, int user_id);
    bool DoesPairExist(QString, QString, int user_id);
    int OneRepMax(double reps, double weight);
    DBaseMan *dt;
};

#endif // BUSINESSLAYER_H
