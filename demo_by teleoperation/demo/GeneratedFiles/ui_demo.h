/********************************************************************************
** Form generated from reading UI file 'demo.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *demoClass)
    {
        if (demoClass->objectName().isEmpty())
            demoClass->setObjectName(QString::fromUtf8("demoClass"));
        demoClass->resize(600, 400);
        menuBar = new QMenuBar(demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        demoClass->setStatusBar(statusBar);

        retranslateUi(demoClass);

        QMetaObject::connectSlotsByName(demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *demoClass)
    {
        demoClass->setWindowTitle(QApplication::translate("demoClass", "demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class demoClass: public Ui_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_H
