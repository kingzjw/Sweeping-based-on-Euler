/*
author: Zhou Jiawei
purpose: cad homewok
statement: this code is bulid by Zhou Jiawei.If you want to use it ,
please send a email to zjwking258@163.com to get the right!
*/

#include "zjw_brep.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	QApplication a(argc, argv);
	zjw_brep w;
	w.show();
	return a.exec();
}
