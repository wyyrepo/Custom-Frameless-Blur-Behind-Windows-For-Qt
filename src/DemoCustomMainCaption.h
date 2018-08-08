#pragma once


#include <QObject>
#include <QWidget>


#include "DemoCustomMainWindow.h"
#include "CustomCaptionButton.h"


class cDemoCustomMainCaption :
    public QWidget
{

    Q_OBJECT

public:
    // Construction / Destruction
    virtual  ~cDemoCustomMainCaption();
    cDemoCustomMainCaption( cDemoCustomMainWindow* parent );

public:
    // Custom NC Handling implementation in caption
    bool  HitEmptySpace( long iX, long iY );

protected:
    // Protected Qt event overrides
    virtual  void  paintEvent(  QPaintEvent*    event )     override;
    virtual  void  resizeEvent( QResizeEvent*   event )     override;

private  slots:
    // Private Qt Slots
    void  ProcessCloseClicked();
    void  ProcessMaximizeClicked();
    void  ProcessMinimizeClicked();

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    ::CFBBWFQ::cCustomCaptionButton*  mCloseButton;
    ::CFBBWFQ::cCustomCaptionButton*  mMaximizeButton;
    ::CFBBWFQ::cCustomCaptionButton*  mMinimizeButton;

    cDemoCustomMainWindow*    mParent;
};

