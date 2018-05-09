/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/

#ifndef QT_DYNAMIC_PLY_WIDGET_HPP
#define QT_DYNAMIC_PLY_WIDGET_HPP

#include <QGLWidget>
#include <QKeyEvent>
#include <GL\glut.h>
#include "zjw_euler.h"
#include "zjw_halfedge.h"
#include "zjw_file.h"

using namespace zjw_euler;
using namespace zjw_halfedge;

class ZjwOpenGL : public  QGLWidget {
	Q_OBJECT

public:
	ZjwOpenGL(QWidget * parent = Q_NULLPTR);
	~ZjwOpenGL();

protected:
	//redifine the virtual function
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	//方向键平移
	void keyPressEvent(QKeyEvent *event);
	// redefine in QWidget class
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	//滚轮放大放小
	void wheelEvent(QWheelEvent * event);
	//时间事件
	void timerEvent(QTimerEvent *);

public:
	//use in paintGL function
	void render();  
	void draw(Solid* solid);
	void drawXianKuang(Solid* solid);
	void initHalfEdge();
	void initFileLoadSolid();

public:
	GLfloat	 *lightPos;
	GLfloat scale;
	//标记当前是stop 或者是paly 的状态
	bool isPlay;
	//3 旋转的速度
	int playSpeed;
	//50ms 旋转的刷新时间
	int palyIntervalTime;
	int timeID;  //即使器的id

	//0: 线框  1: face
	int renderMode;
private:
	//局部坐标系下的
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	//世界坐标系下的
	GLfloat rotationWorldX;
	GLfloat rotationWorldY;
	GLfloat rotationWorldZ;
	QPoint lastPoint;

	//-----------------------------针对应用进行扩展--------------
public:
	//1,2,3,4;显示渲染不同的solid 的模型
	int solidModel;
	//0: 内置solid  1: 表示文件读入solid
	int solidType;
	Solid *solid;
	Solid *fileSolid;
	const int num = 2000;
	double verList[1000][3];
	//归一化后的坐标
	double verNormalList[1000][3];
	unsigned char verColor[1000][3];
	GLUtesselator* obj = gluNewTess();


	ZjwBrepFile * zjwBrepFile;
	void getVerNormal();
	void initParam();

};

#endif