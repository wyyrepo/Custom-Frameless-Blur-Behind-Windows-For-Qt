#pragma once


#include "AbstractFramelessBlurBehindWindow.h"


namespace  CFBBWFQ
{


class cCustomMainWindowBase :
    public cAbstractFramelessBlurBehindWindow
{

    typedef  cAbstractFramelessBlurBehindWindow  tParent;

public:
    // Construction / Destruction
    virtual  ~cCustomMainWindowBase();
    cCustomMainWindowBase( QWidget* parent = Q_NULLPTR );

public:
    // Internal Client Geometry Handling
    void    CaptionHeight( int iValue );
    int     CaptionHeight();
    QRect   CaptionGeometry();
    QRect   ContentsGeometry();

public:
    // Custom Maximize behaviour implementation
    void  Restore();
    bool  CheckCustomWindowMaximizedState()  const;

protected:
    // Protected Non-Client OS behaviour handling overrides
    virtual  bool  NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )  override;

protected:
    // Protected Qt events override
    virtual  void  resizeEvent( QResizeEvent*   event )     override;
    virtual  void  moveEvent(   QMoveEvent*     event )     override;
    virtual  void  changeEvent( QEvent*         event )     override;

private:
    // Window behaviour patch
    void  FixWindowOverlapOnMove();
    void  FixWindowOverlapOnResize( const  QSize&  iOldSize );
    void  AdjustWindowOnMaximize();
    void  AdjustWindowOnRestore();

private:
    // Private member data: internal geometry
    int         mCaptionHeight;
    QMargins    mPaddings;

    // Private member data: Custom maximized / restore behaviour related data
    QRect       mRestoreGeometry;
    bool        mMaximized;
    QPoint      mLatestOldPos;
    QSize       mLatestOldSize;
};


} // namespace  CFBBWFQ

