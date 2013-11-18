#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
/*
    void on_pushButton_5_clicked();

    //void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();
*/


    void on_WorkoutButton_clicked();

    void on_ExercisesButton_clicked();

    void on_StatsButton_clicked();

    void on_CalenderButton_clicked();

    void on_addWorkoutButton_clicked();

    void on_addExercise_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
