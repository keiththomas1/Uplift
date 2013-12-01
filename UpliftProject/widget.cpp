#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

//TEMPORARY USER ID VARIABLE
int user_id = 1;

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pagesStack->setCurrentIndex(0);
    ui->historyButton->setHidden(true);
    ui->exercisesButton->setHidden(true);
    ui->workoutsButton->setHidden(true);
    ui->statsButton->setHidden(true);
    bt = new BusinessTier();

    //disable start page buttons until selection
    ui->deleteWorkoutButton->setEnabled(false);
    ui->startWorkoutButton->setEnabled(false);
    ui->editWorkoutButton->setEnabled(false);

    //signals & slots initialization
    connect(this, SIGNAL(WidgetClosed()), this, SLOT(cleanup_before_quit()));
    connect(ui->workoutList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_workout_buttons()));
    connect(ui->exerciseList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_exercise_buttons()));
    connect(ui->editWorkoutExercisesList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_editWorkout_buttons()));
    connect(ui->performWorkoutExerciseList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_performWorkout_buttons()));
    connect(ui->chooseExerciseHistoryList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_exerciseHistory_buttons()));
    connect(ui->chooseWorkoutHistoryList, SIGNAL(itemSelectionChanged()), this, SLOT(manage_workoutHistory_buttons()));

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
    ui->workoutList->addItems(bt->GetWorkoutList(currUserID));    //repopulate workout list from db
    ui->workoutList->sortItems(Qt::AscendingOrder);     //sort list alphabetically
}
void Widget::UpdateExerciseList() {
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList(currUserID));    //repopulate exercise list from DB
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
void Widget::manage_exerciseHistory_buttons() {
    if (ui->chooseExerciseHistoryList->currentRow() < 0) {
        ui->chooseExerciseHistoryDoneButton->setEnabled(false);
    }
    else ui->chooseExerciseHistoryDoneButton->setEnabled(true);
}
void Widget::manage_workoutHistory_buttons() {
    if (ui->chooseWorkoutHistoryList->currentRow() < 0) {
        ui->chooseWorkoutHistoryDoneButton->setEnabled(false);
    }
    else ui->chooseWorkoutHistoryDoneButton->setEnabled(true);
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
void Widget::disable_exerciseHistory_buttons() {
    ui->chooseExerciseHistoryList->setCurrentRow(-1);
    ui->chooseExerciseHistoryList->itemSelectionChanged();
}
void Widget::disable_workoutHistory_buttons() {
    ui->chooseWorkoutHistoryList->setCurrentRow(-1);
    ui->chooseWorkoutHistoryList->itemSelectionChanged();
}
void Widget::set_exerciseSortBy_buttons(QString setButton) {
    ui->exerciseSortBy1RM->setDown(false);
    ui->exerciseSortByReps->setDown(false);
    ui->exerciseSortByWeight->setDown(false);
    ui->exerciseSortByDate->setDown(false);
    if (setButton == "1RM") ui->exerciseSortBy1RM->setDown(true);
    else if (setButton == "reps") ui->exerciseSortByReps->setDown(true);
    else if (setButton == "weight") ui->exerciseSortByWeight->setDown(true);
    else if (setButton == "date") ui->exerciseSortByDate->setDown(true);
}
void Widget::set_historySortBy_buttons(QString) {

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
    ui->pagesStack->setCurrentIndex(1);
}
void Widget::on_exercisesButton_clicked() { //DONE
    Widget::disable_exercise_buttons();
    ui->pagesStack->setCurrentIndex(2);
}
void Widget::on_historyButton_clicked() {   //DONE
    ui->pagesStack->setCurrentIndex(3);
}
void Widget::on_statsButton_clicked() {     //DONE
    ui->pagesStack->setCurrentIndex(4);
}

/************** WORKOUTS PAGE ****************/
void Widget::on_addWorkoutButton_clicked() {    //DONE
    ui->workoutsStack->setCurrentIndex(1);
}
void Widget::on_addWorkoutNameDoneButton_clicked() {
    if (ui->addWorkoutNameLine->text() == "") return;
    ui->workoutList->clear();                           //clear workoutList text box
    bt->AddWorkout(ui->addWorkoutNameLine->text(), currUserID);     //add workout from line edit
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
    bt->RemoveWorkout(ui->workoutList->currentItem()->text(),currUserID);
    workoutList.removeOne(ui->workoutList->currentItem()->text());
    ui->workoutList->clear();
    ui->workoutList->addItems(workoutList);
    ui->workoutList->addItems(bt->GetWorkoutList(currUserID));
    Widget::manage_workout_buttons();

}
void Widget::on_editWorkoutButton_clicked() {
    Widget::disable_editWorkout_buttons();
    currWorkout = ui->workoutList->currentItem()->text();   //save the workout name
    ui->editWorkoutNameLine->clear();
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutNameLine->setText(currWorkout);          //populate the edit workout line edit with workout name
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    ui->workoutsStack->setCurrentIndex(2);                  //switch to edit workout page
}
void Widget::on_startWorkoutButton_clicked() {
    disable_performWorkout_buttons();
    currWorkout = ui->workoutList->currentItem()->text();

    //log the workout
    bt->AddWorkoutLog(currWorkout, currUserID);
    ui->performWorkoutExerciseList->clear();
    ui->performWorkoutExerciseList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    ui->performWorkoutTitle->setText(currWorkout);
    ui->workoutsStack->setCurrentIndex(4);
}

/************** EDIT WORKOUT PAGE ****************/
void Widget::on_editWorkoutAddButton_clicked() {
    ui->addToWorkoutList->addItems(bt->GetExerciseList(currUserID));  //populate addToWorkoutList with all exercises availble
    ui->workoutsStack->setCurrentIndex(3);                  //switch to addToWorkout page
}
void Widget::on_editWorkoutDoneButton_clicked() {
    if (ui->editWorkoutNameLine->text() == "") return;
    bt->UpdateWorkout(currWorkout, ui->editWorkoutNameLine->text(),currUserID);    //update name in DB
    Widget::UpdateWorkoutList();
    disable_workout_buttons();
    ui->workoutsStack->setCurrentIndex(0);                              //switch to main workouts page
}
void Widget::on_editWorkoutDeleteButton_clicked() {
    //qDebug() << "currWorkout: " << currWorkout;
    //qDebug() << "currExercise: " << ui->editWorkoutExercisesList->currentItem()->text();
    bt->RemoveWorkoutPair(currWorkout, ui->editWorkoutExercisesList->currentItem()->text(),currUserID);
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    Widget::manage_editWorkout_buttons();
}

/************** PERFORM WORKOUT PAGE ****************/
void Widget::on_performExerciseButton_clicked() {
    currExercise = ui->performWorkoutExerciseList->currentItem()->text();
    ui->performExerciseHistoryList->clear();
    ui->performExerciseHistoryList->addItems(bt->GetExerciseHistory(currExercise, currUserID, "date"));
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
    bt->AddSet(currUserID, currWorkout, currExercise, weight, reps);
    ui->performExerciseHistoryList->clear();
    ui->performExerciseHistoryList->addItems(bt->GetExerciseHistory(currExercise, currUserID, "date"));

}
void Widget::on_performExerciseBackButton_clicked()
{
    ui->workoutsStack->setCurrentIndex(4);
}

/************** ADD TO WORKOUT PAGE ****************/
//currWorkout was saved when edit workout button pressed, so it should be correct
void Widget::on_addToWorkoutBackButton_clicked() {
    ui->addToWorkoutList->clear();
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    ui->workoutsStack->setCurrentIndex(2);
}
//IN PROGRESS
void Widget::on_addToWorkoutAddButton_clicked() {
    //last param is TEMPORARY!
    bt->AddWorkoutPair(currWorkout, ui->addToWorkoutList->currentItem()->text(),currUserID,currUserID);    //add the workout pair to DB
}

/************** EXERCISES PAGE ****************/
void Widget::on_addExerciseButton_clicked() {           //DONE
    ui->exercisesStack->setCurrentIndex(1);
}
//TODO: don't allow empty string to be added
void Widget::on_addExerciseNameDoneButton_clicked() {
    if (ui->addExerciseNameLine->text() == "") return;
    ui->exerciseList->clear();                            //clear exerciseList text box
    //qDebug() << "adding exercise with userID = " + currUserID;
    bt->AddExercise(ui->addExerciseNameLine->text(),currUserID);     //add exercise to DB (from line edit)
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
    bt->RemoveExercise(ui->exerciseList->currentItem()->text(),currUserID);
    exerciseList.removeOne(ui->exerciseList->currentItem()->text());
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList(currUserID));
    Widget::manage_exercise_buttons();
}
//TODO: don't allow edit when no exercises exist
void Widget::on_editExerciseButton_clicked() {
    currExercise = ui->exerciseList->currentItem()->text();   //save the Exercise name
    ui->editExerciseLine->setText(currExercise);          //populate the edit Exercise line edit with Exercise name
    ui->exercisesStack->setCurrentIndex(2);                  //switch to edit Exercise page
}
//CURRENT
//TODO: check if update name works
void Widget::on_editExerciseDoneButton_clicked() {
    if (ui->editExerciseLine->text() == "") return;
    bt->UpdateExercise(currExercise, ui->editExerciseLine->text(),currUserID);    //update name in DB
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


//TODO: need a AuthenticateUser function that returns true/false;
void Widget::on_loginButton_clicked()
{
    QString user = ui->userLine->text();
    QString password = ui->passwordLine->text();
    if (bt->DoesUserExist(user)) {
        if (!bt->ValidateUser(user, password)) {
            ui->userLine->clear();
            ui->passwordLine->clear();
            ui->userLine->setText("incorrect password");
            return;
        }
        currUserID = bt->GetUserID(user);
        ui->workoutList->addItems(bt->GetWorkoutList(currUserID));
        ui->exerciseList->addItems(bt->GetExerciseList(currUserID));


        //unhide the page switching buttons
        ui->historyButton->setHidden(false);
        ui->exercisesButton->setHidden(false);
        ui->workoutsButton->setHidden(false);
        ui->statsButton->setHidden(false);
        Widget::disable_workout_buttons();
        Widget::disable_exercise_buttons();

        ui->pagesStack->setCurrentIndex(1); //go to workouts page
        ui->userLine->clear();
        ui->passwordLine->clear();
    }
    else {
        ui->userLine->clear();
        ui->passwordLine->clear();
        ui->userLine->setText("user does not exist");
    }
}

void Widget::on_newUserButton_clicked()
{
    ui->createAccountUsername->clear();
    ui->createAccountPassword1->clear();
    ui->createAccountPassword2->clear();
    ui->loginStack->setCurrentIndex(1);
}

void Widget::on_createAccountBackButton_clicked()
{
    ui->userLine->clear();
    ui->passwordLine->clear();
    ui->loginStack->setCurrentIndex(0);
}

void Widget::on_createAccountDoneButton_clicked()
{
    QString username = ui->createAccountUsername->text();
    QString pass1 = ui->createAccountPassword1->text();
    QString pass2 = ui->createAccountPassword2->text();

    if (bt->DoesUserExist(username)) {
        ui->createAccountUsername->clear();
        ui->createAccountPassword1->clear();
        ui->createAccountPassword2->clear();
        ui->createAccountUsername->setText("user already exists");
    }
    else if (username == "") {
        ui->createAccountUsername->clear();
        ui->createAccountPassword1->clear();
        ui->createAccountPassword2->clear();
        ui->createAccountUsername->setText("username cannot be empty");
        return;
    }
    else if (pass1 == "") {
        ui->createAccountUsername->clear();
        ui->createAccountPassword1->clear();
        ui->createAccountPassword2->clear();
        ui->createAccountUsername->setText("password cannot be empty");
    }
    else if (pass1 != pass2) {
        ui->createAccountUsername->clear();
        ui->createAccountPassword1->clear();
        ui->createAccountPassword2->clear();
        ui->createAccountUsername->setText("passwords don't match");
    }
    else {
        bt->AddUser(username, pass1);
        ui->userLine->clear();
        ui->userLine->setText(username);
        ui->passwordLine->clear();
        ui->loginStack->setCurrentIndex(0);
    }
}

void Widget::on_workoutHistoryButton_clicked()
{
    ui->chooseWorkoutHistoryList->clear();
    disable_workoutHistory_buttons();
    ui->chooseWorkoutHistoryList->addItems(bt->GetWorkoutList(currUserID));
    ui->historyStack->setCurrentIndex(2);
}

void Widget::on_exerciseHistoryButton_clicked()
{
    ui->chooseExerciseHistoryList->clear();
    disable_exerciseHistory_buttons();
    ui->chooseExerciseHistoryList->addItems(bt->GetExerciseList(currUserID));
    ui->historyStack->setCurrentIndex(1);

}

void Widget::on_chooseExerciseHistoryBackButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}

