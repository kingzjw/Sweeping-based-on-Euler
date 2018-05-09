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
		//solid�д�ŵ��棬�ߣ��������
		Face *solid2face;
		Edge *solid2edge;
		Vertex *solid2vertex;

	public:
		Solid();
		//add face to solid and init the face param
		bool addFace(Face *face);
		bool addEdge(Edge *edge);
		bool addVertex(Vertex *vertex);

		//ͨ��pointֵ������е�vertex
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

		//��face�����loop
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

		//��loop�е�ĩβ����µ�halfedge
		bool addHe(HalfEdge *he);
		//�ж���������Ƿ������loop��
		bool verInLoop(Vertex *vertex);
		//�ҵ�����������halfedge��
		HalfEdge *findHeByVer(Vertex *vertex);
	};

	class HalfEdge
	{
	public:
		int id_halfedge;
		HalfEdge *next;
		HalfEdge *prev;
		//����halfedge��Ӧedge�İ��
		HalfEdge *oppositeHe;
		//halfedge���ڵĻ�
		Loop *he2Loop;
		//halfedge ���ڵı�
		Edge *he2Edge;
		//halfedge�ĳ�����
		Vertex *headVertex;
		//halfedge���յ�
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
		//����������Ӧ������haledge
		HalfEdge *halfedge0;
		HalfEdge *halfedge1;

	public:
		Edge();
	};
}
