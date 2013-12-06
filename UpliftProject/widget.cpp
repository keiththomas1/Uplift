#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

using namespace std;

///Sets up the ui
///Sets the start page to the login screen
///Hides all buttons that shouldn't be accessible from the login screen
///Connects signals to custom slots
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
///Deletes the ui and bt objects
Widget::~Widget()
{
    //bt->StoreIDs();
    delete ui;
    delete bt;
}
/************** HELPER FUNCTIONS ****************/
///Clears then updates the workout list on the workout page with the current users workouts
void Widget::UpdateWorkoutList() {
    ui->workoutList->clear();
    ui->workoutList->addItems(bt->GetWorkoutList(currUserID));    //repopulate workout list from db
    ui->workoutList->sortItems(Qt::AscendingOrder);     //sort list alphabetically
}
///Clears then updates the exercise list on the exercise page with the current users exercises
void Widget::UpdateExerciseList() {
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList(currUserID));    //repopulate exercise list from DB
    ui->exerciseList->sortItems(Qt::AscendingOrder);      //sort list alphabetically
}
//Disables buttons on the workout page if no workout has been chosen
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
///Disables buttons on the exercise page if no exercise has been chosen
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
///Disables buttons on the edit workout page if no workout has been chosen
void Widget::manage_editWorkout_buttons() {
    if (ui->editWorkoutExercisesList->currentRow() < 0) {
        ui->editWorkoutDeleteButton->setEnabled(false);
    }
    else ui->editWorkoutDeleteButton->setEnabled(true);
}
///Disablses buttons on the perform workout page if no exercise has been chosen
void Widget::manage_performWorkout_buttons() {
    if (ui->performWorkoutExerciseList->currentRow() < 0) {
        ui->performExerciseButton->setEnabled(false);
    }
    else ui->performExerciseButton->setEnabled(true);
}
///Disables buttons the exercise history page if no exercise has been chosen
void Widget::manage_exerciseHistory_buttons() {
    if (ui->chooseExerciseHistoryList->currentRow() < 0) {
        ui->chooseExerciseHistoryDoneButton->setEnabled(false);
    }
    else ui->chooseExerciseHistoryDoneButton->setEnabled(true);
}
///Disables buttons on the workout history page if no workout has been chosen
void Widget::manage_workoutHistory_buttons() {
    if (ui->chooseWorkoutHistoryList->currentRow() < 0) {
        ui->chooseWorkoutHistoryDoneButton->setEnabled(false);
    }
    else ui->chooseWorkoutHistoryDoneButton->setEnabled(true);
}
///Disables the exercise page buttons
void Widget::disable_exercise_buttons() {
    ui->exerciseList->setCurrentRow(-1);
    ui->exerciseList->itemSelectionChanged();
}
///Disables the workout buttons
void Widget::disable_workout_buttons() {
    ui->workoutList->setCurrentRow(-1);
    ui->workoutList->itemSelectionChanged();
}
///Disables the edit workout buttons
void Widget::disable_editWorkout_buttons() {
    ui->editWorkoutExercisesList->setCurrentRow(-1);
    ui->editWorkoutExercisesList->itemSelectionChanged();
}
///Disables the perform workout buttons
void Widget::disable_performWorkout_buttons() {
    ui->performWorkoutExerciseList->setCurrentRow(-1);
    ui->performWorkoutExerciseList->itemSelectionChanged();
}
///Disables the exercise history buttons
void Widget::disable_exerciseHistory_buttons() {
    ui->chooseExerciseHistoryList->setCurrentRow(-1);
    ui->chooseExerciseHistoryList->itemSelectionChanged();
}
///Disables the workout history buttons
void Widget::disable_workoutHistory_buttons() {
    ui->chooseWorkoutHistoryList->setCurrentRow(-1);
    ui->chooseWorkoutHistoryList->itemSelectionChanged();
}
///Disables the exercise sort by buttons
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
///Disables the history sort by buttons
void Widget::set_historySortBy_buttons(QString) {

}
///Sends signal WidgetClosed() when the user clicks the close button on the app
void Widget::closeEvent(QCloseEvent *event) {
    emit WidgetClosed();
    event->accept();
}
///Closes the database before closing the app
void Widget::cleanup_before_quit() {
    bt->CloseDB();
}

