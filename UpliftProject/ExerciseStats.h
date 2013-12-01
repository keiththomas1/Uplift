#ifndef EXERCISESTATS_H
#define EXERCISESTATS_H

#endif // EXERCISESTATS_H

//!This class is the second-level of the database, and deals with the custom queries needed specifically for the exercise application API.
class ExerciseStats
{
public:
    //!This constructor creates a DBaseMan (database manager) object which sends customized queries to the Data Access Layer.
    ExerciseStats(){}
    //!This is the destructor.
    virtual ~ExerciseStats() {}

    int getFirstToLastWorkout(int user_id);
    int getWorkoutFrequency(int user_id);
    int getTotalNumOfWorkouts(int user_id);
    int getTotalNumOfSets(int user_id);
    int getAvgSetsPerWorkout(int user_id);
    int getAvgRepsPerSet(int user_id);
};
