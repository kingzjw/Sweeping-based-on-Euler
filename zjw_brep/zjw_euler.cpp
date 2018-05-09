/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/
#include "zjw_euler.h"
#include "zjw_halfedge.h"

#include<iostream>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<assert.h>

using namespace std;
using namespace zjw_euler;

void zjw_euler::test(Solid * solid)
{
	cout << "++++++++++++++solid++++++++++++++++++" << endl;
	Face *face = solid->solid2face;
	int index = 0;
	while (face)
	{//���λ��Ƹ���
		cout << "------------------------" << endl;
		cout << "face id: " << face->id_face << endl;

		Loop *temploop = face->face2loop;
		while (temploop)
		{   //������ǰ��ĸ���
			cout << "**********" << endl;
			cout << "loop id: " << temploop->id_loop << endl;

			HalfEdge *halfedge = temploop->loop2halfedge;

			//modify
			if (!halfedge)
			{
				return;
			}
			//end modify
			Vertex *start = halfedge->headVertex;
			Vertex *tmp = halfedge->next->headVertex;

			double pos[3];
			pos[0] = start->position.x;
			pos[1] = start->position.y;
			pos[2] = start->position.z;

			cout << "halfedge id: " << halfedge->id_halfedge << endl;
			cout << "vertex id: " << start->id_vertex << " pos: " << pos[0] << " " << pos[1] << " " << pos[2] << endl;

			halfedge = halfedge->next;
			while (tmp != start)
			{
				double pos1[3];
				pos1[0] = tmp->position.x;
				pos1[1] = tmp->position.y;
				pos1[2] = tmp->position.z;
				cout << "halfedge id: " << halfedge->id_halfedge << endl;
				cout << "vertex id: " << tmp->id_vertex << " pos: " << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl;
				halfedge = halfedge->next;
				tmp = halfedge->headVertex;
			}
			temploop = temploop->next;
		}
		face = face->next;
		index++;
	}
	cout << "++++++++++++++solid++++++++++++++++++" << endl;
}

void zjw_euler::test(Face * face)
{
	Loop * loop = face->face2loop;
	cout << "++++++++++++++face++++++++++++++++++" << endl;
	cout << "solid id: " << loop->loop2face->face2solid->id_solid << endl;
	cout << "face id: " << loop->loop2face->id_face << endl;
	while (loop)
	{   //������ǰ��ĸ���
		cout << "**********" << endl;
		cout << "loop id: " << loop->id_loop << endl;

		HalfEdge *halfedge = loop->loop2halfedge;
		//modify
		if (!halfedge)
		{
			cout << " halfedge is null, no vertex on it";
			return;
			cout << "++++++++++++++loop++++++++++++++++++" << endl;
		}
		//end modify
		Vertex *start = halfedge->headVertex;
		Vertex *tmp = halfedge->next->headVertex;

		double pos[3];
		pos[0] = start->position.x;
		pos[1] = start->position.y;
		pos[2] = start->position.z;

		cout << "halfedge id: " << halfedge->id_halfedge << endl;
		cout << "vertex id: " << start->id_vertex << " pos: " << pos[0] << " " << pos[1] << " " << pos[2] << endl;

		halfedge = halfedge->next;
		while (tmp != start)
		{
			double pos1[3];
			pos1[0] = tmp->position.x;
			pos1[1] = tmp->position.y;
			pos1[2] = tmp->position.z;
			cout << "halfedge id: " << halfedge->id_halfedge << endl;
			cout << "vertex id: " << tmp->id_vertex << " pos: " << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl;
			halfedge = halfedge->next;
			tmp = halfedge->headVertex;
		}
		loop = loop->next;
	}

	cout << "++++++++++++++face++++++++++++++++++" << endl;
}