/************** MAIN PAGE SWITCHING ****************/
///Switches to the workout page when the workout button is clicked
void Widget::on_workoutsButton_clicked() {
    Widget::disable_workout_buttons();
    ui->pagesStack->setCurrentIndex(1);
}
///Switches to the exercise page when the exercise button is clicked
void Widget::on_exercisesButton_clicked() {
    Widget::disable_exercise_buttons();
    ui->pagesStack->setCurrentIndex(2);
}
///Switches to the history page when the history button is clicked
void Widget::on_historyButton_clicked() {
    ui->pagesStack->setCurrentIndex(3);
}
///Switches to the stats page when the stats button is clicked
void Widget::on_statsButton_clicked() {
    ui->pagesStack->setCurrentIndex(4);
    ui->firstWorkoutDateVal->setText(QString(bt->getFirstWorkoutDate(currUserID)));
    ui->lastWorkoutDateVal->setText(QString(bt->getLastWorkoutDate(currUserID)));
    ui->firstLastSpanVal->setText(QString::number(bt->getFirstToLastWorkout(currUserID), 'f', 2)+QString(" Days"));
    ui->totalWorkoutsVal->setText(QString::number(bt->getTotalNumOfWorkouts(currUserID))+QString(" Workouts"));
    if(bt->getWorkoutFrequency(currUserID) == -1){
        ui->avgWorkoutFreqVal->setText(QString("N/A"));
    }
    else{
        ui->avgWorkoutFreqVal->setText(QString::number(bt->getWorkoutFrequency(currUserID))+QString(" Workouts/Day"));
    }
    ui->avgVolWorkoutVal->setText(QString::number(bt->getAvgVolumePerWorkout(currUserID)));
    ui->avgSetsWorkoutVal->setText(QString::number(bt->getAvgSetsPerWorkout(currUserID)));
    ui->avgRepsSetVal->setText(QString::number(bt->getAvgRepsPerSet(currUserID)));
    ui->totalWeightLiftedVal->setText(QString::number(bt->getTotalWeight(currUserID)));
    ui->totalSetsVal->setText(QString::number(bt->getTotalNumOfSets(currUserID)));
    ui->totalRepsVal->setText(QString::number(bt->getTotalNumOfReps(currUserID)));
}

/************** WORKOUTS PAGE ****************/
///switches to the "add workout" page when the "+" button is clicked on the workouts page
void Widget::on_addWorkoutButton_clicked() {    //DONE
    ui->workoutsStack->setCurrentIndex(1);
}
///switches to the workouts page when the done button is clicked
void Widget::on_addWorkoutNameDoneButton_clicked() {
    if (ui->addWorkoutNameLine->text() == "") return;
    ui->workoutList->clear();                           //clear workoutList text box
    bt->AddWorkout(ui->addWorkoutNameLine->text(), currUserID);     //add workout from line edit
    Widget::UpdateWorkoutList();
    ui->addWorkoutNameLine->clear();                    //clear line edit
    ui->workoutsStack->setCurrentIndex(0);              //switch back to workout page
}
///switches to the workout page when the cancel button is clicked
void Widget::on_addWorkoutNameCancelButton_clicked() {  //DONE
    ui->addWorkoutNameLine->clear();                    //clear line edit
    ui->workoutsStack->setCurrentIndex(0);              //go back to main workouts page
}
///removes the workout and updates the list when the delete button is clicked
void Widget::on_deleteWorkoutButton_clicked() {
    if (ui->workoutList->count() == 0) return;
    bt->RemoveWorkout(ui->workoutList->currentItem()->text(),currUserID);
    workoutList.removeOne(ui->workoutList->currentItem()->text());
    ui->workoutList->clear();
    ui->workoutList->addItems(workoutList);
    ui->workoutList->addItems(bt->GetWorkoutList(currUserID));
    Widget::manage_workout_buttons();

}
///switches to the edit workout page when the edit button is clicked
void Widget::on_editWorkoutButton_clicked() {
    Widget::disable_editWorkout_buttons();
    currWorkout = ui->workoutList->currentItem()->text();   //save the workout name
    ui->editWorkoutNameLine->clear();
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutNameLine->setText(currWorkout);          //populate the edit workout line edit with workout name
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    ui->workoutsStack->setCurrentIndex(2);                  //switch to edit workout page
}
///switches to the perform workout page when the start workout button is clicked
void Widget::on_startWorkoutButton_clicked() {
    disable_performWorkout_buttons();
    currWorkout = ui->workoutList->currentItem()->text();

    //log the workout
    bt->AddWorkoutLog(currWorkout, currUserID);
    //get the workoutInstanceID back from DB
    currWorkoutInstanceID = bt->GetWorkoutInstanceID();
    ui->performWorkoutExerciseList->clear();
    ui->performWorkoutExerciseList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    ui->performWorkoutTitle->setText(currWorkout);
    ui->workoutsStack->setCurrentIndex(4);
}

