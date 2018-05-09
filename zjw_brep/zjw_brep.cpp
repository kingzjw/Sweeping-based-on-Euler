/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/

#include "zjw_brep.h"

void zjw_brep::clickSolid1RB()
{
	ui.openGLWidget->solidType = 0;
	ui.openGLWidget->solidModel = 1;
	ui.openGLWidget->initHalfEdge();
	ui.openGLWidget->initParam();
	ui.openGLWidget->update();
}

void zjw_brep::clickSolid2RB()
{
	ui.openGLWidget->solidType = 0;
	ui.openGLWidget->solidModel = 2;
	ui.openGLWidget->initHalfEdge();
	ui.openGLWidget->initParam();
	ui.openGLWidget->update();
}

void zjw_brep::clickSolid3RB()
{
	ui.openGLWidget->solidType = 0;
	ui.openGLWidget->solidModel = 3;
	ui.openGLWidget->initHalfEdge();
	ui.openGLWidget->initParam();
	ui.openGLWidget->update();
}

void zjw_brep::clickSolid4RB()
{
	ui.openGLWidget->solidType = 0;
	ui.openGLWidget->solidModel = 4;
	ui.openGLWidget->initHalfEdge();
	ui.openGLWidget->initParam();
	ui.openGLWidget->update();
}

void zjw_brep::clickFaceRB()
{
	ui.openGLWidget->renderMode = 1;
	ui.openGLWidget->update();
}

void zjw_brep::clickWireFrameRB()
{
	ui.openGLWidget->renderMode = 0;
	ui.openGLWidget->update();
}

void zjw_brep::clickedOpenFileAction()
{
	ui.openGLWidget->solidType = 1;
	QString filename = QFileDialog::getOpenFileName(this, tr("Input"), ".", "Image file(*.zjwbrep)", 0);

	std::string st = filename.toStdString();
	std::string stt = "";
	for (int i = 0; i < st.length(); i++)
	{
		if (st[i] == '/') 
			stt += "//";
		else 
			stt += st[i];
	}
	std::cout << "you choose the file: " << std::endl << stt << endl;;
	ui.openGLWidget->zjwBrepFile->ver2dimList.clear();
	ui.openGLWidget->zjwBrepFile->loadZjwBrepFile(stt);
	//更新file solid
	ui.openGLWidget->initFileLoadSolid();
	ui.openGLWidget->initParam();
	ui.openGLWidget->update();
}

zjw_brep::zjw_brep(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//-----------------------------button 进行处理-----------------------------
	solidBttnGroup = new QButtonGroup;
	renderModeBttnGroup = new QButtonGroup;
	solidBttnGroup->addButton(ui.solid1RadioButton);
	solidBttnGroup->addButton(ui.solid2RadioButton);
	solidBttnGroup->addButton(ui.solid3RadioButton);
	solidBttnGroup->addButton(ui.solid4RadioButton);

	renderModeBttnGroup->addButton(ui.faceRadioButton);
	renderModeBttnGroup->addButton(ui.wireFrameRadioButton);
	ui.solid1RadioButton->setChecked(true);

	//-------------------------信号处理---------------------------
	connect(ui.solid1RadioButton, SIGNAL(clicked()), this, SLOT(clickSolid1RB()));
	connect(ui.solid2RadioButton, SIGNAL(clicked()), this, SLOT(clickSolid2RB()));
	connect(ui.solid3RadioButton, SIGNAL(clicked()), this, SLOT(clickSolid3RB()));
	connect(ui.solid4RadioButton, SIGNAL(clicked()), this, SLOT(clickSolid4RB()));
	connect(ui.faceRadioButton, SIGNAL(clicked()), this, SLOT(clickFaceRB()));
	connect(ui.wireFrameRadioButton, SIGNAL(clicked()), this, SLOT(clickWireFrameRB()));

	//打开文件
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(clickedOpenFileAction()));
}

zjw_brep::~zjw_brep()
{
	delete solidBttnGroup;
	delete renderModeBttnGroup;
}
