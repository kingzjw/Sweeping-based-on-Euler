/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/

//-----------------------zjw opengl in qt----------------

#include "zjw_opengl.h"
#include <QtOpenGL>
#include <QtGui>
#include <QString>
#include <gl/GLU.H>
#include<iostream>
using namespace std;

//----------------in order to render the hole-------------------------------

void CALLBACK beginCallback(GLenum which)
{
	glBegin(which);
}
void CALLBACK errorCallback(GLenum errorCode)
{
	const GLubyte *estring;
	estring = gluErrorString(errorCode);
	fprintf(stderr, "Tessellation Error: %s\n", estring);
	exit(0);
}
void CALLBACK endCallback(void)
{
	glEnd();
}
void CALLBACK vertexCallback(GLvoid *vertex)
{
	const GLdouble *pointer;
	pointer = (GLdouble *)vertex;
	glVertex3dv(pointer);
}

//----------------end in order to render the hole-------------------------------

ZjwOpenGL::ZjwOpenGL(QWidget * parent) : QGLWidget(parent) {
	lightPos = new GLfloat[4];
	lightPos[0] = 0.0f;
	lightPos[1] = 0.0f;
	lightPos[2] = 300.0f;
	lightPos[3] = 1.0f;
	//end
	rotationX = 0;
	rotationY = 0;
	rotationZ = 10;
	rotationWorldX = 0;
	rotationWorldY = 0;
	rotationWorldZ = 10;
	scale = 1.0;

	//播放设置
	playSpeed = 3;
	palyIntervalTime = 75;
	isPlay = true;


	solid = nullptr;
	fileSolid = nullptr;
	solidType = 0;
	renderMode = 1;
	solidModel = 1;
	initHalfEdge();
	zjwBrepFile = new ZjwBrepFile;
}

ZjwOpenGL::~ZjwOpenGL() {
	delete zjwBrepFile;
}


void ZjwOpenGL::initParam()
{
	rotationX = 0;
	rotationY = 0;
	rotationZ = 10;
	rotationWorldX = 0;
	rotationWorldY = 0;
	rotationWorldZ = 10;
	scale = 1.0;
}

void ZjwOpenGL::initializeGL()
{
	//为了使移动有效果
	setFocusPolicy(Qt::StrongFocus);

	qglClearColor(Qt::black);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	//对3D进行光滑
	glEnable(GL_SMOOTH);
	//glEnable(GL_FLAT);
	//设置光照
	glEnable(GL_LIGHTING);

	GLfloat ambientLight[] = { 0.4f,0.4f,0.4f,1.0f };//三种光照的强度
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glEnable(GL_LIGHT0);

	//设置反射材料属性
	GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };//镜面反射属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 50);  //0-128 设置镜面指数，越大，亮度越大，越集中

											   //设置环境光，散射光的材料属性
	glEnable(GL_COLOR_MATERIAL);  //启用颜色追踪
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	gluTessCallback(obj, GLU_TESS_VERTEX, (void (CALLBACK *)())vertexCallback);
	gluTessCallback(obj, GLU_TESS_BEGIN, (void (CALLBACK *)())beginCallback);
	gluTessCallback(obj, GLU_TESS_END, (void (CALLBACK *)())endCallback);
	gluTessCallback(obj, GLU_TESS_ERROR, (void (CALLBACK *)())errorCallback);
}
void ZjwOpenGL::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(width) / height;
	
	//gluPerspective(60, width / height, 0.1, 200);
	////gluLookAt(0, 0, -50,0, 0, 0, 0, 1, 0);
	//glTranslatef(0, 0, -5);

	// 因为我已经把坐标实际的值归一化到-0.5-0.5，所以只需要
	//glOrtho是创建一个正交平行的视景体,范围只需要在-1到1之间就可以了
	GLfloat nRange = 1.0f;
	//下面这段代码，保证了，物体的尺寸不会随着窗体的变化而变化
	if (width <= height)
		glOrtho(-nRange, nRange, -nRange*height / width, nRange*height / width, -nRange, nRange);
	else
		glOrtho(-nRange*width / height, nRange*width / height, -nRange, nRange, -nRange, nRange);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);//设置光照的位置
}
//glDraw()调用下面这个虚函数
void ZjwOpenGL::paintGL()
{
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render();
}
void ZjwOpenGL::render()
{
	//局部坐标系下，响应鼠标事件等
	glPushMatrix();
	// Save matrix state and do the rotation
	glScalef(scale, scale, scale);   // here need scale

	/*glRotatef(rotationWorldX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationWorldY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationWorldZ, 0.0f, 1.0f, 0.0f);*/

	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationZ, 0.0f, 1.0f, 0.0f);
	
	//画内置的solid
	if (solidType == 0)
	{
		if (renderMode == 0)
		{
			drawXianKuang(solid);
		}
		else if (renderMode == 1)
		{
			draw(solid);
		}
		else
		{
			draw(solid);
		}
	}
	else if (solidType == 1)
	{
		//画文件读入的solid
		if (renderMode == 0)
		{
			drawXianKuang(fileSolid);
		}
		else if (renderMode == 1)
		{
			draw(fileSolid);
		}
		else
		{
			draw(fileSolid);
		}
	}
	glPopMatrix();
}