/************** EDIT WORKOUT PAGE ****************/
///switches to the add to workout page when the add button is clicked
void Widget::on_editWorkoutAddButton_clicked() {
    ui->addToWorkoutList->addItems(bt->GetExerciseList(currUserID));  //populate addToWorkoutList with all exercises availble
    ui->workoutsStack->setCurrentIndex(3);                  //switch to addToWorkout page
}
///swtiches to the workouts page when the done button is clicked
void Widget::on_editWorkoutDoneButton_clicked() {
    if (ui->editWorkoutNameLine->text() == "") return;
    bt->UpdateWorkout(currWorkout, ui->editWorkoutNameLine->text(),currUserID);    //update name in DB
    Widget::UpdateWorkoutList();
    disable_workout_buttons();
    ui->workoutsStack->setCurrentIndex(0);                              //switch to main workouts page
}
///deletes the exercise from the workout and updates the exercise list
void Widget::on_editWorkoutDeleteButton_clicked() {
    //qDebug() << "currWorkout: " << currWorkout;
    //qDebug() << "currExercise: " << ui->editWorkoutExercisesList->currentItem()->text();
    bt->RemoveWorkoutPair(currWorkout, ui->editWorkoutExercisesList->currentItem()->text(),currUserID);
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    Widget::manage_editWorkout_buttons();
}

/************** PERFORM WORKOUT PAGE ****************/
///switches to the perform set page when the perform exercise button is clicked
void Widget::on_performExerciseButton_clicked() {
    currExercise = ui->performWorkoutExerciseList->currentItem()->text();
    ui->performExerciseHistoryList->clear();
    ui->performExerciseHistoryList->addItems(bt->GetExerciseHistory(currExercise, currUserID, "date"));
    ui->performExerciseTitle->setText(currExercise);
    ui->performExerciseCurrWorkoutTitle->setText(currWorkout);
    ui->workoutsStack->setCurrentIndex(5);

}
///swtiches to the main workout page when the finish button is clicked
void Widget::on_finishWorkoutButton_clicked() {
    ui->performWorkoutExerciseList->clear();
    ui->workoutsStack->setCurrentIndex(0);
}

/************** PERFORM EXERCISE PAGE ****************/
///switches to the new exercise page when the add button is clicked
void Widget::on_performExerciseAddButton_clicked() {
    int weight = ui->performExerciseWeight->value();
    int reps = ui->performExerciseReps->value();
    bt->AddSet(currUserID, currWorkoutInstanceID, currWorkout, currExercise, reps, weight);
    ui->performExerciseHistoryList->clear();
    ui->performExerciseHistoryList->addItems(bt->GetExerciseHistory(currExercise, currUserID, "date"));

}
///switches to the exercise list page when the back button is clicked
void Widget::on_performExerciseBackButton_clicked()
{
    ui->workoutsStack->setCurrentIndex(4);
}

/************** ADD TO WORKOUT PAGE ****************/
///switches to the workout page when the back button is clicked
//currWorkout was saved when edit workout button pressed, so it should be correct
void Widget::on_addToWorkoutBackButton_clicked() {
    ui->addToWorkoutList->clear();
    ui->editWorkoutExercisesList->clear();
    ui->editWorkoutExercisesList->addItems(bt->GetExercisesInWorkout(currWorkout,currUserID));
    ui->workoutsStack->setCurrentIndex(2);
}
//IN PROGRESS
///adds the exercise to the workout
void Widget::on_addToWorkoutAddButton_clicked() {
    //last param is TEMPORARY!
    bt->AddWorkoutPair(currWorkout, ui->addToWorkoutList->currentItem()->text(),currUserID,currUserID);    //add the workout pair to DB
}

/************** EXERCISES PAGE ****************/
///switches to the add exercise page when the "+" button is clicked
void Widget::on_addExerciseButton_clicked() {           //DONE
    ui->exercisesStack->setCurrentIndex(1);
}
///switches to the exercises page when the done button is clicked
void Widget::on_addExerciseNameDoneButton_clicked() {
    if (ui->addExerciseNameLine->text() == "") return;
    ui->exerciseList->clear();                            //clear exerciseList text box
    //qDebug() << "adding exercise with userID = " + currUserID;
    bt->AddExercise(ui->addExerciseNameLine->text(),currUserID);     //add exercise to DB (from line edit)
    Widget::UpdateExerciseList();
    ui->addExerciseNameLine->clear();                     //clear line edit
    ui->exercisesStack->setCurrentIndex(0);               //switch back to exercises page
}
///switches to the exercisese page when the cancel button is clicked
void Widget::on_addExerciseNameCancelButton_clicked() {
    ui->addExerciseNameLine->clear();
    ui->exercisesStack->setCurrentIndex(0);
}
///removes the exercise from the list
void Widget::on_deleteExerciseButton_clicked() {
    if(ui->exerciseList->count() == 0) return;
    bt->RemoveExercise(ui->exerciseList->currentItem()->text(),currUserID);
    exerciseList.removeOne(ui->exerciseList->currentItem()->text());
    ui->exerciseList->clear();
    ui->exerciseList->addItems(bt->GetExerciseList(currUserID));
    Widget::manage_exercise_buttons();
}
///swtiches to the edit exercise page when the edit button is clicked
void Widget::on_editExerciseButton_clicked() {
    currExercise = ui->exerciseList->currentItem()->text();   //save the Exercise name
    ui->editExerciseLine->setText(currExercise);          //populate the edit Exercise line edit with Exercise name
    ui->exercisesStack->setCurrentIndex(2);                  //switch to edit Exercise page
}
///switches to the main exercise page when the done button is clicked
void Widget::on_editExerciseDoneButton_clicked() {
    if (ui->editExerciseLine->text() == "") return;
    bt->UpdateExercise(currExercise, ui->editExerciseLine->text(),currUserID);    //update name in DB
    Widget::UpdateExerciseList();
    disable_exercise_buttons();
    ui->exercisesStack->setCurrentIndex(0);                            //switch to main exercise page
}
///switches to the main exercises page when the cancel button is clicked
void Widget::on_editExerciseCancelButton_clicked() {
    ui->editExerciseLine->clear();
    ui->exercisesStack->setCurrentIndex(0);
}

