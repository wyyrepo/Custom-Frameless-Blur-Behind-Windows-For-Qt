#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CustomFramelessBlurBehindWindowsForQt.h"

class CustomFramelessBlurBehindWindowsForQt : public QMainWindow
{
    Q_OBJECT

public:
    CustomFramelessBlurBehindWindowsForQt(QWidget *parent = Q_NULLPTR);

private:
    Ui::CustomFramelessBlurBehindWindowsForQtClass ui;
};
