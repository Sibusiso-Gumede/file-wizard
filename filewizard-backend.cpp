#include "filewizard-backend.h"
#include <QFileInfo>
#include <QDebug>

FileWizardBackEnd::FileWizardBackEnd()
{
    objectsFound = false;
}

void FileWizardBackEnd::findObjects(QString dirName, QString f)
{           
    if(f == NULL)
    {
        rootDirectory = QDir(dirName);
        // list all objects, but exclude special entries.
        assignObjects(rootDirectory.entryList(QDir::NoDotAndDotDot |
                                         QDir::AllDirs | QDir::Files));
    }

    else
    {
        qDebug("Executing find filtered objects block.");

        filters << f;
        // list objects that match the filters.
        assignObjects(rootDirectory.entryList(filters, QDir::Dirs |
                                         QDir::Files));
    }
}

QString FileWizardBackEnd::getObjects() const
{
    return objects;
}

QDir FileWizardBackEnd::getRootDirectory() const
{
    return rootDirectory;
}

void FileWizardBackEnd::performEditOperations(QString action)
{



}

bool FileWizardBackEnd::isObjectsFound() const
{
    return objectsFound;
}

void FileWizardBackEnd::assignObjects(QStringList objectList)
{
    QString foundMsg("Objects found in the selected directory:"),
            notFoundMsg("No file(s)/folder(s) were found "
                        "in the selected directory:");

    if(!objectList.isEmpty())
    {
        objectsFound = true;
        objectList.prepend(foundMsg);
        objects = objectList.join("\n");
    }

    else
    {
        objectsFound = false;
        objects = notFoundMsg;
    }
}
