#pragma once


#include <QObject>
#include <QPushButton>


namespace  CFBBWFQ
{


class cCustomCaptionButton :
    public QPushButton
{

    Q_OBJECT

    typedef  QPushButton  tParent;

public:
    // Custom enums for setting button behaviour & style.

// Button shape
enum  class  eShape
{
    kNone = 0,
    kClose,
    kMaximize,
    kMinimize,
    kLeftArrow,
    kRightArrow,
};

// Button background shape & style
public:
enum  class  eBackground
{
    kSquare = 0,
    kDisk,
};

// Button behaviour state
private:
enum  class  eButtonState
{
    kNone           = 0,    // 0000
    kHovered        = 1,    // 0001
    kPressed        = 2,    // 0010
    kPressedHovered = 3,    // 0011
};

public:
    // Construction / Destruction
    virtual  ~cCustomCaptionButton();
    cCustomCaptionButton( QWidget *parent = Q_NULLPTR );

public:
    // Public Style Setup Accessors
    void  SetBackgroundColor( const  QColor&  iColor );
    void  SetHoveredBackgroundColor( const  QColor&  iColor );
    void  SetPressedBackgroundColor( const  QColor&  iColor );
    const  QColor&  GetBackgroundColor()  const;
    const  QColor&  GetHoveredBackgroundColor()  const;
    const  QColor&  GetPressedBackgroundColor()  const;
    void  SetColor( const  QColor&  iColor );
    void  SetHoveredColor( const  QColor&  iColor );
    void  SetPressedColor( const  QColor&  iColor );
    const  QColor&  GetColor()  const;
    const  QColor&  GetHoveredColor()  const;
    const  QColor&  GetPressedColor()  const;
    void  SetShape( const  eShape&  iShape );
    const  eShape&  GetShape()  const;
    void  SetBackgroundShape( const  eBackground&  iShape );
    const  eBackground&  GetBackgroundShape()  const;
    void  SetSize( int iSize );
    int  GetSize()  const;

public:
    // Public State Accessors
    bool IsHovered();
    bool IsPressed();

public slots:signals:
    void  DoubleClicked();


protected:
    // Protected Qt event overrides
    virtual  void  enterEvent( QEvent* event )  override;
    virtual  void  leaveEvent( QEvent* event )  override;
    virtual  void  mousePressEvent( QMouseEvent* event )  override;
    virtual  void  mouseReleaseEvent( QMouseEvent* event )  override;
    virtual  void  mouseDoubleClickEvent( QMouseEvent* event )  override;
    virtual  void  paintEvent( QPaintEvent* event )  override;

private:
    // Private Data Members
    bool    mHovered;
    bool    mPressed;
    QColor  mBgColor;
    QColor  mHoveredBgColor;
    QColor  mPressedBgColor;
    QColor  mPressedHoveredBgColor;
    QColor  mColor;
    QColor  mHoveredColor;
    QColor  mPressedColor;
    QColor  mPressedHoveredColor;
    eShape  mShape;
    int     mSize;
    eBackground mBackground;

};


} // namespace  CFBBWFQ

