#include "newexercisedialog.h"
#include "ui_newexercisedialog.h"
#include <string>
#include <iostream>

NewExerciseDialog::NewExerciseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewExerciseDialog)
{
    ui->setupUi(this);
}

NewExerciseDialog::~NewExerciseDialog()
{
    delete ui;
}

void NewExerciseDialog::on_Cancel_clicked()
{
    close();
}

void NewExerciseDialog::on_OK_clicked()
{
    std::string name;
    std::string sets;
    std::string reps;

    QString temp_name;
    QString temp_sets;
    QString temp_reps;

    temp_name = ui->ExerciseName_->text();
    temp_sets = ui->Reps_->text();
    temp_reps = ui->Sets_->text();

    name = temp_name.toStdString();
    sets = temp_sets.toStdString();
    reps = temp_reps.toStdString();

    std::cout << name << sets << reps << std::endl;
}
