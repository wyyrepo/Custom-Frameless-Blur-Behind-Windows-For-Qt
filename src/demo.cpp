#include <QApplication>

#include "CFBBWFQ/CustomMainWindow.h"
#include "CFBBWFQ/CustomCaption.h"

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    auto c = new  ::CFBBWFQ::cCustomCaption( NULL );
    c->ActiveBackgroundColor( QColor( 50, 50, 50 ) );
    c->InactiveBackgroundColor( QColor( 30, 30, 30 ) );
    auto w = new  ::CFBBWFQ::cCustomMainWindow( NULL );
    w->SetCaptionWidget( c );
    w->resize( 800, 600 );
    w->show();

    return a.exec();
}

