#include "CustomMainWindow.h"


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


QWidget*

cCustomMainWindow::CaptionWidget()
{
    return  mCaptionWidget;
}


void
cCustomMainWindow::SetCaptionWidget( QWidget* iCaptionWidget )
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

        //TMP:debug
        iCaptionWidget->setStyleSheet( "background:red;" );
    }
}


//--------------------------------------------------------------------------------------
//--------------------------------- Protected Non-Client OS behaviour handling overrides


bool
cCustomMainWindow::NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    bool  eligible = tParent::NCHitCaption( iRect, iBorderWidth, iX, iY );

    if(!eligible)
        return  false;

    if( mCaptionWidget )
    {
        // Delegate call to caption.
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