void zjw_euler::test(Loop * loop)
{
	cout << "++++++++++++++loop++++++++++++++++++" << endl;
	cout << "solid id: " << loop->loop2face->face2solid->id_solid << endl;
	cout << "face id: " << loop->loop2face->id_face << endl;

	cout << "**********" << endl;
	cout << "loop id: " << loop->id_loop << endl;

	HalfEdge *halfedge = loop->loop2halfedge;
	//modify
	if (!halfedge)
	{
		cout << " halfedge is null, no vertex on it";
		return;
		cout << "++++++++++++++loop++++++++++++++++++" << endl;
	}
	//end modify
	Vertex *start = halfedge->headVertex;
	Vertex *tmp = halfedge->next->headVertex;

	double pos[3];
	pos[0] = start->position.x;
	pos[1] = start->position.y;
	pos[2] = start->position.z;

	cout << "halfedge id: " << halfedge->id_halfedge << endl;
	cout << "vertex id: " << start->id_vertex << " pos: " << pos[0] << " " << pos[1] << " " << pos[2] << endl;

	halfedge = halfedge->next;
	while (tmp != start)
	{
		double pos1[3];
		pos1[0] = tmp->position.x;
		pos1[1] = tmp->position.y;
		pos1[2] = tmp->position.z;
		cout << "halfedge id: " << halfedge->id_halfedge << endl;
		cout << "vertex id: " << tmp->id_vertex << " pos: " << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl;
		halfedge = halfedge->next;
		tmp = halfedge->headVertex;
	}

	cout << "++++++++++++++loop++++++++++++++++++" << endl;
}

void zjw_euler::printAllVer(Solid * solid)
{
	cout << "++++++++++++++���еĶ���++++++++++++++++++" << endl;
	Vertex *tempVer = solid->solid2vertex;
	for (; tempVer; tempVer = tempVer->next)
	{
		cout << tempVer->id_vertex << "   " << tempVer->position.x << "  " << tempVer->position.y << "  " << tempVer->position.z << endl;
	}
	cout << "++++++++++++++���еĶ���++++++++++++++++++" << endl;
}

Solid * zjw_euler::mvfs(Point * point)
{
	//���壬���棬�»����µ㡣
	Solid * solid = new Solid;
	Face *face = new Face;
	Loop *loop = new Loop;
	Vertex *ver = new Vertex;

	//�����µĶ���, ��ӵ�solid ��face��
	ver->position = *point;
	solid->addFace(face);
	face->addLoop(loop);
	solid->addVertex(ver);

	return solid;
}

HalfEdge * zjw_euler::mev(Point * oldPoint, Point * newPoint, Loop * lp)
{
	//�ο�����ʦ�Ͽν���α���룬���ֻ�ͼƬ

	Vertex* newVer = new Vertex;
	Edge * newEdge = new Edge;
	HalfEdge * he0 = new HalfEdge;
	HalfEdge * he1 = new HalfEdge;

	Vertex * oldVer = lp->loop2face->face2solid->getVertexByPoint(oldPoint);

	//�ų�loop��ֻ�ж��㣬û��halfedge
	if (!lp->verInLoop(oldVer) && lp->loop2halfedge != nullptr)
	{
		cout << "mev: input parm has error" << endl;
		//exit(-1);
		assert(0);
	}
	Vertex* checkVer = lp->loop2face->face2solid->findVer(oldPoint);
	if (!checkVer)
	{
		cout << "ver id: " << checkVer->id_vertex << endl;
		puts("Point1 can't be found in the Solid.");
		assert(0);
	}

	//set info
	newVer->position = *newPoint;
	newEdge->halfedge0 = he0;
	newEdge->halfedge1 = he1;

	//������߽ṹ����ӵ�ԭ�е�loop��ȥ��
	he0->he2Loop = lp;
	he0->he2Edge = newEdge;
	he0->headVertex = oldVer;
	he0->tailVertex = newVer;
	he0->oppositeHe = he1;

	he1->he2Loop = lp;
	he1->he2Edge = newEdge;
	he1->headVertex = newVer;
	he1->tailVertex = oldVer;
	he1->oppositeHe = he0;

	//�������he0 ��next �϶���he1 , he1��pre ����h0;
	he0->next = he1;
	he1->prev = he0;

	//solid�����Ϣ
	lp->loop2face->face2solid->addEdge(newEdge);
	lp->loop2face->face2solid->addVertex(newVer);

	HalfEdge *hePtr = lp->loop2halfedge;
	if (!hePtr)
	{
		//edge��loop�ĵ�һ����
		lp->loop2halfedge = he1;
		he0->prev = he1;
		he1->next = he0;
	}
	else
	{
		//edge����loop�ĵ�һ���ߣ������ǿ��Ƿֲ�

		//hePtrָ���±ߵ�ǰһ���ߵ�halfedge
		while (hePtr->next->headVertex != oldVer)
		{
			hePtr = hePtr->next;
		}

		//�޸�˫�������ָ��
		he1->next = hePtr->next;
		hePtr->next->prev = he1;
		hePtr->next = he0;
		he0->prev = hePtr;
	}
	return he0;
}

