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

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->addItem("hey");
}


// Workout button.
void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

// Exercise button.
void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

// Calendar button.
void MainWindow::on_pushButton_3_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

// Stats button.
void MainWindow::on_pushButton_4_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}
