#include "welcomescreen.h"
#include <QDebug>
#include <QString>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QWidget(parent)
{
    QString string("Hello, world.");
    label = new QLabel(string);
    label->show();
    //label->x(100);
    //label->y(100);
    qDebug() << label->x();
    qDebug() << label->y();
}