void ZjwOpenGL::keyPressEvent(QKeyEvent * event)
{
	float speed = 0.3;
	//std::cout << "key press event" << std::endl;
	switch (event->key()) {
	case Qt::Key_Up:
		glTranslated(0, speed, 0);  // 上移
		break;
	case Qt::Key_Down:
		glTranslated(0, -speed, 0);  // 上移
		break;
	case Qt::Key_Left:
		glTranslated(-speed, 0, 0);  // 上移
		break;
	case Qt::Key_Right:
		glTranslated(speed, 0, 0);  // 上移
		break;
	}
	updateGL();
}
void ZjwOpenGL::mousePressEvent(QMouseEvent * event)
{
	lastPoint = event->pos();
}
void ZjwOpenGL::mouseMoveEvent(QMouseEvent * event)
{
	GLfloat dx = GLfloat(event->x() - lastPoint.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPoint.y()) / height();

	if (event->buttons() & Qt::LeftButton) { //左键  
		rotationX += 180 * dy;
		rotationY += 180 * dx;
		updateGL(); //Updates the widget by calling glDraw().
	}
	else if (event->buttons() & Qt::RightButton) { //右键
		rotationX += 180 * dy;
		rotationZ += 180 * dx;
		updateGL();
	}
	lastPoint = event->pos();
}
void ZjwOpenGL::wheelEvent(QWheelEvent * event)
{
	double numDegrees = -event->delta() / 8.0;
	double numSteps = numDegrees / 15.0;
	scale *= pow(1.125, numSteps);
	updateGL();
}
void ZjwOpenGL::timerEvent(QTimerEvent *)
{
	rotationWorldY += playSpeed; //绕着Y轴转
	updateGL(); //Updates the widget by calling glDraw().
}

void ZjwOpenGL::draw(Solid * solid)
{
	if (!solid)
		return;
	Face *face = solid->solid2face;
	while (face)
	{
		gluTessBeginPolygon(obj, NULL);
		Loop *temploop = face->face2loop;
		while (temploop)
		{
			HalfEdge *halfedge = temploop->loop2halfedge;
			Vertex *start = halfedge->headVertex;
			glColor3b(verColor[start->id_vertex][0], verColor[start->id_vertex][1], verColor[start->id_vertex][2]);

			gluTessBeginContour(obj);
			gluTessVertex(obj, verNormalList[start->id_vertex], verNormalList[start->id_vertex]);

			//test
			//cout << verNormalList[start->id_vertex][0] << "  " << verNormalList[start->id_vertex][1] << "  " << verNormalList[start->id_vertex][2]<< endl;
			//end test
			Vertex *tmp = halfedge->next->headVertex;
			halfedge = halfedge->next;
			while (tmp != start)
			{
				glColor3b(verColor[tmp->id_vertex][0], verColor[tmp->id_vertex][1], verColor[tmp->id_vertex][2]);
				gluTessVertex(obj, verNormalList[tmp->id_vertex], verNormalList[tmp->id_vertex]);
				//test
				//cout << verNormalList[start->id_vertex][0] << "  " << verNormalList[start->id_vertex][1] << "  " << verNormalList[start->id_vertex][2] << endl;
				//end test
				halfedge = halfedge->next;
				tmp = halfedge->headVertex;
			}
			gluTessEndContour(obj);
			temploop = temploop->next;
		}
		gluTessEndPolygon(obj);
		face = face->next;
	}
}

