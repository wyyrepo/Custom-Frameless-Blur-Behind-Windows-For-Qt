#pragma once


#include <QMainWindow>


// Primary abstract level for custom windows
// Handles OS events and OS API calls
// You should not derive this class


namespace  CFBBWFQ
{


class cAbstractFramelessBlurBehindWindow :
    public QMainWindow
{

    typedef  QMainWindow  tParent;

public:
    // Construction / Destruction
    virtual  ~cAbstractFramelessBlurBehindWindow();
    cAbstractFramelessBlurBehindWindow( QWidget*  parent = Q_NULLPTR );

protected:
    // Protected Non-Client OS geometry setup for behaviour override in childrens
    int     BorderWidth();
    int     DefaultBorderWidth();
    void    SetBorderWidth( int iValue );
    void    ResetBorderWidth();

private:
    // Private WinAPI flags setup
    void    InitNativeGlass();
    void    InitNativeFrameless();

private:
    // Protected Non-Client OS behaviour handling
    void  WM_NCHITTEST_Event_Handler( int iX, int iY, long *oResult );
    bool  NCHitLeftBorder(     const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitRightBorder(    const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitTopBorder(      const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitBottomBorder(   const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitTopLeftCorner(  const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitTopRightCorner( const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitBotRightCorner( const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
    bool  NCHitBotLeftCorner(  const  QRect&  iRect, const long iBorderWidth, long iX, long iY );
protected:
    virtual  bool  NCHitCaption(        const  QRect&  iRect, const long iBorderWidth, long iX, long iY );

protected:
    // Protected Qt / WinAPI native events override
    virtual  bool  nativeEvent( const  QByteArray& eventType, void* message, long* result)  override;

private:
    // Non-Client OS border geometry
    int  mBorderWidth;
};


} // namespace  CFBBWFQ

