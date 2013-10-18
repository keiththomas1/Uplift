/*#include <QLabel>
#include <QBoxLayout>
#include "label.h"

Label::Label(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::Label)
{
    // Trying to initialize some sort of container for the picture in the
    // assets folder and display it on screen. This compiles but doesn't
    // show anything.
    QWidget mainWindow;

    QBoxLayout* titleLayout = new QBoxLayout( QBoxLayout::Down );

    QPixmap* titlePixmap = new QPixmap( "/assets/Title.png" );
    QLabel* titleLabel = new QLabel( "Title", &mainWindow );
    titleLabel->setPixmap( *titlePixmap );

    titleLayout->addWidget( &mainWindow );

    mainWindow.show();
    //http://harmattan-dev.nokia.com/docs/library/html/qt4/designer-using-a-ui-file.html

    ui->setupUi(this);
}

Label::~Label()
{
    delete ui;
}
*/
