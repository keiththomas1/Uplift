#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class newExerciseDialog;
}

class newExerciseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newExerciseDialog(QWidget *parent = 0);
    ~newExerciseDialog();

private:
    Ui::newExerciseDialog *addExerciseDialogue;
};

#endif // DIALOG_H
