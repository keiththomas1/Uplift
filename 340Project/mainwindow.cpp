#include <QBoxLayout>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Trying to initialize some sort of container for the picture in the
    // assets folder and display it on screen. This compiles but doesn't
    // show anything.
    /*QWidget mainWindow;

    QBoxLayout* titleLayout = new QBoxLayout( QBoxLayout::Down );

    QPixmap* titlePixmap = new QPixmap( "/assets/Title.png" );
    QLabel* titleLabel = new QLabel( "Title", &mainWindow );
    titleLabel->setPixmap( *titlePixmap );

    titleLayout->addWidget( &mainWindow );

    mainWindow.show(); */
    //http://harmattan-dev.nokia.com/docs/library/html/qt4/designer-using-a-ui-file.html

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
