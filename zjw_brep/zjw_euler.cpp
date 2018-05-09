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
	{//依次绘制各面
		cout << "------------------------" << endl;
		cout << "face id: " << face->id_face << endl;

		Loop *temploop = face->face2loop;
		while (temploop)
		{   //遍历当前面的各点
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
	{   //遍历当前面的各点
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
	cout << "++++++++++++++所有的顶点++++++++++++++++++" << endl;
	Vertex *tempVer = solid->solid2vertex;
	for (; tempVer; tempVer = tempVer->next)
	{
		cout << tempVer->id_vertex << "   " << tempVer->position.x << "  " << tempVer->position.y << "  " << tempVer->position.z << endl;
	}
	cout << "++++++++++++++所有的顶点++++++++++++++++++" << endl;
}

Solid * zjw_euler::mvfs(Point * point)
{
	//新体，新面，新环，新点。
	Solid * solid = new Solid;
	Face *face = new Face;
	Loop *loop = new Loop;
	Vertex *ver = new Vertex;

	//设置新的顶点, 添加到solid 和face中
	ver->position = *point;
	solid->addFace(face);
	face->addLoop(loop);
	solid->addVertex(ver);

	return solid;
}

HalfEdge * zjw_euler::mev(Point * oldPoint, Point * newPoint, Loop * lp)
{
	//参考高老师上课讲的伪代码，见手机图片

	Vertex* newVer = new Vertex;
	Edge * newEdge = new Edge;
	HalfEdge * he0 = new HalfEdge;
	HalfEdge * he1 = new HalfEdge;

	Vertex * oldVer = lp->loop2face->face2solid->getVertexByPoint(oldPoint);

	//排除loop中只有顶点，没有halfedge
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

	//建立半边结构，添加到原有的loop上去。
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

	//无乱如何he0 的next 肯定是he1 , he1的pre 就是h0;
	he0->next = he1;
	he1->prev = he0;

	//solid添加信息
	lp->loop2face->face2solid->addEdge(newEdge);
	lp->loop2face->face2solid->addVertex(newVer);

	HalfEdge *hePtr = lp->loop2halfedge;
	if (!hePtr)
	{
		//edge是loop的第一条边
		lp->loop2halfedge = he1;
		he0->prev = he1;
		he1->next = he0;
	}
	else
	{
		//edge不是loop的第一条边，别忘记考虑分叉

		//hePtr指向新边的前一条边的halfedge
		while (hePtr->next->headVertex != oldVer)
		{
			hePtr = hePtr->next;
		}

		//修改双向链表的指针
		he1->next = hePtr->next;
		hePtr->next->prev = he1;
		hePtr->next = he0;
		he0->prev = hePtr;
	}
	return he0;
}

// oldPoint2 在lp中的位置 比oldPoint1靠前。
// oldPoint2开头的Halfedge作为外环，oldPoint1开头的的he 作为内环）
//这个时候,newLoop是内环 放在new face中，lp是外环也在原有的面。
Loop * zjw_euler::mef(Point * oldPoint1, Point * oldPoint2, Loop * lp)
{
	//新的边，新的半边，新的面，新的环
	Edge * newEdge = new Edge;
	HalfEdge * he0 = new HalfEdge;
	HalfEdge * he1 = new HalfEdge;
	Face * newFace = new Face;
	//原来的环，当loop的 半边外环，这个newLoop当半边的内环
	Loop * newLoop = new Loop;

	Vertex * oldVer1 = lp->loop2face->face2solid->getVertexByPoint(oldPoint1);
	Vertex * oldVer2 = lp->loop2face->face2solid->getVertexByPoint(oldPoint2);

	//检查这两个点是否在同一个loop中,避免输入错误
	if (lp->verInLoop(oldVer1) && lp->verInLoop(oldVer2))
	{
		lp->loop2face->face2solid->addEdge(newEdge);
		//把新的内环 放到原有的 face上去
		lp->loop2face->face2solid->addFace(newFace);
		newFace->addLoop(newLoop);

		//edge info
		newEdge->halfedge0 = he0;
		newEdge->halfedge1 = he1;

		//-------------处理he和loop--------------

		//he1 作为半边外环的起点  he2 作为半边内环的起点
		HalfEdge* heLp0 = lp->findHeByVer(oldVer1);
		HalfEdge* heLp1 = lp->findHeByVer(oldVer2);

		// -----------创建完整的 newLoop--------------
		newLoop->addHe(he1);
		//把其中一个环的 loop属性 都改成 newloop
		HalfEdge* tempHe = heLp0;
		while (tempHe)
		{
			if (tempHe == heLp1)
				break;
			tempHe->he2Loop = newLoop;
			tempHe = tempHe->next;
		}
		he1->next = heLp0;
		//tempHe存储后面需要用的那个halfedge
		tempHe = heLp0->prev;
		heLp0->prev = he1;
		he1->prev = heLp1->prev;
		heLp1->prev->next = he1;

		//----创建完整的 lp(old loop)------
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

//kemr：消去环lp中的一条边(p1,p2)，构造一条物理上的内环（面内有个洞）
//lp中，p1要在p2之后
//这个函数不支持一个多边形去一条边的情况
//函数返回的是： 面的内环（newloop）,lp指向了handle的外环
Loop * zjw_euler::kemr(Point* oldPoint1, Point* oldPoint2, Loop * lp)
{
	//kemr 有两种情况，别忘记考虑。

	Vertex * oldVer1 = lp->loop2face->face2solid->getVertexByPoint(oldPoint1);
	Vertex * oldVer2 = lp->loop2face->face2solid->getVertexByPoint(oldPoint2);

	//检查这两个点是否在同一个loop中,避免输入错误
	if (lp->verInLoop(oldVer1) && lp->verInLoop(oldVer2))
	{
		//拿到需要删除edge的两个halfedge
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

		//--------oldver1 和oldver2 不知道谁在前面---------
		if (he0->next != he1)
		{
			//he1 的后面是he0

			//------------现在构造面的新内环-------- -
			newLoop->addHe(he0->next);

			//修改he 的loop属性
			HalfEdge *tempHe = he0->next->next;
			while (tempHe != he1)
			{
				tempHe->he2Loop = newLoop;
				tempHe = tempHe->next;
			}

			he0->next->prev = he1->prev;
			he1->prev->next = he0->next;
		}
		//---------lp指向--构造handle（洞）的外环------------------
		lp->loop2halfedge = he0->prev;
		he0->prev->next = he1->next;
		he1->next->prev = he0->prev;

		//-----------------------------删除那条边---------------------------

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
			//边在中间
			deleleEdge->next->prev = deleleEdge->prev;
			deleleEdge->prev->next = deleleEdge->next;
		}
		else if (deleleEdge->next == nullptr &&deleleEdge->prev != nullptr)
		{
			//边在末尾
			deleleEdge->prev->next = nullptr;
		}
		else if (deleleEdge->prev == nullptr&&deleleEdge->next != nullptr)
		{
			//边在开始
			deleleEdge->next->prev = nullptr;
			lp->loop2face->face2solid->solid2edge = deleleEdge->next;
		}
		else
		{
			//只有一条边的时候
			lp->loop2face->face2solid->solid2edge = nullptr;
		}

		//---删除edge and halfedge-----
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

//kfmrh: 删除一个面(innerlp---柄的内环)，将其定义为另一个面中的内环，从而构成一个柄
//outerlp: base face 的外环，innerlp---柄的内环
//柄所在的内环，和 base face 的外环是同一个面 （solid中最早的面）
void zjw_euler::kfmrh(Loop * outerlp, Loop * innerlp)
{
	if (outerlp &&innerlp)
	{
		Face * deleteFace = innerlp->loop2face;
		outerlp->loop2face->addLoop(innerlp);

		//---------删除这个face 从链表中删除   4中情况---------
		/*
		四种情况：只有一个，在开头，在结尾，在中间
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

//input: 轨迹线方向和长度是原点和sweepPoint构成的
//参考老师上课讲的伪代码
void zjw_euler::translationSweep(Solid * solid, Face *face, Point * sweepPoint)
{
	//baseVer 表示 face原来的点，upver 是baseVer 平移之后的顶点；
	//firstUpver: 记录第一个平移后的点
	Point *baseVer = new Point;
	Point *upVer = new Point;
	Point *firstUpVer = new Point;
	Point *preUpVer = new Point;

	Loop *tempLp;
	//-------------遍历每个Loop-------------
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

		//处理特殊情况的环
		if (tempHe == finalHe)
		{
			//最后一条halfedge ,处理最后一个面
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
				//最后一条halfedge ,处理最后一个面
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
	//不会产生白色的点
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
	
	//第一个out solid face
	vector<Point> outSolid = file->ver2dimList[0];
	Solid* solid = mvfs(&outSolid[0]);
	Loop* lp = solid->solid2face->face2loop;
	Loop* outloop = lp;
	
	for (int face_it = 0; face_it < faceNum; face_it++)
	{

		//说明这个是base face
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
			//cubeLoop面成这个面的外环，内环已经放在新面内
			mef(&outSolid[verNum-1], &outSolid[0], lp);
			//test
			//cout << "out mev: " << verNum - 1 << " " << 0 << endl;
			//end test
		}
		else{
			vector<Point> inSolid = file->ver2dimList[face_it];

			//拿到mef中上面构建好的base face的内环
			lp = solid->solid2face->next->face2loop;
			//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
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
			//cubeLoop面成这个面的外环，内环已经放在新面内
			Loop* inloop = mef(&inSolid[verNum - 1], &inSolid[0], lp);
			//outLoop指向的是 baseFace 的外环
			kfmrh(outloop, inloop);
		}
	}
	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid1()
{
	//输入的数据
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

	//cubeLoop面成这个面的外环，内环已经放在新面内
	mef(&outSolid[7], &outSolid[0], lp);

	//-------------inner :需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &inSolid[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &inSolid[0], lp);
	//构建第一个洞
	mev(&inSolid[0], &inSolid[1], lp);
	mev(&inSolid[1], &inSolid[2], lp);
	mev(&inSolid[2], &inSolid[3], lp);
	//inloop指向洞0的内环
	Loop* inloop = mef(&inSolid[3], &inSolid[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop);

	//-------------sweepPoint 和坐标远点构成 平移扫成的方向和距离-------------------

	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid2()
{
	//输入的数据
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

	//cubeLoop面成这个面的外环，内环已经放在新面内
	mef(&outSolid[7], &outSolid[0], lp);

	//-------------inner : 需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &insolid1[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &insolid1[0], lp);
	//构建第一个洞
	mev(&insolid1[0], &insolid1[1], lp);
	mev(&insolid1[1], &insolid1[2], lp);
	mev(&insolid1[2], &insolid1[3], lp);

	//inloop指向洞0的内环
	Loop* inloop = mef(&insolid1[3], &insolid1[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop);


	//-------------inner :需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &insolid2[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &insolid2[0], lp);
	//构建第一个洞
	mev(&insolid2[0], &insolid2[1], lp);
	mev(&insolid2[1], &insolid2[2], lp);
	mev(&insolid2[2], &insolid2[3], lp);

	//inloop指向洞0的内环
	Loop* inloop2 = mef(&insolid2[3], &insolid2[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop2);
	return solid;
}

Solid * zjw_euler::getBaseFaceForSolid3()
{
	//输入的数据
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
	//cubeLoop面成这个面的外环，内环已经放在新面内
	mef(&outSolid[3], &outSolid[0], lp);

	//-------------inner : 需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &in5bx0[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &in5bx0[0], lp);
	//构建第一个洞
	mev(&in5bx0[0], &in5bx0[1], lp);
	mev(&in5bx0[1], &in5bx0[2], lp);
	mev(&in5bx0[2], &in5bx0[3], lp);
	mev(&in5bx0[3], &in5bx0[4], lp);
	//inloop指向洞0的内环
	Loop* inloop = mef(&in5bx0[4], &in5bx0[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop);


	//------------inner 2---------------
	//拿到的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &in5bx1[0], lp);
	//cubeLoop指向新的空环---为了创建第二个柄
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
	//输入的数据
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

	//cubeLoop面成这个面的外环，内环已经放在新面内
	mef(&outSolid[7], &outSolid[0], lp);

	//-------------inner : 需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &insolid0[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &insolid0[0], lp);
	//构建第一个洞
	mev(&insolid0[0], &insolid0[1], lp);
	mev(&insolid0[1], &insolid0[2], lp);
	mev(&insolid0[2], &insolid0[3], lp);
	//inloop指向洞0的内环
	Loop* inloop = mef(&insolid0[3], &insolid0[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop);


	//-------------inner :需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &insolid1[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &insolid1[0], lp);
	//构建第一个洞
	mev(&insolid1[0], &insolid1[1], lp);
	mev(&insolid1[1], &insolid1[2], lp);
	mev(&insolid1[2], &insolid1[3], lp);
	Loop * inloop2 = mef(&insolid1[3], &insolid1[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop2);

	//-------------inner :需要对上面这个矩形的内环进行操作-------------

	//拿到mef中上面构建好的base face的内环
	lp = solid->solid2face->next->face2loop;
	//构建一个新的空环，并把洞中的第一个顶点 放到 solid中。
	mev(&outSolid[0], &insolid2[0], lp);
	//cubeLoop指向新的空环
	lp = kemr(&outSolid[0], &insolid2[0], lp);
	//构建第一个洞
	mev(&insolid2[0], &insolid2[1], lp);
	mev(&insolid2[1], &insolid2[2], lp);
	mev(&insolid2[2], &insolid2[3], lp);
	Loop * inloop3 = mef(&insolid2[3], &insolid2[0], lp);
	//outLoop指向的是 baseFace 的外环
	kfmrh(outloop, inloop3);

	//-------------inner :需要对上面这个矩形的内环进行操作-------------

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
