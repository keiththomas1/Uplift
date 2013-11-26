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

        //This is probably obsolete at this point.
        /*
        QSqlQuery tmp = dt->executeQuery("SELECT * FROM id_table");
        if (tmp.next()) {
            //seed all the ID counters with db value
            m_NextWorkoutID         = tmp.value(0).toInt();
            m_NextWorkoutNameID     = tmp.value(1).toInt();
            m_NextExerciseID        = tmp.value(2).toInt();
            m_NextExerciseSetID     = tmp.value(3).toInt();
            m_NextExerciseNameID    = tmp.value(4).toInt();
            m_NextUserID            = tmp.value(5).toInt();
        }
        else {
            //seed all the ID counters with 0
            m_NextWorkoutID = 0;
            m_NextWorkoutNameID = 0;
            m_NextExerciseID = 0;
            m_NextExerciseSetID = 0;
            m_NextExerciseNameID = 0;
            m_NextUserID = 0;
        }
        */
    }
    //!This is the destructor.
    virtual ~BusinessTier() {}

    int GetTime()       { return (int)time(NULL);}
    int AddExercise     (QString);
    int AddWorkout      (QString);
    int AddWorkoutPair  (QString, QString, int);
    int AddUser         (QString, QString);
    int AddSet          (int currUserID, QString currWorkout, QString currExercise, int weight, int reps);
    int RemoveExercise  (QString);
    int RemoveWorkout   (QString);
    int RemoveWorkoutPair (QString, QString);
    int RemoveUser      (QString, QString);
    int RemoveSet();
    int ModifySet(); //not sure how to implement this
    void UpdateWorkout   (QString, QString);
    void UpdateExercise  (QString, QString);
    void StoreIDs();
    void CloseDB();
    int GetWorkoutNameID(QString);
    int GetExerciseNameID(QString);
    int GetUserID(QString);
    QStringList GetExercisesInWorkout(QString workoutName);
    QStringList GetWorkoutList();
    QStringList GetExerciseList();

    DBaseMan *dt; //SHOULD BE PRIVATE, PUBLIC FOR TESTING
private:

    //These probably can be removed.
    int m_NextWorkoutID;
    int m_NextWorkoutNameID;
    int m_NextExerciseID;
    int m_NextExerciseSetID;
    int m_NextExerciseNameID;
    int m_NextUserID;

    bool DoesExerciseExist(QString);
    bool DoesWorkoutExist(QString);
    bool DoesUserExist(QString);
    bool DoesPairExist(QString, QString);

};


#endif // BUSINESSLAYER_H
