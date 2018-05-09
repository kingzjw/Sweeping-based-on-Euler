/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/

#ifndef ZJW_BREP_H
#define ZJW_BREP_H

#include <QtWidgets/QMainWindow>
#include <QButtonGroup>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <string>
#include <iostream>
#include "ui_zjw_brep.h"

class zjw_brep : public QMainWindow
{
	Q_OBJECT

public slots:
	void clickSolid1RB();
	void clickSolid2RB();
	void clickSolid3RB();
	void clickSolid4RB();
	void clickFaceRB();
	void clickWireFrameRB();

	void clickedOpenFileAction();

public:
	zjw_brep(QWidget *parent = 0);
	~zjw_brep();

private:
	Ui::zjw_brepClass ui;
	QButtonGroup * renderModeBttnGroup;
	QButtonGroup * solidBttnGroup;
};

#endif // ZJW_BREP_H
