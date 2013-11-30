#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pagesStack->setCurrentIndex(0);
    bt = new BusinessTier();
    ui->workoutList->addItems(bt->GetWorkoutList());
    ui->exerciseList->addItems(bt->GetExerciseList());

    //disable start page buttons until selection
    ui->deleteWorkoutButton->setEnabled(false);
    ui->startWorkoutButton->setEnabled(false);
    ui->editWorkoutButton->setEnabled(false);

    //this is how you do non-default signals/slots
    connect(this, SIGNAL(WidgetClosed()), this, SLOT(cleanup_before_quit()));
    connect(ui->workoutList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_workout_buttons()));
    connect(ui->exerciseList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_exercise_buttons()));
    connect(ui->editWorkoutExercisesList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_editWorkout_buttons()));
    connect(ui->performWorkoutExerciseList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_performWorkout_buttons()));
}
Widget::~Widget()
{
    //bt->StoreIDs();
    delete ui;
    delete bt;
}
/************** HELPER FUNCTIONS ****************/
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
void Widget::manage_workout_buttons() {
    if (ui->workoutList->currentRow() < 0) {
        ui->deleteWorkoutButton->setEnabled(false);
        ui->startWorkoutButton->setEnabled(false);
        ui->editWorkoutButton->setEnabled(false);
    }
    else {
        ui->deleteWorkoutButton->setEnabled(true);
        ui->startWorkoutButton->setEnabled(true);
        ui->editWorkoutButton->setEnabled(true);
    }
}
void Widget::manage_exercise_buttons() {
    if (ui->exerciseList->currentRow() < 0) {
        ui->editExerciseButton->setEnabled(false);
        ui->deleteExerciseButton->setEnabled(false);
    }
    else {
        ui->editExerciseButton->setEnabled(true);
        ui->deleteExerciseButton->setEnabled(true);
    }
}
void Widget::manage_editWorkout_buttons() {
    if (ui->editWorkoutExercisesList->currentRow() < 0) {
        ui->editWorkoutDeleteButton->setEnabled(false);
    }
    else ui->editWorkoutDeleteButton->setEnabled(true);
}
void Widget::manage_performWorkout_buttons() {
    if (ui->performWorkoutExerciseList->currentRow() < 0) {
        ui->performExerciseButton->setEnabled(false);
    }
    else ui->performExerciseButton->setEnabled(true);
}

void Widget::disable_exercise_buttons() {
    ui->exerciseList->setCurrentRow(-1);
    ui->exerciseList->itemSelectionChanged();
}
void Widget::disable_workout_buttons() {
    ui->workoutList->setCurrentRow(-1);
    ui->workoutList->itemSelectionChanged();
}
void Widget::disable_editWorkout_buttons() {
    ui->editWorkoutExercisesList->setCurrentRow(-1);
    ui->editWorkoutExercisesList->itemSelectionChanged();
}
void Widget::disable_performWorkout_buttons() {
    ui->performWorkoutExerciseList->setCurrentRow(-1);
    ui->performWorkoutExerciseList->itemSelectionChanged();
}

void Widget::closeEvent(QCloseEvent *event) { //DONE
    emit WidgetClosed();
    event->accept();
}
void Widget::cleanup_before_quit() {        //MAYBE FREE SOME DATA?
    bt->CloseDB();
}

/************** MAIN PAGE SWITCHING ****************/
void Widget::on_workoutsButton_clicked() {  //DONE
    Widget::disable_workout_buttons();
    ui->pagesStack->setCurrentIndex(0);
}
void Widget::on_exercisesButton_clicked() { //DONE
    Widget::disable_exercise_buttons();
    ui->pagesStack->setCurrentIndex(1);
}
void Widget::on_historyButton_clicked() {   //DONE
    ui->pagesStack->setCurrentIndex(2);
}
void Widget::on_statsButton_clicked() {     //DONE
    ui->pagesStack->setCurrentIndex(3);
}

