#pragma once


#include <QWidget>


#include "CustomMainWindowBase.h"


// Tertiary level for custom windows
// Handles Custom events and provides Custom API calls
// You can derive this class if you want more customization


namespace  CFBBWFQ
{


class cCustomMainWindow :
    public cCustomMainWindowBase
{

    typedef  cCustomMainWindowBase  tParent;
    typedef  cCustomMainWindow      tSelf;

public:
    // Construction / Destruction
    virtual  ~cCustomMainWindow();
    cCustomMainWindow( QWidget* parent = Q_NULLPTR );

public:
    // Caption API
    QWidget*  CaptionWidget();  // Return pointer to mCaptionWidget, this keeps owning it
    void  SetCaptionWidget( QWidget* iCaptionWidget );  // Pass pointer to mCaptionWidget, becoming owner

protected:
    // Protected Non-Client OS behaviour handling overrides
    virtual  bool  NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )  override;

protected:
    // Protected Qt events override
    virtual  void  resizeEvent( QResizeEvent*  event )  override;

private:
    // Internal GUI management
    void  Init();       // allocate GUI members
    void  Build();      // set GUI members flags, styles, properties
    void  Compose();    // compose members in GUI
    void  Destroy();    // delete GUI members

private:
    QWidget* mCaptionWidget;
};


} // namespace  CFBBWFQ

