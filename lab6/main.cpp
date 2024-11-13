#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Functions.h"
//#include <QLocale>

using namespace std;

int main(int argc, char *argv[])
{
    /*QLocale::setDefault(QLocale::Russian);*/
    setlocale(LC_ALL, "ru_RU.UTF-8");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
