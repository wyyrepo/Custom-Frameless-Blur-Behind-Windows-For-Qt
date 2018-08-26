#include "CustomMainWindow.h"


#include <QApplication>


namespace  CFBBWFQ
{


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cCustomMainWindow::~cCustomMainWindow()
{
    tSelf::Destroy();
}


cCustomMainWindow::cCustomMainWindow( QWidget *parent ) :
    tParent( parent ),
    mCaptionWidget( NULL )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Caption API


cCustomCaptionBase*
cCustomMainWindow::CaptionWidget()
{
    return  mCaptionWidget;
}


void
cCustomMainWindow::SetCaptionWidget( cCustomCaptionBase* iCaptionWidget )
{
    if( mCaptionWidget )
    {
        // This is owner of mCaptionWidget, responsibility to delete
        delete  mCaptionWidget;
        mCaptionWidget = NULL;
    }

    if( iCaptionWidget )
    {
        mCaptionWidget = iCaptionWidget;
        iCaptionWidget->setParent( this );
        iCaptionWidget->show();
        QObject::connect( mCaptionWidget, SIGNAL( CloseClicked() ), this, SLOT( ProcessCloseClicked() ) );
        QObject::connect( mCaptionWidget, SIGNAL( MaximizeClicked() ), this, SLOT( ProcessMaximizeClicked() ) );
        QObject::connect( mCaptionWidget, SIGNAL( MinimizeClicked() ), this, SLOT( ProcessMinimizeClicked() ) );
    }
}


QWidget*
cCustomMainWindow::CenterWidget()
{
    return  mCenterWidget;
}


void
cCustomMainWindow::SetCenterWidget( QWidget* iCenterWidget )
{
    if( mCenterWidget )
    {
        delete  mCenterWidget;
        mCenterWidget = NULL;
    }

    if( iCenterWidget )
    {
        mCenterWidget = iCenterWidget;
        iCenterWidget->setParent( this );
        iCenterWidget->show();
    }
}


//--------------------------------------------------------------------------------------
//--------------------------------- Protected Non-Client OS behaviour handling overrides


bool
cCustomMainWindow::NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    bool  eligible = tParent::NCHitCaption( iRect, iBorderWidth, iX, iY );
    QPoint local = mapFromGlobal( QPoint( iX, iY ) );

    if(!eligible)
        return  false;

    if( mCaptionWidget )
    {
        return  mCaptionWidget->HitEmptySpace( local.x(), local.y() );
    }
    else
    {
        return  true;
    }
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt events override


void
cCustomMainWindow::resizeEvent( QResizeEvent*  event )
{
    // Very important !
    tParent::resizeEvent( event );

    // Recompute internal geometry
    tSelf::Compose();
}



//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Private Qt Slots


void
cCustomMainWindow::ProcessCloseClicked()
{
    close();
}

void
cCustomMainWindow::ProcessMaximizeClicked()
{
    if( CheckCustomWindowMaximizedState() )
    {
        Restore();
    }
    else
    {
        showMaximized();
    }
}


void
cCustomMainWindow::ProcessMinimizeClicked()
{
    showMinimized();
}


//--------------------------------------------------------------------------------------
//--------------------------------- Protected Non-Client OS behaviour handling overrides


void
cCustomMainWindow::Init()
{
    // Not much there ATM but keep for consistency with the rest of the API GUI convention in my other Libs.
    mCaptionWidget = NULL;
}


void
cCustomMainWindow::Build()
{
    // Not much there ATM but keep for consistency with the rest of the API GUI convention in my other Libs.
}


void
cCustomMainWindow::Compose()
{
    if( mCaptionWidget )
    {
        mCaptionWidget->setGeometry( CaptionGeometry() );
    }

    if( mCenterWidget )
    {
        mCenterWidget->setGeometry( ContentsGeometry() );
    }
}


void
cCustomMainWindow::Destroy()
{
    if( mCaptionWidget )
    {
        // This is owner of mCaptionWidget, responsibility to delete
        delete  mCaptionWidget;
        mCaptionWidget = NULL;
    }
}


} // namespace  CFBBWFQ

