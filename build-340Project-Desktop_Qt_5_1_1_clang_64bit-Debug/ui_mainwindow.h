/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextBrowser *Title;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *MainLayout;
    QTabWidget *TabWidgets;
    QWidget *workoutTab;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *WorkOutTabLayout;
    QLabel *WorkoutLabel;
    QListWidget *WorkoutList;
    QPushButton *addWorkoutButton;
    QWidget *exerciseTab;
    QLabel *ExerciseLabel;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout;
    QListWidget *ExerciseList;
    QPushButton *addExercise;
    QWidget *calendarTab;
    QLabel *label_2;
    QWidget *statsTab;
    QLabel *label_3;
    QHBoxLayout *MainButtonLayout;
    QPushButton *WorkoutButton;
    QPushButton *ExercisesButton;
    QPushButton *StatsButton;
    QPushButton *CalenderButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(675, 592);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Title = new QTextBrowser(centralWidget);
        Title->setObjectName(QStringLiteral("Title"));
        Title->setGeometry(QRect(190, 10, 321, 41));
        QFont font;
        font.setFamily(QStringLiteral("NoviasHand"));
        Title->setFont(font);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(70, 70, 534, 461));
        MainLayout = new QVBoxLayout(verticalLayoutWidget);
        MainLayout->setSpacing(6);
        MainLayout->setContentsMargins(11, 11, 11, 11);
        MainLayout->setObjectName(QStringLiteral("MainLayout"));
        MainLayout->setContentsMargins(0, 0, 0, 0);
        TabWidgets = new QTabWidget(verticalLayoutWidget);
        TabWidgets->setObjectName(QStringLiteral("TabWidgets"));
        workoutTab = new QWidget();
        workoutTab->setObjectName(QStringLiteral("workoutTab"));
        verticalLayoutWidget_2 = new QWidget(workoutTab);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 501, 331));
        WorkOutTabLayout = new QVBoxLayout(verticalLayoutWidget_2);
        WorkOutTabLayout->setSpacing(6);
        WorkOutTabLayout->setContentsMargins(11, 11, 11, 11);
        WorkOutTabLayout->setObjectName(QStringLiteral("WorkOutTabLayout"));
        WorkOutTabLayout->setContentsMargins(0, 0, 0, 0);
        WorkoutLabel = new QLabel(verticalLayoutWidget_2);
        WorkoutLabel->setObjectName(QStringLiteral("WorkoutLabel"));
        QFont font1;
        font1.setPointSize(16);
        WorkoutLabel->setFont(font1);

        WorkOutTabLayout->addWidget(WorkoutLabel);

        WorkoutList = new QListWidget(verticalLayoutWidget_2);
        WorkoutList->setObjectName(QStringLiteral("WorkoutList"));

        WorkOutTabLayout->addWidget(WorkoutList);

        addWorkoutButton = new QPushButton(verticalLayoutWidget_2);
        addWorkoutButton->setObjectName(QStringLiteral("addWorkoutButton"));

        WorkOutTabLayout->addWidget(addWorkoutButton);

        TabWidgets->addTab(workoutTab, QString());
        exerciseTab = new QWidget();
        exerciseTab->setObjectName(QStringLiteral("exerciseTab"));
        ExerciseLabel = new QLabel(exerciseTab);
        ExerciseLabel->setObjectName(QStringLiteral("ExerciseLabel"));
        ExerciseLabel->setGeometry(QRect(10, 0, 91, 31));
        ExerciseLabel->setFont(font1);
        verticalLayoutWidget_3 = new QWidget(exerciseTab);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(9, 31, 511, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ExerciseList = new QListWidget(verticalLayoutWidget_3);
        ExerciseList->setObjectName(QStringLiteral("ExerciseList"));

        verticalLayout->addWidget(ExerciseList);

        addExercise = new QPushButton(verticalLayoutWidget_3);
        addExercise->setObjectName(QStringLiteral("addExercise"));

        verticalLayout->addWidget(addExercise);

        TabWidgets->addTab(exerciseTab, QString());
        calendarTab = new QWidget();
        calendarTab->setObjectName(QStringLiteral("calendarTab"));
        label_2 = new QLabel(calendarTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 10, 91, 31));
        label_2->setFont(font1);
        TabWidgets->addTab(calendarTab, QString());
        statsTab = new QWidget();
        statsTab->setObjectName(QStringLiteral("statsTab"));
        label_3 = new QLabel(statsTab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 10, 91, 31));
        label_3->setFont(font1);
        TabWidgets->addTab(statsTab, QString());

        MainLayout->addWidget(TabWidgets);

        MainButtonLayout = new QHBoxLayout();
        MainButtonLayout->setSpacing(6);
        MainButtonLayout->setObjectName(QStringLiteral("MainButtonLayout"));
        WorkoutButton = new QPushButton(verticalLayoutWidget);
        WorkoutButton->setObjectName(QStringLiteral("WorkoutButton"));

        MainButtonLayout->addWidget(WorkoutButton);

        ExercisesButton = new QPushButton(verticalLayoutWidget);
        ExercisesButton->setObjectName(QStringLiteral("ExercisesButton"));

        MainButtonLayout->addWidget(ExercisesButton);

        StatsButton = new QPushButton(verticalLayoutWidget);
        StatsButton->setObjectName(QStringLiteral("StatsButton"));

        MainButtonLayout->addWidget(StatsButton);

        CalenderButton = new QPushButton(verticalLayoutWidget);
        CalenderButton->setObjectName(QStringLiteral("CalenderButton"));

        MainButtonLayout->addWidget(CalenderButton);


        MainLayout->addLayout(MainButtonLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 675, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        TabWidgets->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Title->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'NoviasHand'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:18pt; font-weight:600;\">LiftBook</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        workoutTab->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        WorkoutLabel->setText(QApplication::translate("MainWindow", "Workouts", 0));
        addWorkoutButton->setText(QApplication::translate("MainWindow", "Add Workout Button", 0));
        TabWidgets->setTabText(TabWidgets->indexOf(workoutTab), QApplication::translate("MainWindow", "W", 0));
        ExerciseLabel->setText(QApplication::translate("MainWindow", "Exercises", 0));
        addExercise->setText(QApplication::translate("MainWindow", "Add", 0));
        TabWidgets->setTabText(TabWidgets->indexOf(exerciseTab), QApplication::translate("MainWindow", "E", 0));
        label_2->setText(QApplication::translate("MainWindow", "Calendar", 0));
        TabWidgets->setTabText(TabWidgets->indexOf(calendarTab), QApplication::translate("MainWindow", "C", 0));
        label_3->setText(QApplication::translate("MainWindow", "Stats", 0));
        TabWidgets->setTabText(TabWidgets->indexOf(statsTab), QApplication::translate("MainWindow", "S", 0));
        WorkoutButton->setText(QApplication::translate("MainWindow", "Workouts", 0));
        ExercisesButton->setText(QApplication::translate("MainWindow", "Exercises", 0));
        StatsButton->setText(QApplication::translate("MainWindow", "Stats", 0));
        CalenderButton->setText(QApplication::translate("MainWindow", "Calendar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
