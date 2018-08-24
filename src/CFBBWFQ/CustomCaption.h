#pragma once


#include <QObject>


#include "CustomCaptionBase.h"
#include "CustomCaptionButton.h"


namespace  CFBBWFQ
{


class cCustomCaption :
    public cCustomCaptionBase
{

    Q_OBJECT

    typedef  ::CFBBWFQ::cCustomCaptionBase  tParent;

public:
    // Construction / Destruction
    virtual  ~cCustomCaption();
    cCustomCaption( QWidget* parent = Q_NULLPTR );

public:
    // Public customization utilities
    void  ActiveBackgroundColor( const  QColor& iColor );
    const  QColor&  ActiveBackgroundColor();
    void  InactiveBackgroundColor( const  QColor& iColor );
    const  QColor&  InactiveBackgroundColor();

public:
    // Custom NC Handling implementation in caption
    virtual  bool  HitEmptySpace( long iX, long iY )  override;

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

    QColor  mActiveBackgroundColor;
    QColor  mInactiveBackgroundColor;
};


} // namespace  CFBBWFQ

