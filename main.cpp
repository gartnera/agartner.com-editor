#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.showMaximized();
    w.openCredencialWindow();

	
	return a.exec();
}