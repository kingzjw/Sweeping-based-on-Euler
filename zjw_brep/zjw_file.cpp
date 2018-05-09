/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/
#include "zjw_file.h"

bool ZjwBrepFile::loadZjwBrepFile(string & objPath)
{
	std::cout << "start load  file..." << endl;
	fstream file;
	file.open(objPath, fstream::in | fstream::out | fstream::app);
	if (!file.is_open()) {
		std::cout << "open file failed! may be you use chinese file path ,please change it to english path!" << endl;
		return false;
	}
	string startStr;
	string typeStr;
	Point tempPoint;
	while (file >> typeStr)
	{
		//开始一个face的读取
		if (typeStr == "start")
		{
			vector<Point> verForFace;

			while (file >> typeStr)
			{
				if (typeStr == "out")
				{
					file >> tempPoint.x;
					file >> tempPoint.y;
					file >> tempPoint.z;
					//cout << "out: " << tempPoint.x <<" "<<tempPoint.y <<" "<< tempPoint.z << endl;
					verForFace.push_back(tempPoint);
				}
				else if (typeStr == "inner")
				{
					file >> tempPoint.x;
					file >> tempPoint.y;
					file >> tempPoint.z;
					verForFace.push_back(tempPoint);
					//cout << "inner: " << tempPoint.x << " " << tempPoint.y << " " << tempPoint.z << endl;
				}
				else if (typeStr == "end")
				{
					ver2dimList.push_back(verForFace);
					break;
				}
				else
				{
					std::cout << "error here 1!" << std::endl;
				}
			}
		}
		else if (typeStr == "sweeppoint")
		{
			file >> tempPoint.x;
			file >> tempPoint.y;
			file >> tempPoint.z;
			sweepPoint = tempPoint;
		}
	}
	file.close();
	std::cout << "finish load obj file !" << endl;
	return true;
}
