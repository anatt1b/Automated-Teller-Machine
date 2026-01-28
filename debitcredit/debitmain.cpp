#include "debitcreditwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    debitcreditWindow w;
    w.show();
    return a.exec();
}
