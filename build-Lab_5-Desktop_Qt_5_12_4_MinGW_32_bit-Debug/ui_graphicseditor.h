/********************************************************************************
** Form generated from reading UI file 'graphicseditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSEDITOR_H
#define UI_GRAPHICSEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicsEditor
{
public:
    QAction *BackColor;
    QAction *SetPen;
    QAction *Clear;
    QAction *AddFigure;
    QAction *DeleteFigure;
    QAction *Eraser;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *GraphicsEditor)
    {
        if (GraphicsEditor->objectName().isEmpty())
            GraphicsEditor->setObjectName(QString::fromUtf8("GraphicsEditor"));
        GraphicsEditor->resize(1086, 740);
        BackColor = new QAction(GraphicsEditor);
        BackColor->setObjectName(QString::fromUtf8("BackColor"));
        SetPen = new QAction(GraphicsEditor);
        SetPen->setObjectName(QString::fromUtf8("SetPen"));
        Clear = new QAction(GraphicsEditor);
        Clear->setObjectName(QString::fromUtf8("Clear"));
        AddFigure = new QAction(GraphicsEditor);
        AddFigure->setObjectName(QString::fromUtf8("AddFigure"));
        DeleteFigure = new QAction(GraphicsEditor);
        DeleteFigure->setObjectName(QString::fromUtf8("DeleteFigure"));
        Eraser = new QAction(GraphicsEditor);
        Eraser->setObjectName(QString::fromUtf8("Eraser"));
        centralwidget = new QWidget(GraphicsEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        GraphicsEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GraphicsEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1086, 20));
        GraphicsEditor->setMenuBar(menubar);
        toolBar = new QToolBar(GraphicsEditor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        GraphicsEditor->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(GraphicsEditor);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        GraphicsEditor->addToolBar(Qt::TopToolBarArea, toolBar_2);
        GraphicsEditor->insertToolBarBreak(toolBar_2);

        toolBar->addAction(BackColor);
        toolBar->addAction(SetPen);
        toolBar->addAction(Clear);
        toolBar->addAction(AddFigure);
        toolBar->addAction(DeleteFigure);
        toolBar->addAction(Eraser);

        retranslateUi(GraphicsEditor);

        QMetaObject::connectSlotsByName(GraphicsEditor);
    } // setupUi

    void retranslateUi(QMainWindow *GraphicsEditor)
    {
        GraphicsEditor->setWindowTitle(QApplication::translate("GraphicsEditor", "MainWindow", nullptr));
        BackColor->setText(QApplication::translate("GraphicsEditor", "\320\244\320\276\320\275", nullptr));
        SetPen->setText(QApplication::translate("GraphicsEditor", "\320\237\320\265\321\200\320\276", nullptr));
        Clear->setText(QApplication::translate("GraphicsEditor", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260", nullptr));
        AddFigure->setText(QApplication::translate("GraphicsEditor", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\204\320\270\320\263\321\203\321\200\321\203", nullptr));
        DeleteFigure->setText(QApplication::translate("GraphicsEditor", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\204\320\270\320\263\321\203\321\200\321\203", nullptr));
        Eraser->setText(QApplication::translate("GraphicsEditor", "\320\233\320\260\321\201\321\202\320\270\320\272", nullptr));
        toolBar->setWindowTitle(QApplication::translate("GraphicsEditor", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QApplication::translate("GraphicsEditor", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphicsEditor: public Ui_GraphicsEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSEDITOR_H
