/********************************************************************************
** Form generated from reading UI file 'CustomFramelessBlurBehindWindowsForQt.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMFRAMELESSBLURBEHINDWINDOWSFORQT_H
#define UI_CUSTOMFRAMELESSBLURBEHINDWINDOWSFORQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomFramelessBlurBehindWindowsForQtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CustomFramelessBlurBehindWindowsForQtClass)
    {
        if (CustomFramelessBlurBehindWindowsForQtClass->objectName().isEmpty())
            CustomFramelessBlurBehindWindowsForQtClass->setObjectName(QStringLiteral("CustomFramelessBlurBehindWindowsForQtClass"));
        CustomFramelessBlurBehindWindowsForQtClass->resize(600, 400);
        menuBar = new QMenuBar(CustomFramelessBlurBehindWindowsForQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CustomFramelessBlurBehindWindowsForQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CustomFramelessBlurBehindWindowsForQtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CustomFramelessBlurBehindWindowsForQtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CustomFramelessBlurBehindWindowsForQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CustomFramelessBlurBehindWindowsForQtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CustomFramelessBlurBehindWindowsForQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CustomFramelessBlurBehindWindowsForQtClass->setStatusBar(statusBar);

        retranslateUi(CustomFramelessBlurBehindWindowsForQtClass);

        QMetaObject::connectSlotsByName(CustomFramelessBlurBehindWindowsForQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *CustomFramelessBlurBehindWindowsForQtClass)
    {
        CustomFramelessBlurBehindWindowsForQtClass->setWindowTitle(QApplication::translate("CustomFramelessBlurBehindWindowsForQtClass", "CustomFramelessBlurBehindWindowsForQt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomFramelessBlurBehindWindowsForQtClass: public Ui_CustomFramelessBlurBehindWindowsForQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMFRAMELESSBLURBEHINDWINDOWSFORQT_H