// oldPoint2 ��lp�е�λ�� ��oldPoint1��ǰ��
// oldPoint2��ͷ��Halfedge��Ϊ�⻷��oldPoint1��ͷ�ĵ�he ��Ϊ�ڻ���
//���ʱ��,newLoop���ڻ� ����new face�У�lp���⻷Ҳ��ԭ�е��档
Loop * zjw_euler::mef(Point * oldPoint1, Point * oldPoint2, Loop * lp)
{
	//�µıߣ��µİ�ߣ��µ��棬�µĻ�
	Edge * newEdge = new Edge;
	HalfEdge * he0 = new HalfEdge;
	HalfEdge * he1 = new HalfEdge;
	Face * newFace = new Face;
	//ԭ���Ļ�����loop�� ����⻷�����newLoop����ߵ��ڻ�
	Loop * newLoop = new Loop;

	Vertex * oldVer1 = lp->loop2face->face2solid->getVertexByPoint(oldPoint1);
	Vertex * oldVer2 = lp->loop2face->face2solid->getVertexByPoint(oldPoint2);

	//������������Ƿ���ͬһ��loop��,�����������
	if (lp->verInLoop(oldVer1) && lp->verInLoop(oldVer2))
	{
		lp->loop2face->face2solid->addEdge(newEdge);
		//���µ��ڻ� �ŵ�ԭ�е� face��ȥ
		lp->loop2face->face2solid->addFace(newFace);
		newFace->addLoop(newLoop);

		//edge info
		newEdge->halfedge0 = he0;
		newEdge->halfedge1 = he1;

		//-------------����he��loop--------------

		//he1 ��Ϊ����⻷�����  he2 ��Ϊ����ڻ������
		HalfEdge* heLp0 = lp->findHeByVer(oldVer1);
		HalfEdge* heLp1 = lp->findHeByVer(oldVer2);

		// -----------���������� newLoop--------------
		newLoop->addHe(he1);
		//������һ������ loop���� ���ĳ� newloop
		HalfEdge* tempHe = heLp0;
		while (tempHe)
		{
			if (tempHe == heLp1)
				break;
			tempHe->he2Loop = newLoop;
			tempHe = tempHe->next;
		}
		he1->next = heLp0;
		//tempHe�洢������Ҫ�õ��Ǹ�halfedge
		tempHe = heLp0->prev;
		heLp0->prev = he1;
		he1->prev = heLp1->prev;
		heLp1->prev->next = he1;

		//----���������� lp(old loop)------
		he0->prev = tempHe;
		tempHe->next = he0;
		he0->next = heLp1;
		heLp1->prev = he0;
		lp->loop2halfedge = he0;

		//----------info---------
		he0->he2Loop = lp;
		he0->he2Edge = newEdge;
		he0->oppositeHe = he1;
		he0->headVertex = oldVer1;
		he0->tailVertex = oldVer2;

		he1->he2Loop = newLoop;
		he1->he2Edge = newEdge;
		he1->oppositeHe = he0;
		he1->headVertex = oldVer2;
		he1->tailVertex = oldVer1;
	}
	else
	{
		cout << "mef: this two point are not in the same loop" << endl;
	}
	return newLoop;
}

