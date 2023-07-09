#include "filewizard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileWizard window;
    window.show();
    return a.exec();
}