void Widget::on_chooseExerciseHistoryDoneButton_clicked()
{
    currExerciseHistory = ui->chooseExerciseHistoryList->currentItem()->text();
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "date"));
    set_exerciseSortBy_buttons("date");
    ui->historyStack->setCurrentIndex(3);
}

void Widget::on_chooseWorkoutHistoryBackButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}

//TODO: disable button unless selection made
//TODO: need GetWorkoutHistory function
void Widget::on_chooseWorkoutHistoryDoneButton_clicked()
{
    currWorkoutHistory = ui->chooseWorkoutHistoryList->currentItem()->text();
    ui->workoutHistoryList->clear();
    //ui->workoutHistoryList->addItems(bt->GetWorkoutHistory(currUserID, currWorkoutHistory));
    ui->historyStack->setCurrentIndex(4);
}

//TODO: workoutHistoryBackButton
//TODO: exerciseHistoryBackButton

void Widget::on_exerciseHistoryDoneButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}

void Widget::on_exerciseSortBy1RM_clicked()
{
    set_exerciseSortBy_buttons("1RM");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "1RM"));
}

void Widget::on_exerciseSortByDate_clicked()
{
    set_exerciseSortBy_buttons("date");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "date"));
}

void Widget::on_exerciseSortByReps_clicked()
{
    set_exerciseSortBy_buttons("reps");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "reps"));
}

void Widget::on_exerciseSortByWeight_clicked()
{
    set_exerciseSortBy_buttons("weight");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "weight"));
}

void Widget::on_workoutHistoryDoneButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}

void Widget::on_workoutSortByDate_clicked()
{

}

void Widget::on_workoutSortBySets_clicked()
{

}

void Widget::on_workoutSortByVolume_clicked()
{

}