//kemr����ȥ��lp�е�һ����(p1,p2)������һ�������ϵ��ڻ��������и�����
//lp�У�p1Ҫ��p2֮��
//���������֧��һ�������ȥһ���ߵ����
//�������ص��ǣ� ����ڻ���newloop��,lpָ����handle���⻷
Loop * zjw_euler::kemr(Point* oldPoint1, Point* oldPoint2, Loop * lp)
{
	//kemr ����������������ǿ��ǡ�

	Vertex * oldVer1 = lp->loop2face->face2solid->getVertexByPoint(oldPoint1);
	Vertex * oldVer2 = lp->loop2face->face2solid->getVertexByPoint(oldPoint2);

	//������������Ƿ���ͬһ��loop��,�����������
	if (lp->verInLoop(oldVer1) && lp->verInLoop(oldVer2))
	{
		//�õ���Ҫɾ��edge������halfedge
		HalfEdge * he0 = lp->loop2halfedge;
		HalfEdge * he1;
		Loop * newLoop = new Loop;
		lp->loop2face->addLoop(newLoop);

		while (he0)
		{
			if (he0->headVertex == oldVer1 && he0->tailVertex == oldVer2)
			{
				break;
			}
			he0 = he0->next;
		}
		he1 = he0->oppositeHe;

		//--------oldver1 ��oldver2 ��֪��˭��ǰ��---------
		if (he0->next != he1)
		{
			//he1 �ĺ�����he0

			//------------���ڹ���������ڻ�-------- -
			newLoop->addHe(he0->next);

			//�޸�he ��loop����
			HalfEdge *tempHe = he0->next->next;
			while (tempHe != he1)
			{
				tempHe->he2Loop = newLoop;
				tempHe = tempHe->next;
			}

			he0->next->prev = he1->prev;
			he1->prev->next = he0->next;
		}
		//---------lpָ��--����handle���������⻷------------------
		lp->loop2halfedge = he0->prev;
		he0->prev->next = he1->next;
		he1->next->prev = he0->prev;

		//-----------------------------ɾ��������---------------------------

		Edge * deleleEdge = he0->he2Edge;

		while (deleleEdge)
		{
			if (deleleEdge->halfedge0 == he1 || deleleEdge->halfedge1 == he1)
				break;
			deleleEdge = deleleEdge->next;
		}

		if (he1->he2Edge != deleleEdge)
		{
			cout << "the info save in halfedge is error!" << endl;
		}

		if (deleleEdge->next && deleleEdge->prev)
		{
			//�����м�
			deleleEdge->next->prev = deleleEdge->prev;
			deleleEdge->prev->next = deleleEdge->next;
		}
		else if (deleleEdge->next == nullptr &&deleleEdge->prev != nullptr)
		{
			//����ĩβ
			deleleEdge->prev->next = nullptr;
		}
		else if (deleleEdge->prev == nullptr&&deleleEdge->next != nullptr)
		{
			//���ڿ�ʼ
			deleleEdge->next->prev = nullptr;
			lp->loop2face->face2solid->solid2edge = deleleEdge->next;
		}
		else
		{
			//ֻ��һ���ߵ�ʱ��
			lp->loop2face->face2solid->solid2edge = nullptr;
		}

		//---ɾ��edge and halfedge-----
		delete deleleEdge;
		delete he0;
		delete he1;

		return newLoop;
	}
	else
	{
		cout << "kemr: this two point are not in the same loop" << endl;
		return nullptr;
	}
}

//kfmrh: ɾ��һ����(innerlp---�����ڻ�)�����䶨��Ϊ��һ�����е��ڻ����Ӷ�����һ����
//outerlp: base face ���⻷��innerlp---�����ڻ�
//�����ڵ��ڻ����� base face ���⻷��ͬһ���� ��solid��������棩
void zjw_euler::kfmrh(Loop * outerlp, Loop * innerlp)
{
	if (outerlp &&innerlp)
	{
		Face * deleteFace = innerlp->loop2face;
		outerlp->loop2face->addLoop(innerlp);

		//---------ɾ�����face ��������ɾ��   4�����---------
		/*
		���������ֻ��һ�����ڿ�ͷ���ڽ�β�����м�
		*/
		if (deleteFace->next&&deleteFace->prev)
		{
			deleteFace->next->prev = deleteFace->prev;
			deleteFace->prev->next = deleteFace->next;
		}
		else if (deleteFace->next == nullptr&&deleteFace->prev != nullptr)
		{
			deleteFace->prev->next = nullptr;
		}
		else if (deleteFace->prev == nullptr&&deleteFace->next != nullptr)
		{
			deleteFace->next->prev = nullptr;
			outerlp->loop2face->face2solid->solid2face = deleteFace->next;
		}
		else
		{
			outerlp->loop2face->face2solid->solid2face = nullptr;
		}
		delete deleteFace;
		return;
	}
	else {
		cout << "kfmrh: input param is error!" << endl;
		return;
	}
}

