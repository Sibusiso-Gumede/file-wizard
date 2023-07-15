#include "filewizard-backend.h"
#include <QDir>

FileWizardBackEnd::FileWizardBackEnd(){

}

QString FileWizardBackEnd::findObjects(QString dirName, QString f = "None")
{
    QDir directory(dirName);
    if(f == "None")
        objects = directory.entryList();
    else
    {
        filters << f;
        objects = directory.entryList(filters);
    }
    objects.prepend("Objects found in the selected directory:");
    return objects.join("\n");
}
