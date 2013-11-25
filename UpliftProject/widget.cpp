#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pagesStack->setCurrentIndex(0);
    bt = new BusinessTier();
    ui->workoutList->addItems(bt->GetWorkoutList());
    ui->exerciseList->addItems(bt->GetExerciseList());

    //this is how you do non-default signals/slots
    connect(this, SIGNAL(WidgetClosed()), this, SLOT(cleanup_before_quit()));
}

Widget::~Widget()
{
    bt->StoreIDs();
    delete ui;
    delete bt;
}

void Widget::on_workoutsButton_clicked() {  //DONE
    ui->pagesStack->setCurrentIndex(0);
}
void Widget::on_exercisesButton_clicked() { //DONE
    ui->pagesStack->setCurrentIndex(1);
}
void Widget::on_historyButton_clicked() {   //DONE
    ui->pagesStack->setCurrentIndex(2);
}
void Widget::on_statsButton_clicked() {     //DONE
    ui->pagesStack->setCurrentIndex(3);
}
void Widget::closeEvent(QCloseEvent *event) { //DONE
    emit WidgetClosed();
    event->accept();
}
void Widget::cleanup_before_quit() {        //MAYBE FREE SOME DATA?
    bt->StoreIDs();
}

/************** WORKOUTS PAGE ****************/
void Widget::on_addWorkoutButton_clicked() {    //DONE
    ui->workoutsStack->setCurrentIndex(1);
}
void Widget::on_addWorkoutNameDoneButton_clicked() {    //DONE
    ui->workoutList->clear();                           //clear workoutList text box
    bt->AddWorkout(ui->addWorkoutNameLine->text());     //add workout from line edit
    ui->workoutList->addItems(bt->GetWorkoutList());    //repopulate workout list from db
    ui->addWorkoutNameLine->clear();                    //clear line edit
    ui->workoutsStack->setCurrentIndex(0);              //switch back to workout page
}
void Widget::on_deleteWorkoutButton_clicked() {

    bt->RemoveWorkout(ui->workoutList->currentItem()->text());
    workoutList.removeOne(ui->workoutList->currentItem()->text());
    ui->workoutList->clear();
    ui->workoutList->addItems(workoutList);
    ui->workoutList->addItems(bt->GetWorkoutList());
}
void Widget::on_editWorkoutButton_clicked() {
    ui->workoutsStack->setCurrentIndex(2);
}

/************** EXERCISES PAGE ****************/
void Widget::on_addExerciseButton_clicked() {           //DONE
    ui->exercisesStack->setCurrentIndex(1);
}
void Widget::on_addExerciseNameDoneButton_clicked() {     //DONE
    ui->exerciseList->clear();                            //clear exerciseList text box
    bt->AddExercise(ui->addExerciseNameLine->text());     //add exercise from line edit
    ui->exerciseList->addItems(bt->GetExerciseList());    //repopulate exercise list from db
    ui->addExerciseNameLine->clear();                     //clear line edit
    ui->exercisesStack->setCurrentIndex(0);               //switch back to exercises page
}

//TODO we need to check if the if the exercise exists before trying to delete it.  The gui is crashing with nothing is clicked.
void Widget::on_deleteExerciseButton_clicked() {
    if(ui->exerciseList->currentItem()->text() == NULL) return;
    bt->RemoveExercise(ui->exerciseList->currentItem()->text());
    exerciseList.removeOne(ui->exerciseList->currentItem()->text());
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList());
}




