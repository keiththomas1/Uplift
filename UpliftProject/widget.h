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
    int currWorkoutID;
    int currExerciseID;
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

    //cleanup
    void cleanup_before_quit();

signals:
    void WidgetClosed();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
