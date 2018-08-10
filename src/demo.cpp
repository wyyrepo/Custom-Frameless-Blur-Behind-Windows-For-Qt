#include <QApplication>


#include "DemoCustomMainWindow.h"

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    auto w = new cDemoCustomMainWindow( NULL );
    w->ActiveCaptionBackgroundColor( QColor( 50, 50, 50 ) );
    w->InactiveCaptionBackgroundColor( QColor( 30, 30, 30 ) );
    w->resize( 800, 600 );
    w->show();

    return a.exec();
}

