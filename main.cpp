#include "filewizard-mainview.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    FileWizardMainView window(QDir::currentPath());
    window.show();

    return a.exec();
}
