#ifndef EXERCISE_SET_H
#define EXERCISE_SET_H

class Exercise_Set {

public:
    Exercise_Set(string p_ExerciseName, int p_ExerciseSetID, int p_UserID, int p_TimeStamp, int p_Weight, int p_Reps)
    {
        m_ExerciseName = p_ExerciseName;
        m_ExerciseSetID = p_ExerciseSetID;
        m_UserID = p_UserID;
        m_Timestamp = p_TimeStamp;
        m_Weight = p_Weight;
        m_Reps = p_Reps;
    }
    virtual ~Exercise_Set() {}

    string GetExerciseName()    { return m_ExerciseName;}
    int GetExerciseSetID()      { return m_ExerciseSetID;}
    int GetUserID()             { return m_UserID;}
    int GetTimestamp()          { return m_Timestamp;}  //UNIX epoch?
    int GetWeight()             { return m_Weight;}
    int GetReps()               { return m_Reps;}


private:
    string m_ExerciseName;
    int m_ExerciseSetID;
    int m_UserID;
    int m_Timestamp;
    int m_Weight;
    int m_Reps;
};

#endif // EXERCISE_SET_H
