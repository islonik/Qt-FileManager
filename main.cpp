#include <QApplication>

#include "filemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //MainWindow *mainWin = new MainWindow;
    //mainWin->show();
	MainWindow mainWin;
    return mainWin.exec();
}
