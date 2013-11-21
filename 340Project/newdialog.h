#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>

namespace Ui {
class newDialog;
}

class newDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newDialog(QWidget *parent = 0);
    ~newDialog();

private:
    Ui::newDialog *ui;
};

#endif // NEWDIALOG_H
