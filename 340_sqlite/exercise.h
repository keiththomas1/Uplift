#ifndef EXERCISE_H
#define EXERCISE_H

class Exercise
{
public:
    Exercise(string p_ExerciseName, int p_ExerciseID) :
        m_ExerciseName(p_ExerciseName), m_ExerciseID(p_ExerciseID)
    {
    }
    virtual ~Exercise() {}

    string GetExerciseName() { return m_ExerciseName;}
    int GetExerciseID()      { return m_ExerciseID;}

private:
    string m_ExerciseName;
    int m_ExerciseID;
};
#endif // EXERCISE_H
