#pragma once


#include <QObject>
#include <QWidget>


namespace  CFBBWFQ
{


class cCustomCaptionBase :
    public QWidget
{

    Q_OBJECT

    typedef  QWidget                tParent;
    typedef  cCustomCaptionBase     tSelf;

public:
    // Construction / Destruction
    virtual  ~cCustomCaptionBase();
    cCustomCaptionBase( QWidget* parent = Q_NULLPTR );

public:
    // Custom NC Handling implementation in caption
    virtual  bool  HitEmptySpace( long iX, long iY );

public slots:signals:
    // Private Qt Slots
    void  CloseClicked();
    void  MaximizeClicked();
    void  MinimizeClicked();
};


} // namespace  CFBBWFQ

