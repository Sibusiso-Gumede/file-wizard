#include "filewizard-backend.h"
#include <QFileInfo>

FileWizardBackEnd::FileWizardBackEnd(){}

bool FileWizardBackEnd::objectsFound(QString dirName, QString f)
{
    // find objects in the selected directory.
    // if no filters are specified, proceed to
    // find all files/folders within the directory.
    // else, find files/folders that match the filters.
    rootFolder = QDir(dirName);

    QStringList objectList;
    QString foundMsg("Objects found in the selected directory:"),
            notFoundMsg("No file(s)/folder(s) were found "
                        "in the selected directory:");
    // the subcondition structures check whether objects were found
    // and return them. else, they return a not found message.
    if(f == NULL)
    {
        // list all objects, but exclude special entries.
        objectList = rootFolder.entryList(QDir::NoDotAndDotDot |
                                         QDir::AllDirs |
                                         QDir::Files);
        if(!objectList.isEmpty())
        {
            objectList.prepend(foundMsg);
            objects = objectList.join("\n");
            return  true;
        }
        else
        {
            objects = notFoundMsg;
            return false;
        }
    }
    else
    {
        filters << f;
        // list objects that match the filters.
        objectList = rootFolder.entryList(filters, QDir::Dirs |
                                         QDir::Files);
        if(!objectList.isEmpty())
        {
            objectList.prepend(foundMsg);
            objects = objectList.join("\n");
            return true;
        }
        else
        {
            objects = notFoundMsg;
            return false;
        }
    }
}

QString FileWizardBackEnd::getRootFolder() const
{
    return rootFolder.path();
}

QString FileWizardBackEnd::getObjects() const
{
    return objects;
}

void FileWizardBackEnd::performEditOperations(QString files)
{

}
