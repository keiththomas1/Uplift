#include "newexercisedialog.h"
#include "ui_newexercisedialog.h"

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
