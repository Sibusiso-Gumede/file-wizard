#include "filewizard-mainview.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    FileWizardMainView window;
    window.show();

    return a.exec();
}