//input: �켣�߷���ͳ�����ԭ���sweepPoint���ɵ�
//�ο���ʦ�Ͽν���α����
void zjw_euler::translationSweep(Solid * solid, Face *face, Point * sweepPoint)
{
	//baseVer ��ʾ faceԭ���ĵ㣬upver ��baseVer ƽ��֮��Ķ��㣻
	//firstUpver: ��¼��һ��ƽ�ƺ�ĵ�
	Point *baseVer = new Point;
	Point *upVer = new Point;
	Point *firstUpVer = new Point;
	Point *preUpVer = new Point;

	Loop *tempLp;
	//-------------����ÿ��Loop-------------
	for (tempLp = face->face2loop; tempLp != nullptr; tempLp = tempLp->next)
	{
		HalfEdge *tempHe = tempLp->loop2halfedge;
		HalfEdge * finalHe = tempHe->prev;

		*baseVer = tempHe->headVertex->position;
		upVer->x = baseVer->x + sweepPoint->x;
		upVer->y = baseVer->y + sweepPoint->y;
		upVer->z = baseVer->z + sweepPoint->z;
		*firstUpVer = *upVer;
		*preUpVer = *upVer;
		mev(baseVer, upVer, tempLp);

		//������������Ļ�
		if (tempHe == finalHe)
		{
			//���һ��halfedge ,�������һ����
			tempHe = nullptr;
		}
		else
		{
			tempHe = tempHe->next;
		}

		while (tempHe)
		{
			*baseVer = tempHe->headVertex->position;
			upVer->x = baseVer->x + sweepPoint->x;
			upVer->y = baseVer->y + sweepPoint->y;
			upVer->z = baseVer->z + sweepPoint->z;

			mev(baseVer, upVer, tempLp);
			mef(preUpVer, upVer, tempLp);

			*preUpVer = *upVer;

			if (tempHe == finalHe)
			{
				//���һ��halfedge ,�������һ����
				tempHe = nullptr;
				mef(preUpVer, firstUpVer, tempLp);
			}
			else
			{
				tempHe = tempHe->next;
			}
		}
	}

	//free memory
	delete baseVer;
	delete upVer;
	delete preUpVer;
	delete firstUpVer;
	return;
}

void zjw_euler::saveAllVertexToDouble(Solid * solid, double ver[1000][3])
{
	Vertex *tempVer = solid->solid2vertex;
	for (; tempVer; tempVer = tempVer->next)
	{
		ver[tempVer->id_vertex][0] = tempVer->position.x;
		ver[tempVer->id_vertex][1] = tempVer->position.y;
		ver[tempVer->id_vertex][2] = tempVer->position.z;
	}
}

void zjw_euler::getColorForVertex(unsigned char color[1000][3])
{
	//���������ɫ�ĵ�
	for (int i = 0; i < 1000; i++)
	{
		color[i][0] = rand() % 255-1;
		color[i][1] = rand() % 255-1;
		color[i][2] = rand() % 255-1;
	}
}

Solid * zjw_euler::getSolid(Solid * solid, Point *sweepPoint)
{
	translationSweep(solid, solid->solid2face, sweepPoint);
	return solid;
}



//Solid * zjw_euler::getBaseFaceByFile(ZjwBrepFile * file)
//{
//	return nullptr;
//}

