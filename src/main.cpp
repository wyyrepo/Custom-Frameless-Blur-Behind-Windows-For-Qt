#include <QApplication>
#include <QMainWindow>

int
main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    QMainWindow  w;
    w.resize( 800, 600 );
    w.show();

    return a.exec();
}

