#include <QApplication>


#include "DemoCustomMainWindow.h"
#include "CFBBWFQ/CustomMainWindow.h"

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    auto w = new cDemoCustomMainWindow( NULL );
    w->ActiveCaptionBackgroundColor( QColor( 50, 50, 50 ) );
    w->InactiveCaptionBackgroundColor( QColor( 30, 30, 30 ) );
    w->resize( 800, 600 );
    w->show();

    auto c = new  QWidget( NULL );
    auto w2 = new  ::CFBBWFQ::cCustomMainWindow( NULL );
    w2->SetCaptionWidget( c );
    w2->resize( 800, 600 );
    w2->show();

    return a.exec();
}