/************** STATISTICS PAGE ****************/
///checks the user is authenticate and outputs an error or accepts
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
        ui->loginGraphic->setHidden(true);
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
///switches to the new user page
void Widget::on_newUserButton_clicked()
{
    ui->createAccountUsername->clear();
    ui->createAccountPassword1->clear();
    ui->createAccountPassword2->clear();
    ui->loginStack->setCurrentIndex(1);
}
///switches to the main login page
void Widget::on_createAccountBackButton_clicked()
{
    ui->userLine->clear();
    ui->passwordLine->clear();
    ui->loginStack->setCurrentIndex(0);
}
///makes sure the username isn't already taken then creates an account or outputs an error
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
///switches to the workout history page
void Widget::on_workoutHistoryButton_clicked()
{
    ui->chooseWorkoutHistoryList->clear();
    disable_workoutHistory_buttons();
    ui->chooseWorkoutHistoryList->addItems(bt->GetWorkoutList(currUserID));
    ui->historyStack->setCurrentIndex(2);
}
///switches to the exercise history page
void Widget::on_exerciseHistoryButton_clicked()
{
    ui->chooseExerciseHistoryList->clear();
    disable_exerciseHistory_buttons();
    ui->chooseExerciseHistoryList->addItems(bt->GetExerciseList(currUserID));
    ui->historyStack->setCurrentIndex(1);

}
///switches to the main history page
void Widget::on_chooseExerciseHistoryBackButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}
///switches to the main history page
void Widget::on_chooseExerciseHistoryDoneButton_clicked()
{
    currExerciseHistory = ui->chooseExerciseHistoryList->currentItem()->text();
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "date"));
    set_exerciseSortBy_buttons("date");
    ui->historyStack->setCurrentIndex(3);
}
///switches to the main history page
void Widget::on_chooseWorkoutHistoryBackButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}

///switches to the main history page
void Widget::on_chooseWorkoutHistoryDoneButton_clicked()
{
    currWorkoutHistory = ui->chooseWorkoutHistoryList->currentItem()->text();
    ui->workoutHistoryList->clear();
    ui->workoutHistoryList->addItems(bt->GetWorkoutHistory(currWorkoutHistory, currUserID, "date"));
    ui->historyStack->setCurrentIndex(4);
}
///switches to the main history page
void Widget::on_exerciseHistoryDoneButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}
///sorts the entries and refreshes the list
void Widget::on_exerciseSortBy1RM_clicked()
{
    set_exerciseSortBy_buttons("1RM");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "1RM"));
}
///sorts the entries and refreshes the list
void Widget::on_exerciseSortByDate_clicked()
{
    set_exerciseSortBy_buttons("date");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "date"));
}
///sorts the entries and refreshes the list
void Widget::on_exerciseSortByReps_clicked()
{
    set_exerciseSortBy_buttons("reps");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "reps"));
}
///sorts the entries and refreshes the list
void Widget::on_exerciseSortByWeight_clicked()
{
    set_exerciseSortBy_buttons("weight");
    ui->exerciseHistoryList->clear();
    ui->exerciseHistoryList->addItems(bt->GetExerciseHistory(currExerciseHistory, currUserID, "weight"));
}
///switches to the main history page
void Widget::on_workoutHistoryDoneButton_clicked()
{
    ui->historyStack->setCurrentIndex(0);
}
///sorts the entries and refreshes the list
void Widget::on_workoutSortByDate_clicked()
{
    ui->workoutHistoryList->clear();
    ui->workoutHistoryList->addItems(bt->GetWorkoutHistory(currWorkoutHistory, currUserID, "date"));
}








