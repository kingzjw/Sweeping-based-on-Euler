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
	//---------------------���Ժ���-----------------------------
	void test(Solid * solid);
	void test(Face * face);
	void test(Loop * loop);
	void printAllVer(Solid * solid);

	//------------------------ŷ����������-------------------------

	//mvfs: ������֪�ļ��ε㣬�����µ�vertex,loop ,face ,solid
	Solid* mvfs(Point * point);

	//mev: ����lp�е�oldPoint �� newPoint���ӳ�һ���µı�
	HalfEdge* mev(Point* oldPoint, Point * newPoint,  Loop * lp);

	//mef: ��lp�е������㣬����һ���µıߣ�Ҳ����һ���µ���,�µĻ�(�����ڻ�)
	Loop* mef(Point * oldPoint1, Point* oldPoint2, Loop * lp);

	//kemr����ȥ��lp�е�һ����(p1,p2)������һ�������ϵ��ڻ��������и�����
	Loop* kemr(Point * point1, Point* point2, Loop *lp);

	//kfmrh: ɾ��һ����(innerlp)�����䶨��Ϊ��һ�����е��ڻ����Ӷ�����һ����
	void kfmrh(Loop *outerlp, Loop *innerlp);

	//------------------------����-------------------------
	void saveAllVertexToDouble(Solid * solid, double ver[1000][3]);
	void getColorForVertex(unsigned char color[1000][3]);
	//ƽ��ɨ�ɺ���
	void translationSweep(Solid * solid, Face *face, Point * sweepPoint);
	// ����ƽ�Ƶķ���;��룬����ƽʱɨ�ɺ���
	Solid* getSolid(Solid * solid, Point *sweepPoint);
	
	//-----------------------��ͬ��solidģ�͵� base face ƽ��-------------------------

	//���ļ��ж����solid base face
	Solid* getBaseFaceByFile(ZjwBrepFile * file);
	//ֻ��һ�����ģ�Z��ƽ��
	Solid* getBaseFaceForSolid1();
	//��2�����ģ�Z��ƽ�� 
	Solid* getBaseFaceForSolid2();
	//��2�����ģ�Y,Z��ƽ��  
	Solid* getBaseFaceForSolid3();
	//��4�����ģ�Y,Z��ƽ��
	Solid* getBaseFaceForSolid4();

}
