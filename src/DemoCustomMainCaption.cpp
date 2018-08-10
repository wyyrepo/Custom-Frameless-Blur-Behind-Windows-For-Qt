#include "DemoCustomMainCaption.h"


#include <QApplication>
#include <QPainter>


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------- Default values defines


#define  DEFAULT_MINIMUM_WIDTH 200
#define  DEFAULT_ACTIVE_BACKGROUND_COLOR Qt::gray
#define  DEFAULT_INACTIVE_BACKGROUND_COLOR Qt::white


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cDemoCustomMainCaption::~cDemoCustomMainCaption()
{
    Destroy();
}

cDemoCustomMainCaption::cDemoCustomMainCaption( tParent* parent ) :
    QWidget( parent ),
    mParent( parent ),
    mCloseButton(       NULL ),
    mMaximizeButton(    NULL ),
    mMinimizeButton(    NULL ),
    mActiveBackgroundColor( DEFAULT_ACTIVE_BACKGROUND_COLOR ),
    mInactiveBackgroundColor( DEFAULT_INACTIVE_BACKGROUND_COLOR )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------- Public customization utilities


void
cDemoCustomMainCaption::ActiveBackgroundColor( const  QColor& iColor )
{
    mActiveBackgroundColor = iColor;
}


const  QColor&
cDemoCustomMainCaption::ActiveBackgroundColor()
{
    return  mActiveBackgroundColor;
}

void
cDemoCustomMainCaption::InactiveBackgroundColor( const  QColor& iColor )
{
    mInactiveBackgroundColor = iColor;
}


const  QColor&
cDemoCustomMainCaption::InactiveBackgroundColor()
{
    return  mInactiveBackgroundColor;
}


//--------------------------------------------------------------------------------------
//----------------------------------------- Custom NC Handling implementation in caption


bool
cDemoCustomMainCaption::HitEmptySpace( long iX, long iY )
{
    QList<QWidget*> list = this->findChildren<QWidget*>();

    for each(QWidget *w in list) {
        QRect g = w->geometry();
        if(g.contains(iX,iY))
            return  false;
    }

    return  true;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Protected Qt event overrides


void
cDemoCustomMainCaption::paintEvent(  QPaintEvent*    event )
{
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing, false );
    QColor  bgColor = mParent->isActiveWindow() ? mActiveBackgroundColor : mInactiveBackgroundColor;

    int w = width();
    int h = height();
    painter.setBrush( bgColor );
    painter.setPen( Qt::NoPen );
    painter.drawRect( 0, 0, w, h );

}


void
cDemoCustomMainCaption::resizeEvent( QResizeEvent *event )
{
    QWidget::resizeEvent(event);
    Compose();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Private Qt Slots


void
cDemoCustomMainCaption::ProcessCloseClicked()
{
    mParent->close();
    QApplication::quit();
    QApplication::exit();
}

void
cDemoCustomMainCaption::ProcessMaximizeClicked()
{
    if( mParent->CheckCustomWindowMaximizedState() )
    {
        mParent->Restore();
    }
    else
    {
        mParent->showMaximized();
    }
}


void
cDemoCustomMainCaption::ProcessMinimizeClicked()
{
    mParent->showMinimized();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cDemoCustomMainCaption::Init()
{
    if( !mCloseButton )     mCloseButton    = new  ::CFBBWFQ::cCustomCaptionButton( this );
    if( !mMaximizeButton )  mMaximizeButton = new  ::CFBBWFQ::cCustomCaptionButton( this );
    if( !mMinimizeButton )  mMinimizeButton = new  ::CFBBWFQ::cCustomCaptionButton( this );
}


void
cDemoCustomMainCaption::Build()
{
    mCloseButton->SetShape( ::CFBBWFQ::cCustomCaptionButton::eShape::kClose );
    mMaximizeButton->SetShape( ::CFBBWFQ::cCustomCaptionButton::eShape::kMaximize );
    mMinimizeButton->SetShape( ::CFBBWFQ::cCustomCaptionButton::eShape::kMinimize );

    mCloseButton->SetHoveredBackgroundColor( QColor( 230, 20, 35 ) );

    setMinimumWidth( DEFAULT_MINIMUM_WIDTH );

    QObject::connect( mCloseButton, SIGNAL( clicked() ), this, SLOT( ProcessCloseClicked() ) );
    QObject::connect( mMaximizeButton, SIGNAL( clicked() ), this, SLOT( ProcessMaximizeClicked() ) );
    QObject::connect( mMinimizeButton, SIGNAL( clicked() ), this, SLOT( ProcessMinimizeClicked() ) );
}


void
cDemoCustomMainCaption::Compose()
{
    int w = width();
    int h = height();

    float buttonRatio   = 1.5f;
    int buttonHeight    = h;
    int buttonWidth     = buttonHeight * buttonRatio;

    QSize buttonSize( buttonWidth, h );
    mCloseButton->resize( buttonSize );
    mMaximizeButton->resize( buttonSize );
    mMinimizeButton->resize( buttonSize );

    int n = 0;
    mCloseButton->move(     w - buttonWidth * ++n, 0 );
    mMaximizeButton->move(  w - buttonWidth * ++n, 0 );
    mMinimizeButton->move(  w - buttonWidth * ++n, 0 );
}


void
cDemoCustomMainCaption::Destroy()
{
    delete  mCloseButton;
    delete  mMaximizeButton;
    delete  mMinimizeButton;

    mCloseButton = 0;
    mMaximizeButton = 0;
    mMinimizeButton = 0;
}

