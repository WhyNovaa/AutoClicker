#include "autoclicker.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    AutoClicker w;
    w.show();
    return a.exec();
}
