/*
author: Zhou Jiawei 
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
		   please send a email to zjwking258@163.com to get the right!
*/
#pragma once
namespace zjw_halfedge
{
	class Face;
	class Loop;
	class HalfEdge;
	class Vertex;
	class Edge;

	class Point
	{
	public:
		double x;
		double y;
		double z;

	public:
		Point();
		Point(double x,double y, double z);
		Point& operator= (const Point & p);

	};

	class Solid
	{
	public:
		int id_solid;
		Solid *next;
		Solid *prev;
		//solid中存放的面，边，点的索引
		Face *solid2face;
		Edge *solid2edge;
		Vertex *solid2vertex;

	public:
		Solid();
		//add face to solid and init the face param
		bool addFace(Face *face);
		bool addEdge(Edge *edge);
		bool addVertex(Vertex *vertex);

		//通过point值获得已有的vertex
		Vertex* getVertexByPoint(Point *point);
		Vertex* findVer(Point * point);
	};

	class Face
	{
	public:
		int id_face;
		Face *next;
		Face *prev;
		Solid *face2solid;
		Loop *face2loop;
	public:
		Face();

		//在face中添加loop
		bool addLoop(Loop *pLoop);
	};

	class Loop
	{
	public:
		int id_loop;
		Loop *next;
		Loop *prev;
		Face *loop2face;
		HalfEdge *loop2halfedge;
	public:
		Loop();

		//在loop中的末尾添加新的halfedge
		bool addHe(HalfEdge *he);
		//判断这个顶点是否在这个loop中
		bool verInLoop(Vertex *vertex);
		//找到以这点出发的halfedge。
		HalfEdge *findHeByVer(Vertex *vertex);
	};

	class HalfEdge
	{
	public:
		int id_halfedge;
		HalfEdge *next;
		HalfEdge *prev;
		//这条halfedge对应edge的半边
		HalfEdge *oppositeHe;
		//halfedge所在的环
		Loop *he2Loop;
		//halfedge 所在的边
		Edge *he2Edge;
		//halfedge的出发点
		Vertex *headVertex;
		//halfedge的终点
		Vertex *tailVertex;

	public:
		HalfEdge();
	};

	class Vertex
	{
	public:
		int id_vertex;
		Vertex *next;
		Vertex *prev;
		Point  position;

	public:
		Vertex();
		bool setVertexPos(Point pos);
	};

	class Edge
	{
	public:
		int id_edge;
		Edge *next;
		Edge *prev;
		//这条边所对应的两条haledge
		HalfEdge *halfedge0;
		HalfEdge *halfedge1;

	public:
		Edge();
	};
}
