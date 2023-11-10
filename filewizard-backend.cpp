#include "filewizard-backend.h"
#include <QFileInfo>
#include <QDebug>

FileWizardBackEnd::FileWizardBackEnd()
{
    objectsFound = false;
}

void FileWizardBackEnd::findObjects(QString dirName, QString fileFilter)
{
    objectsFound = false;
    if(fileFilter == NULL)
    {
        rootDirectory = QDir(dirName);
        // list all objects, but exclude special entries.
        assignObjects(rootDirectory.entryList(QDir::NoDotAndDotDot |
                                         QDir::AllDirs | QDir::Files));
    }

    else
    {
        qDebug() << "Executing find filtered objects block.";

        filters << fileFilter;
        // find objects that match the filters.
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
    if(action == "&Move")
    {
        qDebug("Executing move block.");
    }
    else if(action == "&Delete")
    {
    }
    else if(action == "&Copy")
    {
    }
}

bool FileWizardBackEnd::isObjectsFound() const
{
    return objectsFound;
}

void FileWizardBackEnd::assignObjects(QStringList objectList)
{
    if(!objectList.isEmpty())
    {
        objectsFound = true;
        objects = objectList.join("\n");
    }

    else
    {
        objectsFound = false;
        //objects = "No file(s)/folder(s) were found "
                  //"in the selected directory:";
    }
}

void FileWizardBackEnd::setOperationMode(QString op)
{
    operationMode = op;
}

QString FileWizardBackEnd::getOperationMode() const
{
    return operationMode;
}
