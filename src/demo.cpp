#include <QApplication>


#include "FramelessBlurBehindWindowBase.h"

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    cFramelessBlurBehindWindowBase  w;
    w.resize( 800, 600 );
    w.show();

    return a.exec();
}

