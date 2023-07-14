#include "filewizard-backend.h"
#include <QDir>

FileWizardBackEnd::FileWizardBackEnd(){

}

QString FileWizardBackEnd::findObjects(QString dirName)
{
    QDir directory(dirName);
    objects = directory.entryList(filters);

    if(objects.isEmpty())
        return (objects << "No folder(s) or file(s) were found.").join("");
    else
    {
        objects.prepend("Objects found in the selected directory:")
        return objects.join("\n");
    }
}
