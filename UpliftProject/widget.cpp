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
    //bt->StoreIDs();
    delete ui;
    delete bt;
}
void Widget::UpdateWorkoutList() {
    ui->workoutList->clear();
    ui->workoutList->addItems(bt->GetWorkoutList());    //repopulate workout list from db
    ui->workoutList->sortItems(Qt::AscendingOrder);     //sort list alphabetically
}
void Widget::UpdateExerciseList() {
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList());    //repopulate exercise list from DB
    ui->exerciseList->sortItems(Qt::AscendingOrder);      //sort list alphabetically
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
    //bt->StoreIDs();
    bt->CloseDB();
}

/************** WORKOUTS PAGE ****************/
void Widget::on_addWorkoutButton_clicked() {    //DONE
    ui->workoutsStack->setCurrentIndex(1);
}
//TODO: make sure empty string is not added
void Widget::on_addWorkoutNameDoneButton_clicked() {
    ui->workoutList->clear();                           //clear workoutList text box
    bt->AddWorkout(ui->addWorkoutNameLine->text());     //add workout from line edit
    Widget::UpdateWorkoutList();
    ui->addWorkoutNameLine->clear();                    //clear line edit
    ui->workoutsStack->setCurrentIndex(0);              //switch back to workout page
}
void Widget::on_addWorkoutNameCancelButton_clicked() {  //DONE
    ui->addWorkoutNameLine->clear();                    //clear line edit
    ui->workoutsStack->setCurrentIndex(0);              //go back to main workouts page
}

void Widget::on_deleteWorkoutButton_clicked() {
    if (ui->workoutList->count() == 0) return;
    bt->RemoveWorkout(ui->workoutList->currentItem()->text());
    workoutList.removeOne(ui->workoutList->currentItem()->text());
    ui->workoutList->clear();
    ui->workoutList->addItems(workoutList);
    ui->workoutList->addItems(bt->GetWorkoutList());
}
//TODO: don't allow edit when no workouts exist
void Widget::on_editWorkoutButton_clicked() {
    currWorkout = ui->workoutList->currentItem()->text();   //save the workout name
    ui->editWorkoutNameLine->setText(currWorkout);          //populate the edit workout line edit with workout name
    ui->workoutsStack->setCurrentIndex(2);                  //switch to edit workout page
}
void Widget::on_editWorkoutAddButton_clicked() {
    ui->workoutsStack->setCurrentIndex(3);
}
//TODO: don't allow edit with empty nameLine.
void Widget::on_editWorkoutDoneButton_clicked() {
    bt->UpdateWorkout(currWorkout, ui->editWorkoutNameLine->text());    //update name in DB
    Widget::UpdateWorkoutList();
    ui->workoutsStack->setCurrentIndex(0);                              //switch to main workouts page
}

/************** ADD TO WORKOUT PAGE ****************/
void Widget::on_addToWorkoutBackButton_clicked() {
    ui->addToWorkoutList->clear();
    ui->workoutsStack->setCurrentIndex(2);
}

/************** EXERCISES PAGE ****************/
void Widget::on_addExerciseButton_clicked() {           //DONE
    ui->exercisesStack->setCurrentIndex(1);
}
//TODO: don't allow empty string to be added
void Widget::on_addExerciseNameDoneButton_clicked() {
    ui->exerciseList->clear();                            //clear exerciseList text box
    bt->AddExercise(ui->addExerciseNameLine->text());     //add exercise to DB (from line edit)
    Widget::UpdateExerciseList();
    ui->addExerciseNameLine->clear();                     //clear line edit
    ui->exercisesStack->setCurrentIndex(0);               //switch back to exercises page
}
void Widget::on_addExerciseNameCancelButton_clicked() {
    ui->addExerciseNameLine->clear();
    ui->exercisesStack->setCurrentIndex(0);
}
void Widget::on_deleteExerciseButton_clicked() {
    if(ui->exerciseList->count() == 0) return;
    bt->RemoveExercise(ui->exerciseList->currentItem()->text());
    exerciseList.removeOne(ui->exerciseList->currentItem()->text());
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList());
}
//TODO: don't allow edit when no exercises exist
void Widget::on_editExerciseButton_clicked() {
    currExercise = ui->exerciseList->currentItem()->text();   //save the Exercise name
    ui->editExerciseLine->setText(currExercise);          //populate the edit Exercise line edit with Exercise name
    ui->exercisesStack->setCurrentIndex(2);                  //switch to edit Exercise page
}
//CURRENT
//TODO: don't allow edit with empty nameLine.
void Widget::on_editExerciseDoneButton_clicked() {
    bt->UpdateExercise(currExercise, ui->editExerciseLine->text());    //update name in DB
    Widget::UpdateExerciseList();
    ui->exercisesStack->setCurrentIndex(0);                              //switch to main workouts page
}
void Widget::on_editExerciseCancelButton_clicked() {
    ui->editExerciseLine->clear();
    ui->exercisesStack->setCurrentIndex(0);
}