/************** WORKOUTS PAGE ****************/
void Widget::on_addWorkoutButton_clicked() {    //DONE
    ui->workoutsStack->setCurrentIndex(1);
}
void Widget::on_addWorkoutNameDoneButton_clicked() {
    if (ui->addWorkoutNameLine->text() == "") return;
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
    Widget::manage_workout_buttons();

}
void Widget::on_editWorkoutButton_clicked() {
    Widget::disable_editWorkout_buttons();
    currWorkout = ui->workoutList->currentItem()->text();   //save the workout name
    ui->editWorkoutNameLine->clear();
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutNameLine->setText(currWorkout);          //populate the edit workout line edit with workout name
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout));
    ui->workoutsStack->setCurrentIndex(2);                  //switch to edit workout page
}
void Widget::on_startWorkoutButton_clicked() {
    disable_performWorkout_buttons();
    currWorkout = ui->workoutList->currentItem()->text();
    ui->performWorkoutExerciseList->clear();
    ui->performWorkoutExerciseList->addItems(bt->GetExercisesInWorkout(currWorkout));
    ui->performWorkoutTitle->setText(currWorkout);
    ui->workoutsStack->setCurrentIndex(4);
}

/************** EDIT WORKOUT PAGE ****************/
void Widget::on_editWorkoutAddButton_clicked() {
    ui->addToWorkoutList->addItems(bt->GetExerciseList());  //populate addToWorkoutList with all exercises availble
    ui->workoutsStack->setCurrentIndex(3);                  //switch to addToWorkout page
}
//TODO: don't allow edit with empty nameLine.
void Widget::on_editWorkoutDoneButton_clicked() {
    if (ui->editWorkoutNameLine->text() == "") return;
    bt->UpdateWorkout(currWorkout, ui->editWorkoutNameLine->text());    //update name in DB
    Widget::UpdateWorkoutList();
    ui->workoutsStack->setCurrentIndex(0);                              //switch to main workouts page
}
void Widget::on_editWorkoutDeleteButton_clicked() {
    qDebug() << "currWorkout: " << currWorkout;
    qDebug() << "currExercise: " << ui->editWorkoutExercisesList->currentItem()->text();
    bt->RemoveWorkoutPair(currWorkout, ui->editWorkoutExercisesList->currentItem()->text());
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout));
}

/************** PERFORM WORKOUT PAGE ****************/
void Widget::on_performExerciseButton_clicked() {
    currExercise = ui->performWorkoutExerciseList->currentItem()->text();
    ui->performExerciseTitle->setText(currExercise);
    ui->performExerciseCurrWorkoutTitle->setText(currWorkout);
    ui->workoutsStack->setCurrentIndex(5);

}
void Widget::on_finishWorkoutButton_clicked() {
    ui->performWorkoutExerciseList->clear();
    ui->workoutsStack->setCurrentIndex(0);
}

/************** PERFORM EXERCISE PAGE ****************/
void Widget::on_performExerciseAddButton_clicked() {
    int weight = ui->performExerciseWeight->value();
    int reps = ui->performExerciseReps->value();
    bt->AddSet(0, currWorkout, currExercise, weight, reps);
    ui->performExerciseHistoryList->clear();
    ui->performExerciseHistoryList->addItems(exerciseList);  //compiler is complaining about this, check out.

}

/************** ADD TO WORKOUT PAGE ****************/
//currWorkout was saved when edit workout button pressed, so it should be correct
void Widget::on_addToWorkoutBackButton_clicked() {
    ui->addToWorkoutList->clear();
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout));
    ui->workoutsStack->setCurrentIndex(2);
}
//IN PROGRESS
void Widget::on_addToWorkoutAddButton_clicked() {
    //last param is TEMPORARY!
    bt->AddWorkoutPair(currWorkout, ui->addToWorkoutList->currentItem()->text(), 0);    //add the workout pair to DB
}

/************** EXERCISES PAGE ****************/
void Widget::on_addExerciseButton_clicked() {           //DONE
    ui->exercisesStack->setCurrentIndex(1);
}
//TODO: don't allow empty string to be added
void Widget::on_addExerciseNameDoneButton_clicked() {
    if (ui->addExerciseNameLine->text() == "") return;
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
    Widget::manage_exercise_buttons();
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
    if (ui->editExerciseLine->text() == "") return;
    bt->UpdateExercise(currExercise, ui->editExerciseLine->text());    //update name in DB
    Widget::UpdateExerciseList();
    disable_exercise_buttons();
    ui->exercisesStack->setCurrentIndex(0);                            //switch to main exercise page
}
void Widget::on_editExerciseCancelButton_clicked() {
    ui->editExerciseLine->clear();
    ui->exercisesStack->setCurrentIndex(0);
}

/************** STATISTICS PAGE ****************/
/*
void Widget::on_addExerciseButton_clicked() {           //DONE
    ui->exercisesStack->setCurrentIndex(1);
*/




