#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Functions.h"

using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
