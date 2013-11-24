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

class BusinessTier
{
public:
    BusinessTier()
    {
        dt = new DBaseMan();
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
    }
    virtual ~BusinessTier() {}

    int GetTime()       { return (int)time(NULL);}
    int AddExercise     (QString);
    int AddWorkout      (QString);
    int AddUser         (QString, QString);
    int AddSet          (Exercise_Set*);
    int RemoveExercise  (QString);
    int RemoveWorkout   (QString);
    int RemoveUser      (QString, QString);
    int RemoveSet();
    int ModifySet(); //not sure how to implement this
    void StoreIDs();
    QStringList GetWorkoutList();
    QStringList GetExerciseList();

    DBaseMan *dt; //SHOULD BE PRIVATE, PUBLIC FOR TESTING
private:
    int m_NextWorkoutID;
    int m_NextWorkoutNameID;
    int m_NextExerciseID;
    int m_NextExerciseSetID;
    int m_NextExerciseNameID;
    int m_NextUserID;

    bool DoesExerciseExist(QString);
    bool DoesWorkoutExist(QString);
    bool DoesUserExist(QString);
    int GetWorkoutNameID(QString);
    int GetExerciseNameID(QString);
    int GetUserID(QString);
};


#endif // BUSINESSLAYER_H
