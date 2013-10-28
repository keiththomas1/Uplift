#ifndef EXERCISE_H
#define EXERCISE_H
#include <QObject>
#include <iostream>
#include <map>

using namespace std;

class Exercise : public QObject
{
    Q_OBJECT
public:
    Exercise(string name, int reps, int weight, int id) :
        m_name(name), m_reps(reps), m_weight(weight), m_exercise_id(id)
    {
        cout << "exercise_id: " << id << endl;
        printf("%s\n", m_name.c_str());
    }
    virtual ~Exercise() {}

    //Get methods
    string GetName() { return m_name;}
    int GetReps() { return m_reps;}
    int GetWeight() { return m_weight;}
    int GetWorkoutID() { return m_workout_id;}
    int GetExerciseID() { return m_exercise_id;}

private:
    string m_name;
    int m_reps;
    int m_weight;
    int m_exercise_id;
    int m_workout_id;


signals:

public slots:

};

#endif // EXERCISE_H
