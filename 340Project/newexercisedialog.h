#ifndef NEWEXERCISEDIALOG_H
#define NEWEXERCISEDIALOG_H

#include <QDialog>

namespace Ui {
class NewExerciseDialog;
}

class NewExerciseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewExerciseDialog(QWidget *parent = 0);
    ~NewExerciseDialog();

private slots:
    void on_Cancel_clicked();

private:
    Ui::NewExerciseDialog *ui;
};

#endif // NEWEXERCISEDIALOG_H
