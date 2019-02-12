#include "demo.h"
bool enableSig=0;
demo::demo(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

demo::~demo()
{

}
void demo:: mousePressEvent( QMouseEvent * event )
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		enableSig= !enableSig;    
    }

}