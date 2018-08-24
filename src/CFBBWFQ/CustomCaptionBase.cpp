#include "CustomCaptionBase.h"


#include <QApplication>
#include <QPainter>


namespace  CFBBWFQ
{


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cCustomCaptionBase::~cCustomCaptionBase()
{
}

cCustomCaptionBase::cCustomCaptionBase( QWidget* parent ) :
    QWidget( parent )
{
}


//--------------------------------------------------------------------------------------
//----------------------------------------- Custom NC Handling implementation in caption


bool
cCustomCaptionBase::HitEmptySpace( long iX, long iY )
{
    return  true;
}


} // namespace  CFBBWFQ

