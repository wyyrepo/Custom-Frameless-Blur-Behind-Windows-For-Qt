#include <QApplication>


#include "DemoCustomMainWindow.h"

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    cDemoCustomMainWindow  w;
    w.resize( 800, 600 );
    w.show();

    return a.exec();
}

