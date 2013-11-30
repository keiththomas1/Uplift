#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <string>
#include <QStringList>
#include <QCloseEvent>
#include "BusinessLayer.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //QStringList workoutExerciseList;
    QString currWorkout;
    QString currExercise;
    QString currWorkoutHistory;
    QString currExerciseHistory;
    int currWorkoutID;
    int currExerciseID;
    int currUserID;
    void UpdateWorkoutList();
    void UpdateExerciseList();


private:
    Ui::Widget *ui;
    BusinessTier *bt;
    QStringList workoutList;
    QStringList exerciseList;

public slots:
    //main 4 buttons
    void on_workoutsButton_clicked();
    void on_exercisesButton_clicked();
    void on_historyButton_clicked();
    void on_statsButton_clicked();

    //workouts page buttons
    void on_addWorkoutButton_clicked();
    void on_addWorkoutNameDoneButton_clicked();
    void on_addWorkoutNameCancelButton_clicked();
    void on_deleteWorkoutButton_clicked();
    void on_startWorkoutButton_clicked();

    //edit workout page
    void on_editWorkoutButton_clicked();
    void on_editWorkoutAddButton_clicked();
    void on_editWorkoutDoneButton_clicked();
    void on_editWorkoutDeleteButton_clicked();

    //perform workout page
    void on_performExerciseButton_clicked();
    void on_finishWorkoutButton_clicked();

    //add to workout page
    void on_addToWorkoutBackButton_clicked();
    void on_addToWorkoutAddButton_clicked();

    //exercises page buttons
    void on_addExerciseButton_clicked();
    void on_addExerciseNameDoneButton_clicked();
    void on_addExerciseNameCancelButton_clicked();
    void on_deleteExerciseButton_clicked();

    //edit exercise page
    void on_editExerciseButton_clicked();
    void on_editExerciseDoneButton_clicked();
    void on_editExerciseCancelButton_clicked();

    //perform exercise page
    void on_performExerciseAddButton_clicked();
    //void on_performExerciseBackButton_clicked();  //linker was complaining about this.

    //button management
    void manage_workout_buttons();
    void disable_workout_buttons();
    void manage_exercise_buttons();
    void disable_exercise_buttons();
    void manage_editWorkout_buttons();
    void disable_editWorkout_buttons();
    void manage_performWorkout_buttons();
    void disable_performWorkout_buttons();


    //cleanup
    void cleanup_before_quit();

signals:
    void WidgetClosed();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_workoutHistoryButton_clicked();
    void on_exerciseHistoryButton_clicked();
    void on_loginButton_clicked();
    void on_newUserButton_clicked();
    void on_createAccountDoneButton_clicked();
    void on_chooseExerciseHistoryDoneButton_clicked();
    void on_chooseWorkoutHistoryDoneButton_clicked();
    void on_exerciseHistoryDoneButton_clicked();
    void on_exerciseSortBy1RM_clicked();
    void on_exerciseSortByDate_clicked();
    void on_exerciseSortByReps_clicked();
    void on_exerciseSortByWeight_clicked();
    void on_workoutHistoryDoneButton_clicked();
    void on_workoutSortByDate_clicked();
    void on_workoutSortBySets_clicked();
    void on_workoutSortByVolume_clicked();
    void on_createAccountBackButton_clicked();
    void on_chooseExerciseHistoryBackButton_clicked();
    void on_chooseWorkoutHistoryBackButton_clicked();
    void on_performExerciseBackButton_clicked();
};

#endif // WIDGET_H
