#include "DemoCustomMainCaption.h"


#include <QApplication>
#include <QPainter>


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------- Default values defines


#define  DEFAULT_MINIMUM_WIDTH 312


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cDemoCustomMainCaption::~cDemoCustomMainCaption()
{
    Destroy();
}

cDemoCustomMainCaption::cDemoCustomMainCaption( cDemoCustomMainWindow* parent ) :
    QWidget( parent ),
    mParent( parent ),
    mCloseButton(       NULL ),
    mMaximizeButton(    NULL ),
    mMinimizeButton(    NULL )
{
    Init();
    Build();
    Compose();
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

    QColor bgColor = QColor( 58, 58, 58 );
    QColor bgLightColor = QColor( 73, 73, 73 );
    QColor border_top_Color = QColor( 100, 100, 100 );
    QColor border_bot_Color = QColor( 15, 15, 15 );
    QColor holeColor = QColor( 80, 80, 80, 200 );
    QColor hole_border_top_Color = QColor( 255, 255, 255, 127 );
    QColor hole_border_bot_Color = QColor( 0, 0, 0, 127 );

    int padding = 135;
    int w = width();
    int h = height();
    int h2 = h / 1.5;
    QPainterPath captionBezierPathBg;
    QPainterPath captionBezierPathOutlineTop;
    QPainterPath HoleBezierPathBg;
    QPainterPath HoleBezierPathOutlineBot;

    QPoint  refPointA( 0, 0 );
    QPoint  refPointB( padding, 0 );
    QPoint  refPointC( padding + h2, h2 );
    QPoint  refPointD( w - padding - h2, h2 );
    QPoint  refPointE( w - padding, 0 );
    QPoint  refPointF( w, 0 );
    QPoint  refPointG( w, h );
    QPoint  refPointH( 0, h );

    QPoint  shiftXm1( -1, 0 );
    QPoint  shiftYm1( 0, -1 );
    QPoint  shiftXYm1( -1, -1 );

    QPoint  shiftXp1( -1, 0 );
    QPoint  shiftYp1( 0, -1 );
    QPoint  shiftXYp1( -1, -1 );

    //  A       B                   E       F
    //              C           D
    //  H                                   G

    captionBezierPathBg.moveTo( refPointA );
    captionBezierPathBg.lineTo( refPointB );
    captionBezierPathBg.lineTo( refPointC );
    captionBezierPathBg.lineTo( refPointD );
    captionBezierPathBg.lineTo( refPointE );
    captionBezierPathBg.lineTo( refPointF );
    captionBezierPathBg.lineTo( refPointG );
    captionBezierPathBg.lineTo( refPointH );
    captionBezierPathBg.closeSubpath();
    captionBezierPathBg.setFillRule( Qt::FillRule::OddEvenFill );

    QLinearGradient gradient( 0, 0, w, 0 );
    gradient.setColorAt( 0.0, bgLightColor );
    gradient.setColorAt( 0.5, bgColor );
    gradient.setColorAt( 0.66, bgLightColor );
    gradient.setColorAt( 1.0, bgColor );

    painter.setBrush( gradient );
    painter.setPen( Qt::NoPen );
    painter.drawPath( captionBezierPathBg );

    painter.setBrush( Qt::NoBrush );
    painter.setPen( QPen( border_bot_Color, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin ) );
    painter.drawLine( refPointA, refPointH );
    painter.drawLine( refPointH + shiftYm1, refPointG + shiftYm1 );
    painter.drawLine( refPointF + shiftXm1, refPointG + shiftXm1 );

    captionBezierPathOutlineTop.moveTo( refPointA );
    captionBezierPathOutlineTop.lineTo( refPointB );
    captionBezierPathOutlineTop.lineTo( refPointC );
    captionBezierPathOutlineTop.lineTo( refPointD );
    captionBezierPathOutlineTop.lineTo( refPointE );
    captionBezierPathOutlineTop.lineTo( refPointF );
    painter.setBrush( Qt::NoBrush );
    painter.setPen( QPen( border_top_Color, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin ) );
    painter.drawPath( captionBezierPathOutlineTop );

    HoleBezierPathBg.moveTo( refPointB );
    HoleBezierPathBg.lineTo( refPointC );
    HoleBezierPathBg.lineTo( refPointD );
    HoleBezierPathBg.lineTo( refPointE );
    HoleBezierPathBg.closeSubpath();
    HoleBezierPathBg.setFillRule( Qt::FillRule::OddEvenFill );
    painter.setBrush( holeColor );
    painter.setPen( Qt::NoPen );
    painter.drawPath( HoleBezierPathBg );

    HoleBezierPathOutlineBot.moveTo( refPointB + shiftYm1 );
    HoleBezierPathOutlineBot.lineTo( refPointC + shiftYm1 );
    HoleBezierPathOutlineBot.lineTo( refPointD + shiftYm1 );
    HoleBezierPathOutlineBot.lineTo( refPointE + shiftYm1 );
    painter.setBrush( Qt::NoBrush );
    painter.setPen( QPen( hole_border_bot_Color, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin ) );
    painter.drawPath( HoleBezierPathOutlineBot );

    painter.setBrush( Qt::NoBrush );
    painter.setPen( QPen( hole_border_top_Color, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin ) );
    painter.drawLine( refPointB, refPointE );
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

    mCloseButton->move(     w - buttonWidth,        0 );
    mMaximizeButton->move(  w - buttonWidth * 2,    0 );
    mMinimizeButton->move(  w - buttonWidth * 3,    0 );

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

