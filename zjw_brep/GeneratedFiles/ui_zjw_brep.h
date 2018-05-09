/********************************************************************************
** Form generated from reading UI file 'zjw_brep.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZJW_BREP_H
#define UI_ZJW_BREP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "zjw_opengl.h"

QT_BEGIN_NAMESPACE

class Ui_zjw_brepClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    ZjwOpenGL *openGLWidget;
    QTabWidget *tabWidget;
    QWidget *Brep;
    QLabel *renderModel;
    QLabel *solidModel;
    QRadioButton *solid1RadioButton;
    QRadioButton *solid2RadioButton;
    QRadioButton *solid3RadioButton;
    QRadioButton *solid4RadioButton;
    QRadioButton *wireFrameRadioButton;
    QRadioButton *faceRadioButton;
    QWidget *other;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *zjw_brepClass)
    {
        if (zjw_brepClass->objectName().isEmpty())
            zjw_brepClass->setObjectName(QStringLiteral("zjw_brepClass"));
        zjw_brepClass->resize(850, 554);
        actionOpen = new QAction(zjw_brepClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(zjw_brepClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new ZjwOpenGL(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(140, 0, 761, 581));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(6, -1, 131, 491));
        Brep = new QWidget();
        Brep->setObjectName(QStringLiteral("Brep"));
        renderModel = new QLabel(Brep);
        renderModel->setObjectName(QStringLiteral("renderModel"));
        renderModel->setGeometry(QRect(10, 10, 71, 16));
        solidModel = new QLabel(Brep);
        solidModel->setObjectName(QStringLiteral("solidModel"));
        solidModel->setGeometry(QRect(10, 80, 71, 21));
        solid1RadioButton = new QRadioButton(Brep);
        solid1RadioButton->setObjectName(QStringLiteral("solid1RadioButton"));
        solid1RadioButton->setGeometry(QRect(10, 110, 89, 16));
        solid1RadioButton->setChecked(false);
        solid2RadioButton = new QRadioButton(Brep);
        solid2RadioButton->setObjectName(QStringLiteral("solid2RadioButton"));
        solid2RadioButton->setGeometry(QRect(10, 130, 89, 16));
        solid3RadioButton = new QRadioButton(Brep);
        solid3RadioButton->setObjectName(QStringLiteral("solid3RadioButton"));
        solid3RadioButton->setGeometry(QRect(10, 150, 89, 16));
        solid4RadioButton = new QRadioButton(Brep);
        solid4RadioButton->setObjectName(QStringLiteral("solid4RadioButton"));
        solid4RadioButton->setGeometry(QRect(10, 170, 89, 16));
        wireFrameRadioButton = new QRadioButton(Brep);
        wireFrameRadioButton->setObjectName(QStringLiteral("wireFrameRadioButton"));
        wireFrameRadioButton->setGeometry(QRect(10, 30, 121, 16));
        wireFrameRadioButton->setChecked(false);
        faceRadioButton = new QRadioButton(Brep);
        faceRadioButton->setObjectName(QStringLiteral("faceRadioButton"));
        faceRadioButton->setGeometry(QRect(10, 50, 89, 16));
        faceRadioButton->setChecked(true);
        tabWidget->addTab(Brep, QString());
        other = new QWidget();
        other->setObjectName(QStringLiteral("other"));
        tabWidget->addTab(other, QString());
        zjw_brepClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(zjw_brepClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 850, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        zjw_brepClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(zjw_brepClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        zjw_brepClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(zjw_brepClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        zjw_brepClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(zjw_brepClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(zjw_brepClass);
    } // setupUi

    void retranslateUi(QMainWindow *zjw_brepClass)
    {
        zjw_brepClass->setWindowTitle(QApplication::translate("zjw_brepClass", "zjw_brep", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("zjw_brepClass", "Open", Q_NULLPTR));
        renderModel->setText(QApplication::translate("zjw_brepClass", "render model", Q_NULLPTR));
        solidModel->setText(QApplication::translate("zjw_brepClass", "solid model", Q_NULLPTR));
        solid1RadioButton->setText(QApplication::translate("zjw_brepClass", "solid 1", Q_NULLPTR));
        solid2RadioButton->setText(QApplication::translate("zjw_brepClass", "solid 2", Q_NULLPTR));
        solid3RadioButton->setText(QApplication::translate("zjw_brepClass", "solid 3", Q_NULLPTR));
        solid4RadioButton->setText(QApplication::translate("zjw_brepClass", "solid 4", Q_NULLPTR));
        wireFrameRadioButton->setText(QApplication::translate("zjw_brepClass", "wire-frame model", Q_NULLPTR));
        faceRadioButton->setText(QApplication::translate("zjw_brepClass", "face model", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Brep), QApplication::translate("zjw_brepClass", "Brep", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(other), QApplication::translate("zjw_brepClass", "other", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("zjw_brepClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class zjw_brepClass: public Ui_zjw_brepClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZJW_BREP_H
