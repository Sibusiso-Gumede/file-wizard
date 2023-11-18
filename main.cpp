#include "filewizard-frontend.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileWizardFrontEnd window;
    window.show();

    return a.exec();
}
