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
    //QString currWorkout;
    //QString currExercise;

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
    void on_deleteWorkoutButton_clicked();
    void on_editWorkoutButton_clicked();

    //exercises page buttons
    void on_addExerciseButton_clicked();
    void on_addExerciseNameDoneButton_clicked();
    void on_deleteExerciseButton_clicked();

    //cleanup
    void cleanup_before_quit();

signals:
    void WidgetClosed();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
