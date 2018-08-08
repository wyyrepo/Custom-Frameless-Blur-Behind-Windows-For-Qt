#include "CustomMainWindowBase.h"


#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>


// Default values defines
#define  DEFAULT_CAPTION_HEIGHT 30
#define  DEFAULT_PADDING_LEFT   0
#define  DEFAULT_PADDING_TOP    0
#define  DEFAULT_PADDING_RIGHT  0
#define  DEFAULT_PADDING_BOTTOM 0
#define  DEFAULT_PADDINGS       DEFAULT_PADDING_LEFT, DEFAULT_PADDING_TOP, DEFAULT_PADDING_RIGHT, DEFAULT_PADDING_BOTTOM


namespace  CFBBWFQ
{


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cCustomMainWindowBase::~cCustomMainWindowBase()
{
}


cCustomMainWindowBase::cCustomMainWindowBase( QWidget *parent ) :
    tParent( parent ),
    mCaptionHeight(     DEFAULT_CAPTION_HEIGHT  ),
    mPaddings(          DEFAULT_PADDINGS        ),
    mRestoreGeometry(   QRect()                 ),
    mMaximized(         false                   ),
    mLatestOldPos(      QPoint()                ),
    mLatestOldSize(     QSize()                 )
{
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------- Internal Client Geometry Handling


void
cCustomMainWindowBase::CaptionHeight( int iValue )
{
    mCaptionHeight = iValue;
}


int
cCustomMainWindowBase::CaptionHeight()
{
    return  mCaptionHeight;
}


QRect
cCustomMainWindowBase::CaptionGeometry()
{
    // Get Geometyry & Height of the title caption part, starting from top.
    return  QRect( 0, 0, width(), mCaptionHeight );
}


QRect
cCustomMainWindowBase::ContentsGeometry()
{
    // Get Geometry of the contents part.
    return  QRect(  mPaddings.left(),
                    mCaptionHeight              + mPaddings.top(),
                    width()                     - mPaddings.right()     - mPaddings.left(),
                    height() - mCaptionHeight   - mPaddings.bottom()    - mPaddings.top() );
}


//--------------------------------------------------------------------------------------
//--------------------------------------------- Custom Maximize behaviour implementation


void
cCustomMainWindowBase::Restore()
{
    // Manual restore implementation

    // The Regular way.
    showNormal();

    // The Patch geometry handles cases where snap & maximize conflict.
    setGeometry( mRestoreGeometry );

    // The patch Adjust which resets the flag & borders.
    AdjustWindowOnRestore();

    // The flag reset for consistency.
    mMaximized = false;
}


bool
cCustomMainWindowBase::CheckCustomWindowMaximizedState()  const
{
    // Manual maximized state implementation check:
    return  mMaximized;
}


//--------------------------------------------------------------------------------------
//--------------------------------- Protected Non-Client OS behaviour handling overrides


bool
cCustomMainWindowBase::NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Transition implementation can be called or overriden in childs of this class.
    // This one allows dragging only if caption geometry.

    // Custom processing for sending "hit caption" message to the OS
    // Return true:  the OS handles window move under mouse cursor like a native window
    // Return false: the mouse Events remain within the window
    bool  eligible = iY >= iRect.top() && iY < iRect.top() + CaptionHeight();

    if(!eligible)
        return  false;

    return  true;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt events override


void
cCustomMainWindowBase::resizeEvent( QResizeEvent* event )
{
    // Patch window behaviour and size on Maximize according to the available geometry

    // This is for the custom Maximize behaviour.
    QRect availableRect = QApplication::desktop()->availableGeometry( this );
    if( event->oldSize().width() < availableRect.width() - 1 && event->oldSize().height() < availableRect.height() - 1 )
        mLatestOldSize = event->oldSize();

    // On Restore Behaviour Patch ( here applied for win7 )
    AdjustWindowOnRestore();

    // Avoid having the window stuck behind taskbar
    FixWindowOverlapOnResize( event->oldSize() );

    // Fix for move too since resizing on some sides is equivalent to a move.
    FixWindowOverlapOnMove();
}


void
cCustomMainWindowBase::moveEvent( QMoveEvent* event )
{
    // Patch window behaviour and size on Maximize according to the available geometry
    QRect availableRect = QApplication::desktop()->availableGeometry( this );
    if( event->oldPos().x() > availableRect.x() + 1 && event->oldPos().y() > availableRect.y() + 1 )
        mLatestOldPos = event->oldPos();

    // Avoid having the window stuck behind taskbar
    FixWindowOverlapOnMove();
}


void
cCustomMainWindowBase::changeEvent(QEvent* event)
{
    // Regular processing anyways
    tParent::changeEvent(event);

    // + Additional Behaviour Patch Processing
    if( !( event->type() == QEvent::WindowStateChange ) )
        return;

    // Handling special behaviour for maximized state on windows state change
    if( isMaximized() )
    {
        // On Maximized Behaviour Patch
        AdjustWindowOnMaximize();

        // + set restore geometry manually for later.
        mRestoreGeometry = QRect( mLatestOldPos, mLatestOldSize );
    }
    else
    {
        // On Restore Behaviour Patch ( win10 )
        AdjustWindowOnRestore();
    }
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------- Window behaviour patch


void
cCustomMainWindowBase::FixWindowOverlapOnMove()
{
    // Collect screen & geometry information on move
    QRect availableRect = QApplication::desktop()->availableGeometry( this );
    QRect thisRect      = geometry().adjusted( 0, mCaptionHeight, 0, 0 );
    int shift = mCaptionHeight;
    // If the Rect of the window is outside of the bounds ( taking the caption height into account )
    if( !thisRect.intersects( availableRect ) )
    {
        // We move the window in bounds
        if( thisRect.bottom() < availableRect.top() )   move( thisRect.x(),                     availableRect.top()    + shift );
        if( thisRect.top() > availableRect.bottom() )   move( thisRect.x(),                     availableRect.bottom() - shift );
        if( thisRect.right() < availableRect.left() )   move( availableRect.left()    + shift,  thisRect.y() );
        if( thisRect.left() > availableRect.right() )   move( availableRect.right()   - shift,  thisRect.y() );
    }
}


void
cCustomMainWindowBase::FixWindowOverlapOnResize( const  QSize&  iOldSize )
{
    // Collect screen & geometry information on resize 
    QRect availableRect = QApplication::desktop()->availableGeometry( this );
    QRect thisRect      = geometry().adjusted( 0, mCaptionHeight, 0, 0 );

    // If the Rect of the window is outside of the bounds ( taking the caption height into account )
    if( !thisRect.intersects( availableRect ) )
    {
        // We forbid resizing
        resize( iOldSize );
    }
}


void
cCustomMainWindowBase::AdjustWindowOnMaximize()
{
    if(!isMaximized())
        return;

    // Patch window behaviour and size on Maximize according to the available geometry
    int screenNumber    = QApplication::desktop()->screenNumber( this );
    QRect fullRect      = QApplication::desktop()->screenGeometry( screenNumber );
    QRect availableRect = QApplication::desktop()->availableGeometry( screenNumber );

    // Computing shifts
    int adjustLeft      = fullRect.left()   > availableRect.left()  ? +1 : 0;
    int adjustTop       = fullRect.top()    > availableRect.top()   ? +1 : 0;
    int adjustRight     = fullRect.right()  > availableRect.right() ? -1 : 0;
    int adjustBottom    = -1;

    // Adjust Geometry
    availableRect.adjust( adjustLeft, adjustTop, adjustRight, adjustBottom );
    setGeometry( availableRect );

    // Disable OS resize on border when maximized
    tParent::SetBorderWidth( 0 );

    // Set manual maximized state as the resizing done before disabled the os maximized flag.
    mMaximized = true;
}


void
cCustomMainWindowBase::AdjustWindowOnRestore()
{
    // When not maximized, we make sure the border width
    // telling the OS where to resize are reset to default
    if( isMaximized() )
        return;

    // Reset the OS resize on border
    ResetBorderWidth();

    // Remove the manual maximized flag
    mMaximized = false;
}


} // namespace  CFBBWFQ

