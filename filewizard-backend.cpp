#include "filewizard-backend.h"
#include <QFileInfo>
#include <QDebug>

FileWizardBackEnd::FileWizardBackEnd()
{
    objectsFound = false;
}

void FileWizardBackEnd::findFiles(QString dirName, QString fileFilter)
{
    objectsFound = false;
    if(fileFilter == NULL)
    {
        directory = QDir(dirName);
        // list all objects, but exclude special entries.
        assignFiles(directory.entryList(QDir::NoDotAndDotDot |
                                         QDir::AllDirs | QDir::Files));
    }

    else
    {
        qDebug() << "Executing find filtered objects block.";

        filters << fileFilter;
        // find objects that match the filters.
        assignFiles(directory.entryList(filters, QDir::Dirs |
                    QDir::Files));
    }
}

QString FileWizardBackEnd::getFiles() const
{
    return originalFileNames;
}

QDir FileWizardBackEnd::getRootDirectory() const
{
    return directory;
}

void FileWizardBackEnd::performEditOperations(QStringList files)
{
    if(originalFileNames.size() == files.size())
    {
        int index = 0;
        foreach(QString fileName, files)
        {
            QFileInfo info(directory.absolutePath() + "/" + originalFileNames);
            // Perform changes to the files.
            if(operationMode == "&Rename")
            {
                QString rawFileName = fileName.section(".", 0, 0);
                QString newName = info.absoluteFilePath().section("/", 0, -2)
                        + "/" + rawFileName;
            }
            else if(operationMode == "&Move")
            {
                qDebug("Executing move block.");
            }
            else if(operationMode == "&Delete")
            {
                qDebug("Executing delete block.");
            }
            else if(operationMode == "&Copy")
            {
                qDebug("Executing copy block.");
            }
        }
    }
}

bool FileWizardBackEnd::isFilesFound() const
{
    return objectsFound;
}

void FileWizardBackEnd::assignFiles(QStringList fileNames)
{
    if(!fileNames.isEmpty())
    {
        objectsFound = true;
        originalFileNames = fileNames.join("\n");
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
