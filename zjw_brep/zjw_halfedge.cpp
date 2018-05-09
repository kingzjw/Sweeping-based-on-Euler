/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/

#include "zjw_halfedge.h"
#include<iostream>
using namespace zjw_halfedge;

zjw_halfedge::Point::Point()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

zjw_halfedge::Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point& zjw_halfedge::Point::operator=(const Point&  p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	return *this;
}

//--------------------------------solid------------------------------------------

zjw_halfedge::Solid::Solid()
{
	static int id = 0;
	id_solid = id++;
	next = prev = nullptr;
	solid2face = nullptr;
	solid2edge = nullptr;
	solid2vertex = nullptr;
}

bool zjw_halfedge::Solid::addFace(Face *face)
{
	if (!face)
	{
		return false;
	}
	Face *f = solid2face;
	//第一次添加face
	if (!f)
	{
		solid2face = face;
	}
	else
	{
		//在原有的基础上，添加face
		while (f->next)
		{
			f = f->next;
		}
		f->next = face;
		face->prev = f;
	}
	face->face2solid = this;
	return true;
}

bool zjw_halfedge::Solid::addEdge(Edge * edge)
{
	if (!edge)
	{
		return false;
	}
	Edge *e = solid2edge;

	if (!e)
	{
		//第一次添加边
		solid2edge = edge;
	}
	else
	{
		//在原有的基础上，添加edge
		while (e->next)
		{
			e = e->next;
		}
		e->next = edge;
		edge->prev = e;
	}
	return true;
}

bool zjw_halfedge::Solid::addVertex(Vertex *vertex)
{
	if (!vertex)
	{
		return false;
	}
	Vertex *ver = solid2vertex;
	//第一次 add ver
	if (!ver)
	{
		solid2vertex = vertex;
	}
	else
	{
		//在原有的基础上，添加vertex
		while (ver->next)
		{
			ver = ver->next;
		}
		ver->next = vertex;
		vertex->prev = ver;
	}
	return true;
}

Vertex * zjw_halfedge::Solid::getVertexByPoint(Point *point)
{
	Vertex *tempVer = solid2vertex;
	for (; tempVer; tempVer = tempVer->next)
	{
		if (tempVer->position.x == point->x &&
			tempVer->position.y == point->y &&
			tempVer->position.z == point->z)
		{
			return tempVer;
		}
	}
	std::cout << "point not find in solid vertex!" << std::endl;
	std::cout << "point:" << point->x << " " << point->y << " " << point->z << " " << std::endl;
	return nullptr;
}

Vertex * zjw_halfedge::Solid::findVer(Point * point)
{
	Vertex *tempVer = solid2vertex;
	for (; tempVer; tempVer = tempVer->next)
	{
		if (tempVer->position.x == point->x && tempVer->position.y == point->y && tempVer->position.z == point->z)
		{
			return tempVer;
		}
	}
	return nullptr;
}

//--------------------------------face------------------------------------------

zjw_halfedge::Face::Face()
{
	static int id = 0;
	id_face = id++;
	next = nullptr;
	prev = nullptr;
	face2solid = nullptr;
	face2loop = nullptr;
}

bool zjw_halfedge::Face::addLoop(Loop *loop)
{
	if (!loop)
	{
		return false;
	}

	Loop*	lp = face2loop;

	//第一次添加环
	if (!lp)
		face2loop = loop;
	else
	{
		//在原有的基础上，添加loop
		while (lp->next)
		{
			lp = lp->next;
		}
		lp->next = loop;
		loop->prev = lp;
	}
	loop->loop2face = this;

	return true;
}

//--------------------------------loop------------------------------------------

zjw_halfedge::Loop::Loop()
{
	static int id = 0;
	id_loop = id++;
	next = nullptr;
	prev = nullptr;
	loop2face = nullptr;
	loop2halfedge = nullptr;
}

bool zjw_halfedge::Loop::addHe(HalfEdge *he)
{
	if (!he)
		return false;
	HalfEdge *tempHe = loop2halfedge;
	if (!tempHe)
	{
		loop2halfedge = he;
	}
	else
	{
		while (tempHe->next)
			tempHe = tempHe->next;
		tempHe->next = he;
		he->prev = tempHe;
	}
	he->he2Loop = this;
	return true;
}
bool zjw_halfedge::Loop::verInLoop(Vertex *vertex)
{
	if (!vertex)
		return false;
	HalfEdge *phe = loop2halfedge;
	while (phe)
	{
		if (phe->headVertex == vertex)
			return true;
		phe = phe->next;
		if (phe == loop2halfedge)
			return false;
	}
	return false;
}
zjw_halfedge::HalfEdge * zjw_halfedge::Loop::findHeByVer(Vertex *vertex)
{
	if (!vertex)
		return nullptr;
	HalfEdge *tempHalfedge = loop2halfedge;
	while (tempHalfedge)
	{
		if (tempHalfedge->headVertex == vertex)
			return tempHalfedge;
		tempHalfedge = tempHalfedge->next;
		if (tempHalfedge == loop2halfedge)
			return nullptr;
	}
	return nullptr;
}

//--------------------------------halfedge------------------------------------------

zjw_halfedge::HalfEdge::HalfEdge()
{
	static int id = 0;
	id_halfedge = id++;
	next = nullptr;
	prev = nullptr;
	oppositeHe = nullptr;
	he2Loop = nullptr;
	he2Edge = nullptr;
	headVertex = nullptr;
	tailVertex = nullptr;
}

//--------------------------------vertex------------------------------------------

zjw_halfedge::Vertex::Vertex()
{
	position.x = position.y = position.z = 0;
	next = prev = nullptr;
	static int id = 0;
	id_vertex = id++;
}

bool zjw_halfedge::Vertex::setVertexPos(Point pos)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	return true;
}

//--------------------------------edge------------------------------------------

zjw_halfedge::Edge::Edge()
{
	static int id = 0;
	id_edge = id++;
	next = nullptr;
	prev = nullptr;
	halfedge0 = nullptr;
	halfedge1 = nullptr;
}