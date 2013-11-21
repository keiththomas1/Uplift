#include <QBoxLayout>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newExerciseDialog.h"
#include "ui_newExerciseDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//work out button
void MainWindow::on_WorkoutButton_clicked()
{
    ui->TabWidgets->setCurrentIndex(0);

}

//exercise button
void MainWindow::on_ExercisesButton_clicked()
{
    ui->TabWidgets->setCurrentIndex(1);

}

//stats button
void MainWindow::on_StatsButton_clicked()
{
    ui->TabWidgets->setCurrentIndex(3);
}

//calendar button
void MainWindow::on_CalenderButton_clicked()
{
    ui->TabWidgets->setCurrentIndex(2);
}

void MainWindow::on_addWorkoutButton_clicked()
{
    ui->WorkoutList->addItem("hey");

}

void MainWindow::on_addExercise_clicked()
{
    NewExerciseDialog *ExerciseDialog = new NewExerciseDialog();
    ExerciseDialog->exec();
}
