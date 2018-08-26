#pragma once


#include <QWidget>


#include "CustomMainWindowBase.h"
#include "CustomCaptionBase.h"


// Tertiary level for custom windows
// Handles Custom events and provides Custom API calls
// You can derive this class if you want more customization


namespace  CFBBWFQ
{


class cCustomMainWindow :
    public cCustomMainWindowBase
{
    Q_OBJECT

    typedef  cCustomMainWindowBase  tParent;
    typedef  cCustomMainWindow      tSelf;

public:
    // Construction / Destruction
    virtual  ~cCustomMainWindow();
    cCustomMainWindow( QWidget* parent = Q_NULLPTR );

public:
    // Center / Caption API
    cCustomCaptionBase*  CaptionWidget();  // Return pointer to mCaptionWidget, this keeps owning it
    void  SetCaptionWidget( cCustomCaptionBase* iCaptionWidget );  // Pass pointer to mCaptionWidget, becoming owner
    //-
    QWidget* CenterWidget();  // Return pointer to mCenterWidget, keeps owning it.
    void  SetCenterWidget( QWidget* iCenterWidget ); // Acquire ownership

protected:
    // Protected Non-Client OS behaviour handling overrides
    virtual  bool  NCHitCaption( const  QRect&  iRect, const  long iBorderWidth, long iX, long iY )  override;

protected:
    // Protected Qt events override
    virtual  void  resizeEvent( QResizeEvent*  event )  override;

private  slots:
    // Private Qt Slots
    void  ProcessCloseClicked();
    void  ProcessMaximizeClicked();
    void  ProcessMinimizeClicked();

private:
    // Internal GUI management
    void  Init();       // allocate GUI members
    void  Build();      // set GUI members flags, styles, properties
    void  Compose();    // compose members in GUI
    void  Destroy();    // delete GUI members

private:
    cCustomCaptionBase* mCaptionWidget;
    QWidget* mCenterWidget;
};


} // namespace  CFBBWFQ