Solid * zjw_euler::getBaseFaceByFile(ZjwBrepFile * file)
{
	//cout << "face num: "<<file->ver2dimList.size() << endl;
	int faceNum = file->ver2dimList.size();
	
	//��һ��out solid face
	vector<Point> outSolid = file->ver2dimList[0];
	Solid* solid = mvfs(&outSolid[0]);
	Loop* lp = solid->solid2face->face2loop;
	Loop* outloop = lp;
	
	for (int face_it = 0; face_it < faceNum; face_it++)
	{

		//˵�������base face
		if (face_it == 0)
		{
			int verNum = file->ver2dimList[face_it].size();
			for (int v_it = 0; v_it < verNum-1; v_it++)
			{
				//test
				//cout << "out mev: " << v_it << " " << v_it + 1<<endl;
				//end test
				mev(&outSolid[v_it], &outSolid[v_it + 1], lp);
			}
			//cubeLoop����������⻷���ڻ��Ѿ�����������
			mef(&outSolid[verNum-1], &outSolid[0], lp);
			//test
			//cout << "out mev: " << verNum - 1 << " " << 0 << endl;
			//end test
		}
		else{
			vector<Point> inSolid = file->ver2dimList[face_it];

			//�õ�mef�����湹���õ�base face���ڻ�
			lp = solid->solid2face->next->face2loop;
			//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
			//test
			//cout << "mev: out " << 0 << " in " << 0 << endl;
			//end test
			mev(&outSolid[0], &inSolid[0], lp);
			lp = kemr(&outSolid[0], &inSolid[0], lp);


			int verNum = file->ver2dimList[face_it].size();
			for (int v_it = 0; v_it < verNum - 1; v_it++)
			{
				//cout << "in mev: " << v_it << " " << v_it + 1 << endl;
				mev(&inSolid[v_it], &inSolid[v_it + 1], lp);
			}
			//cubeLoop����������⻷���ڻ��Ѿ�����������
			Loop* inloop = mef(&inSolid[verNum - 1], &inSolid[0], lp);
			//outLoopָ����� baseFace ���⻷
			kfmrh(outloop, inloop);
		}
	}
	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid1()
{
	//���������
	vector<Point> outSolid;
	outSolid.push_back(Point(0.0, 0.0, 0.0));
	outSolid.push_back(Point(50.0, 20.0, 0.0));
	outSolid.push_back(Point(100.0, 0.0, 0.0));
	outSolid.push_back(Point(80.0, 50.0, 0.0));
	outSolid.push_back(Point(100.0, 100.0, 0.0));
	outSolid.push_back(Point(50.0, 80.0, 0.0));
	outSolid.push_back(Point(0.0, 100.0, 0.0));
	outSolid.push_back(Point(20.0, 50.0, 0.0));


	vector<Point> inSolid;
	inSolid.push_back(Point(40.0, 40.0, 0.0));
	inSolid.push_back(Point(60.0, 40.0, 0.0));
	inSolid.push_back(Point(60.0, 60.0, 0.0));
	inSolid.push_back(Point(40.0, 60.0, 0.0));

	Solid* solid = mvfs(&outSolid[0]);

	Loop* lp = solid->solid2face->face2loop;
	Loop* outloop = lp;

	//-----------------------out ------------------

	mev(&outSolid[0], &outSolid[1], lp);
	mev(&outSolid[1], &outSolid[2], lp);
	mev(&outSolid[2], &outSolid[3], lp);
	mev(&outSolid[3], &outSolid[4], lp);
	mev(&outSolid[4], &outSolid[5], lp);
	mev(&outSolid[5], &outSolid[6], lp);
	mev(&outSolid[6], &outSolid[7], lp);

	//cubeLoop����������⻷���ڻ��Ѿ�����������
	mef(&outSolid[7], &outSolid[0], lp);

	//-------------inner :��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &inSolid[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &inSolid[0], lp);
	//������һ����
	mev(&inSolid[0], &inSolid[1], lp);
	mev(&inSolid[1], &inSolid[2], lp);
	mev(&inSolid[2], &inSolid[3], lp);
	//inloopָ��0���ڻ�
	Loop* inloop = mef(&inSolid[3], &inSolid[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop);

	//-------------sweepPoint ������Զ�㹹�� ƽ��ɨ�ɵķ���;���-------------------

	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid2()
{
	//���������
	vector<Point> outSolid;
	outSolid.push_back(Point(0.0, 0.0, 0.0));
	outSolid.push_back(Point(50.0, 20.0, 0.0));
	outSolid.push_back(Point(100.0, 0.0, 0.0));
	outSolid.push_back(Point(80.0, 50.0, 0.0));
	outSolid.push_back(Point(100.0, 100.0, 0.0));
	outSolid.push_back(Point(50.0, 80.0, 0.0));
	outSolid.push_back(Point(0.0, 100.0, 0.0));
	outSolid.push_back(Point(20.0, 50.0, 0.0));

	vector<Point> insolid1;
	insolid1.push_back(Point(30.0, 30.0, 0.0));
	insolid1.push_back(Point(40.0, 30.0, 0.0));
	insolid1.push_back(Point(40.0, 70.0, 0.0));
	insolid1.push_back(Point(30.0, 70.0, 0.0));


	vector<Point> insolid2;
	insolid2.push_back(Point(60.0, 30.0, 0.0));
	insolid2.push_back(Point(70.0, 30.0, 0.0));
	insolid2.push_back(Point(70.0, 70.0, 0.0));
	insolid2.push_back(Point(60.0, 70.0, 0.0));


	Solid* solid = mvfs(&outSolid[0]);

	Loop* lp = solid->solid2face->face2loop;
	Loop* outloop = lp;

	//-----------------------out ------------------

	mev(&outSolid[0], &outSolid[1], lp);
	mev(&outSolid[1], &outSolid[2], lp);
	mev(&outSolid[2], &outSolid[3], lp);
	mev(&outSolid[3], &outSolid[4], lp);
	mev(&outSolid[4], &outSolid[5], lp);
	mev(&outSolid[5], &outSolid[6], lp);
	mev(&outSolid[6], &outSolid[7], lp);

	//cubeLoop����������⻷���ڻ��Ѿ�����������
	mef(&outSolid[7], &outSolid[0], lp);

	//-------------inner : ��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &insolid1[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &insolid1[0], lp);
	//������һ����
	mev(&insolid1[0], &insolid1[1], lp);
	mev(&insolid1[1], &insolid1[2], lp);
	mev(&insolid1[2], &insolid1[3], lp);

	//inloopָ��0���ڻ�
	Loop* inloop = mef(&insolid1[3], &insolid1[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop);


	//-------------inner :��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &insolid2[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &insolid2[0], lp);
	//������һ����
	mev(&insolid2[0], &insolid2[1], lp);
	mev(&insolid2[1], &insolid2[2], lp);
	mev(&insolid2[2], &insolid2[3], lp);

	//inloopָ��0���ڻ�
	Loop* inloop2 = mef(&insolid2[3], &insolid2[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop2);
	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid3()
{
	//���������
	vector<Point> outSolid;
	outSolid.push_back(Point(0.0, 30.0, 0.0));
	outSolid.push_back(Point(100.0, 30.0, 0.0));
	outSolid.push_back(Point(100.0, 70.0, 0.0));
	outSolid.push_back(Point(0.0, 70.0, 0.0));

	vector<Point> in5bx0;
	in5bx0.push_back(Point(10.0, 40.0, 0.0));
	in5bx0.push_back(Point(25.0, 40.0, 0.0));
	in5bx0.push_back(Point(40.0, 50.0, 0.0));
	in5bx0.push_back(Point(25.0, 60.0, 0.0));
	in5bx0.push_back(Point(10.0, 60.0, 0.0));

	vector<Point> in5bx1;
	in5bx1.push_back(Point(60.0, 50.0, 0.0));
	in5bx1.push_back(Point(75.0, 40.0, 0.0));
	in5bx1.push_back(Point(90.0, 40.0, 0.0));
	in5bx1.push_back(Point(90.0, 60.0, 0.0));
	in5bx1.push_back(Point(75.0, 60.0, 0.0));

	Solid* solid = mvfs(&outSolid[0]);
	Loop* lp = solid->solid2face->face2loop;
	Loop* outloop = lp;

	//-----------------------out ------------------

	mev(&outSolid[0], &outSolid[1], lp);
	mev(&outSolid[1], &outSolid[2], lp);
	mev(&outSolid[2], &outSolid[3], lp);
	//cubeLoop����������⻷���ڻ��Ѿ�����������
	mef(&outSolid[3], &outSolid[0], lp);

	//-------------inner : ��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &in5bx0[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &in5bx0[0], lp);
	//������һ����
	mev(&in5bx0[0], &in5bx0[1], lp);
	mev(&in5bx0[1], &in5bx0[2], lp);
	mev(&in5bx0[2], &in5bx0[3], lp);
	mev(&in5bx0[3], &in5bx0[4], lp);
	//inloopָ��0���ڻ�
	Loop* inloop = mef(&in5bx0[4], &in5bx0[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop);


	//------------inner 2---------------
	//�õ���base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &in5bx1[0], lp);
	//cubeLoopָ���µĿջ�---Ϊ�˴����ڶ�����
	lp = kemr(&outSolid[0], &in5bx1[0], lp);

	mev(&in5bx1[0], &in5bx1[1], lp);
	mev(&in5bx1[1], &in5bx1[2], lp);
	mev(&in5bx1[2], &in5bx1[3], lp);
	mev(&in5bx1[3], &in5bx1[4], lp);
	Loop* inloop2 = mef(&in5bx1[4], &in5bx1[0], lp);
	kfmrh(outloop, inloop2);
	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid4()
{
	//���������
	vector<Point> outSolid;
	outSolid.push_back(Point(0.0, 0.0, 0.0));
	outSolid.push_back(Point(50.0, 20.0, 0.0));
	outSolid.push_back(Point(100.0, 0.0, 0.0));
	outSolid.push_back(Point(80.0, 50.0, 0.0));
	outSolid.push_back(Point(100.0, 100.0, 0.0));
	outSolid.push_back(Point(50.0, 80.0, 0.0));
	outSolid.push_back(Point(0.0, 100.0, 0.0));
	outSolid.push_back(Point(20.0, 50.0, 0.0));

	vector<Point> insolid0;
	insolid0.push_back(Point(30, 30, 0.0));
	insolid0.push_back(Point(45, 30, 0.0));
	insolid0.push_back(Point(45, 45, 0.0));
	insolid0.push_back(Point(30, 45, 0.0));

	vector<Point> insolid1;
	insolid1.push_back(Point(55, 30.0, 0.0));
	insolid1.push_back(Point(70, 30.0, 0.0));
	insolid1.push_back(Point(70, 45, 0.0));
	insolid1.push_back(Point(55, 45, 0.0));

	vector<Point> insolid2;
	insolid2.push_back(Point(30, 55, 0.0));
	insolid2.push_back(Point(45, 55, 0.0));
	insolid2.push_back(Point(45, 70, 0.0));
	insolid2.push_back(Point(30, 70, 0.0));

	vector<Point> insolid3;
	insolid3.push_back(Point(55, 55, 0.0));
	insolid3.push_back(Point(70, 55, 0.0));
	insolid3.push_back(Point(70, 70, 0.0));
	insolid3.push_back(Point(55, 70, 0.0));

	Solid* solid = mvfs(&outSolid[0]);

	Loop* lp = solid->solid2face->face2loop;
	Loop* outloop = lp;

	//-----------------------out ------------------

	mev(&outSolid[0], &outSolid[1], lp);
	mev(&outSolid[1], &outSolid[2], lp);
	mev(&outSolid[2], &outSolid[3], lp);
	mev(&outSolid[3], &outSolid[4], lp);
	mev(&outSolid[4], &outSolid[5], lp);
	mev(&outSolid[5], &outSolid[6], lp);
	mev(&outSolid[6], &outSolid[7], lp);

	//cubeLoop����������⻷���ڻ��Ѿ�����������
	mef(&outSolid[7], &outSolid[0], lp);

	//-------------inner : ��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &insolid0[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &insolid0[0], lp);
	//������һ����
	mev(&insolid0[0], &insolid0[1], lp);
	mev(&insolid0[1], &insolid0[2], lp);
	mev(&insolid0[2], &insolid0[3], lp);
	//inloopָ��0���ڻ�
	Loop* inloop = mef(&insolid0[3], &insolid0[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop);


	//-------------inner :��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &insolid1[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &insolid1[0], lp);
	//������һ����
	mev(&insolid1[0], &insolid1[1], lp);
	mev(&insolid1[1], &insolid1[2], lp);
	mev(&insolid1[2], &insolid1[3], lp);
	Loop * inloop2 = mef(&insolid1[3], &insolid1[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop2);

	//-------------inner :��Ҫ������������ε��ڻ����в���-------------

	//�õ�mef�����湹���õ�base face���ڻ�
	lp = solid->solid2face->next->face2loop;
	//����һ���µĿջ������Ѷ��еĵ�һ������ �ŵ� solid�С�
	mev(&outSolid[0], &insolid2[0], lp);
	//cubeLoopָ���µĿջ�
	lp = kemr(&outSolid[0], &insolid2[0], lp);
	//������һ����
	mev(&insolid2[0], &insolid2[1], lp);
	mev(&insolid2[1], &insolid2[2], lp);
	mev(&insolid2[2], &insolid2[3], lp);
	Loop * inloop3 = mef(&insolid2[3], &insolid2[0], lp);
	//outLoopָ����� baseFace ���⻷
	kfmrh(outloop, inloop3);

	//-------------inner :��Ҫ������������ε��ڻ����в���-------------

	lp = solid->solid2face->next->face2loop;
	mev(&outSolid[0], &insolid3[0], lp);
	lp = kemr(&outSolid[0], &insolid3[0], lp);
	mev(&insolid3[0], &insolid3[1], lp);
	mev(&insolid3[1], &insolid3[2], lp);
	mev(&insolid3[2], &insolid3[3], lp);
	Loop * inloop4 = mef(&insolid3[3], &insolid3[0], lp);
	kfmrh(outloop, inloop4);
	return solid;
}

//Solid * zjw_euler::getBaseFaceByFile(ZjwBrepFile * file)
//{
//
//	return solid;
//}
