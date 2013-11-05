#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>
#include <QLabel>

class WelcomeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeScreen(QWidget *parent = 0);

private:
    QLabel* label;

signals:

public slots:

};

#endif // WELCOMESCREEN_H
