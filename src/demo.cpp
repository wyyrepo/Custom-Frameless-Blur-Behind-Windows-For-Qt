#include <QApplication>

#include "CFBBWFQ/CustomMainWindow.h"
#include "CFBBWFQ/CustomCaption.h"

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    QWidget* b;
    b = new QWidget();
    b->setStyleSheet( "background:rgba( 0, 0, 0, 0.5 );" );

    auto c = new  ::CFBBWFQ::cCustomCaption( NULL );
    c->ActiveBackgroundColor( QColor( 50, 50, 50 ) );
    c->InactiveBackgroundColor( QColor( 30, 30, 30 ) );

    auto w = new  ::CFBBWFQ::cCustomMainWindow( NULL );
    w->setAttribute( Qt::WA_DeleteOnClose );
    w->SetCaptionWidget( c );
    w->SetCenterWidget( b );
    w->resize( 800, 600 );
    w->show();

    return a.exec();
}

