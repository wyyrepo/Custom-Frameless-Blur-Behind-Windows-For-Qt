#include "CustomFramelessBlurBehindWindowsForQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomFramelessBlurBehindWindowsForQt w;
    w.show();
    return a.exec();
}
