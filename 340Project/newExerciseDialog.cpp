#include "newExerciseDialog.h"
//#include "ui_newExerciseDialog.h"

newExerciseDialog::newExerciseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new newExerciseDialog)
{
    addExerciseDialogue->setupUi(this);
}

newExerciseDialog::~newExerciseDialog()
{
    delete addExerciseDialogue;
}