void ZjwOpenGL::drawXianKuang(Solid * solid)
{
	//cout << "draw solid xian kuang !" << endl;
	glLineWidth(3);

	Face *face = solid->solid2face;
	while (face)
	{
		Loop *temploop = face->face2loop;
		while (temploop)
		{
			if (temploop->id_loop == 23)
				int i = 100;

			HalfEdge *halfedge = temploop->loop2halfedge;
			Vertex *start = halfedge->headVertex;
			Vertex * end = halfedge->tailVertex;
			glColor3b(verColor[start->id_vertex][0], verColor[start->id_vertex][1], verColor[start->id_vertex][2]);

			glBegin(GL_LINES);
			//gluTessVertex(obj, verNormalList[start->id_vertex], verNormalList[start->id_vertex]);
			glVertex3f(verNormalList[start->id_vertex][0], verNormalList[start->id_vertex][1], verNormalList[start->id_vertex][2]);
			glVertex3f(verNormalList[end->id_vertex][0], verNormalList[end->id_vertex][1], verNormalList[end->id_vertex][2]);
			glEnd();

			//test
			//cout << verNormalList[start->id_vertex][0] << "  " << verNormalList[start->id_vertex][1] << "  " << verNormalList[start->id_vertex][2] << endl;
			//end test
			Vertex *tmp = halfedge->next->headVertex;
			Vertex *tmp1 = halfedge->next->tailVertex;
			halfedge = halfedge->next;
			while (tmp != start)
			{
				glColor3b(verColor[tmp->id_vertex][0], verColor[tmp->id_vertex][1], verColor[tmp->id_vertex][2]);


				glBegin(GL_LINES);
				//gluTessVertex(obj, verNormalList[start->id_vertex], verNormalList[start->id_vertex]);
				glVertex3f(verNormalList[tmp->id_vertex][0], verNormalList[tmp->id_vertex][1], verNormalList[tmp->id_vertex][2]);
				glVertex3f(verNormalList[tmp1->id_vertex][0], verNormalList[tmp1->id_vertex][1], verNormalList[tmp1->id_vertex][2]);

				glEnd();

				halfedge = halfedge->next;
				tmp = halfedge->headVertex;
				tmp1 = halfedge->tailVertex;
			}
			temploop = temploop->next;
		}
		face = face->next;
	}
}

void ZjwOpenGL::initHalfEdge()
{
	static int i = 0;
	if (i == 0)
	{
		getColorForVertex(verColor);
		i++;
	}

	//对brep 需要用的数据，进行初始化
	if (solidModel == 1)
	{
		Point *sweepPoint = new Point(0, 0, 30);
		solid = getBaseFaceForSolid1();
		solid = getSolid(solid, sweepPoint);
	}
	else if (solidModel == 2)
	{
		Point *sweepPoint = new Point(0, 0, 30);
		solid = getBaseFaceForSolid2();
		solid = getSolid(solid, sweepPoint);
		
		//test
		//test(solid);
		//end test
	}
	else if (solidModel == 3)
	{
		Point *sweepPoint = new Point(0, 20, 30);
		solid = getBaseFaceForSolid3();
		solid = getSolid(solid, sweepPoint);

	}
	else  if (solidModel == 4)
	{
		Point *sweepPoint = new Point(0, 10, 30);
		solid = getBaseFaceForSolid4();
		solid = getSolid(solid, sweepPoint);

	}
	else {
		Point *sweepPoint = new Point(0, 0, 30);
		solid = getBaseFaceForSolid1();
		solid = getSolid(solid, sweepPoint);
	}

	saveAllVertexToDouble(solid, verList);
	getVerNormal();
}

void ZjwOpenGL::initFileLoadSolid()
{
	fileSolid = getBaseFaceByFile(zjwBrepFile);
	fileSolid = getSolid(fileSolid, &(zjwBrepFile->sweepPoint));

	//test
	//test(fileSolid);
	//end test
	saveAllVertexToDouble(fileSolid, verList);
	getVerNormal();
}

void ZjwOpenGL::getVerNormal()
{
	double maxNum = 0.0;

	for (int i = 0; i < 1000; i++)
	{
		maxNum = max(verList[i][0], maxNum);
		maxNum = max(verList[i][1], maxNum);
		maxNum = max(verList[i][2], maxNum);
	}

	for (int i = 0; i < 1000; i++)
	{
		verNormalList[i][0] = verList[i][0] / maxNum - 0.5;
		verNormalList[i][1] = verList[i][1] / maxNum - 0.5;
		verNormalList[i][2] = verList[i][2] / maxNum - 0.5;
	}

}
