/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/
#pragma once

#include "zjw_halfedge.h"
#include "zjw_file.h"
#include <vector>
using namespace zjw_halfedge;

namespace zjw_euler
{
	//---------------------测试函数-----------------------------
	void test(Solid * solid);
	void test(Face * face);
	void test(Loop * loop);
	void printAllVer(Solid * solid);

	//------------------------欧拉基本操作-------------------------

	//mvfs: 根据已知的几何点，构造新的vertex,loop ,face ,solid
	Solid* mvfs(Point * point);

	//mev: 连接lp中的oldPoint 和 newPoint连接成一条新的边
	HalfEdge* mev(Point* oldPoint, Point * newPoint,  Loop * lp);

	//mef: 给lp中的两个点，构成一条新的边，也构成一个新的面,新的环(构造内环)
	Loop* mef(Point * oldPoint1, Point* oldPoint2, Loop * lp);

	//kemr：消去环lp中的一条边(p1,p2)，构造一条物理上的内环（面内有个洞）
	Loop* kemr(Point * point1, Point* point2, Loop *lp);

	//kfmrh: 删除一个面(innerlp)，将其定义为另一个面中的内环，从而构成一个柄
	void kfmrh(Loop *outerlp, Loop *innerlp);

	//------------------------操作-------------------------
	void saveAllVertexToDouble(Solid * solid, double ver[1000][3]);
	void getColorForVertex(unsigned char color[1000][3]);
	//平移扫成函数
	void translationSweep(Solid * solid, Face *face, Point * sweepPoint);
	// 设置平移的方向和距离，调用平时扫成函数
	Solid* getSolid(Solid * solid, Point *sweepPoint);
	
	//-----------------------不同的solid模型的 base face 平面-------------------------

	//从文件中读入的solid base face
	Solid* getBaseFaceByFile(ZjwBrepFile * file);
	//只有一个洞的，Z轴平移
	Solid* getBaseFaceForSolid1();
	//有2个洞的，Z轴平移 
	Solid* getBaseFaceForSolid2();
	//有2个洞的，Y,Z轴平移  
	Solid* getBaseFaceForSolid3();
	//有4个洞的，Y,Z轴平移
	Solid* getBaseFaceForSolid4();

}
