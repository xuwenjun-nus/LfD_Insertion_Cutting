#ifndef DEMO_H
#define DEMO_H
#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include "ui_demo.h"
#include <QMouseEvent>
class demo : public QMainWindow
{
	Q_OBJECT

public:
	demo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~demo();
	void mousePressEvent( QMouseEvent * event );
private:
	Ui::demoClass ui;
};

#endif // DEMO_H
