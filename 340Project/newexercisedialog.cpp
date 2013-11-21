#include "newexercisedialog.h"
#include "ui_newexercisedialog.h"
#include <string>
#include <iostream>

//!constructor of the exercise class
NewExerciseDialog::NewExerciseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewExerciseDialog)
{
    ui->setupUi(this);
}

//!destructor of the exercise class
NewExerciseDialog::~NewExerciseDialog()
{
    delete ui;
}

void NewExerciseDialog::on_Cancel_clicked()
{
    //!close the ui when cancel is clicked
    close();
}

void NewExerciseDialog::on_OK_clicked()
{
    //!string variables
    std::string name;
    std::string sets;
    std::string reps;

    QString temp_name;
    QString temp_sets;
    QString temp_reps;

    //!get the qstrings from the lineEdit
    temp_name = ui->ExerciseName_->text();
    temp_sets = ui->Reps_->text();
    temp_reps = ui->Sets_->text();

    //!turn the qstrings into std strings
    name = temp_name.toStdString();
    sets = temp_sets.toStdString();
    reps = temp_reps.toStdString();

    /***have to throw these into a class or struct of sorts and then throw them into the database***/

    std::cout << name << sets << reps << std::endl;
}
