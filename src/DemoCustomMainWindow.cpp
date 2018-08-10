#include "DemoCustomMainWindow.h"


#include "DemoCustomMainCaption.h"


#include <QApplication>
#include <QResizeEvent>


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cDemoCustomMainWindow::~cDemoCustomMainWindow()
{
    Destroy();
}


cDemoCustomMainWindow::cDemoCustomMainWindow( QWidget *parent ) :
    tParent( parent ),
    mCustomCaption( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------- Buffer methods for customization of the caption


void
cDemoCustomMainWindow::ActiveCaptionBackgroundColor( const  QColor& iColor )
{
    mCustomCaption->ActiveBackgroundColor( iColor );
}


const  QColor&
cDemoCustomMainWindow::ActiveCaptionBackgroundColor()
{
    return  mCustomCaption->ActiveBackgroundColor();
}


void
cDemoCustomMainWindow::InactiveCaptionBackgroundColor( const  QColor& iColor )
{
    mCustomCaption->InactiveBackgroundColor( iColor );
}


const  QColor&
cDemoCustomMainWindow::InactiveCaptionBackgroundColor()
{
    return  mCustomCaption->InactiveBackgroundColor();
}


//--------------------------------------------------------------------------------------
//--------------------------------- Protected Non-Client OS behaviour handling overrides


bool
cDemoCustomMainWindow::NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )
{
    // Final Implementation

    // Custom processing for sending "hit caption" message to the OS
    // Return true:  the OS handles window move under mouse cursor like a native window
    // Return false: the mouse Events remain within the window

    bool  eligible = tParent::NCHitCaption( iRect, iBorderWidth, iX, iY );

    if(!eligible)
        return  false;

    long localx = iX - iRect.left();
    long localy = iY - iRect.top();
    // Custom Caption Widget Must Implement HitEmptySpace
    return  mCustomCaption->HitEmptySpace(localx,localy);
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt events override


void
cDemoCustomMainWindow::resizeEvent( QResizeEvent* event )
{
    tParent::resizeEvent( event );
    // Resize of internal geometry
    Compose();
}


void
cDemoCustomMainWindow::closeEvent( QCloseEvent* event )
{
    QApplication::quit();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cDemoCustomMainWindow::Init()
{
    // Allocation
    if( !mCustomCaption )  mCustomCaption = new  cDemoCustomMainCaption(this);
}


void
cDemoCustomMainWindow::Build()
{
    // Setup
    setMinimumSize( mCustomCaption->minimumWidth(), CaptionHeight() );
}


void
cDemoCustomMainWindow::Compose()
{
    // Geometry
    mCustomCaption->setGeometry( CaptionGeometry() );
}

void
cDemoCustomMainWindow::Destroy()
{
    // De-Allocation
    delete  mCustomCaption;

    mCustomCaption = 0;
}

