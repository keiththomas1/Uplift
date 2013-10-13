#include <QLabel>
#include <QBoxLayout>
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

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
