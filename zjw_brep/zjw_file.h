/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "zjw_halfedge.h"
using namespace zjw_halfedge;
using namespace std;


class ZjwBrepFile
{
public:
	//两位数组
	vector<vector<Point>> ver2dimList;
	Point sweepPoint;
public:
	bool loadZjwBrepFile(string & objPath);
};
