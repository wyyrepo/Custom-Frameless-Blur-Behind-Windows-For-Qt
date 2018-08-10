#pragma once


#include "CFBBWFQ/CustomMainWindowBase.h"


class  cDemoCustomMainCaption;


class cDemoCustomMainWindow :
    public ::CFBBWFQ::cCustomMainWindowBase
{

    typedef  ::CFBBWFQ::cCustomMainWindowBase  tParent;

public:
    // Construction / Destruction
    virtual  ~cDemoCustomMainWindow();
    cDemoCustomMainWindow( QWidget* parent = Q_NULLPTR );

public:
    // Buffer methods for customization of the caption
    void  ActiveCaptionBackgroundColor( const  QColor& iColor );
    const  QColor&  ActiveCaptionBackgroundColor();
    void  InactiveCaptionBackgroundColor( const  QColor& iColor );
    const  QColor&  InactiveCaptionBackgroundColor();

private:
    // Protected Non-Client OS behaviour handling overrides
    virtual  bool  NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )  override;

protected:
    // Protected Qt events override
    virtual  void  resizeEvent( QResizeEvent*   event )  override;
    virtual  void  closeEvent(  QCloseEvent*    event )   override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private data members
    cDemoCustomMainCaption* mCustomCaption;
};

