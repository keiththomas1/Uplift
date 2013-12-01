#ifndef EXERCISESTATS_H
#define EXERCISESTATS_H

#endif // EXERCISESTATS_H

//!This class add statistical functions to the business layer API.
class ExerciseStats
{
public:
    //!This is the constructor for the ExerciseStats class.
    ExerciseStats(){}
    //!This is the destructor.
    virtual ~ExerciseStats() {}

    //!This function returns the time in days from the first to most recent workout.
    //!/param user_id this tracks the current user.
    int getFirstToLastWorkout(int user_id);

    //!This function returns the frequency of workouts per day for a user.
    //!/param user_id this tracks the current user.
    int getWorkoutFrequency(int user_id);

    //!This function returns the total number of workouts for a user.
    //!/param user_id this tracks the current user.
    int getTotalNumOfWorkouts(int user_id);

    //!This function returns the total number of sets for a user.
    //!/param user_id this tracks the current user.
    int getTotalNumOfSets(int user_id);

    //!This function returns the average sets per workout a user has done.
    //!/param user_id this tracks the current user.
    int getAvgSetsPerWorkout(int user_id);

    //!This function returns the average reps per set for a user.
    //!/param user_id this tracks the current user.
    int getAvgRepsPerSet(int user_id);
};
