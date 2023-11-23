#include "filewizard-backend.h"
#include <QFileInfo>
#include <QFile>
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
        qDebug() << "Executing list all root directory objects block.";

        rootDirectory = QDir(dirName);
        // list all objects, but exclude special entries.
        assignFiles(rootDirectory.entryList(QDir::NoDotAndDotDot |
                                         QDir::AllDirs | QDir::Files));
    }
    else
    {
        qDebug() << "Executing find filtered objects block.";

        filters << fileFilter;
        // find objects that match the filters.
        assignFiles(rootDirectory.entryList(filters, QDir::Dirs |
                    QDir::Files));
    }
}

QString FileWizardBackEnd::getFiles() const
{
    return oldFileNames;
}

QDir FileWizardBackEnd::getRootDirectory() const
{
    return rootDirectory;
}

bool FileWizardBackEnd::performEditOperations(QStringList fileNames, QString destinationDir)
{
    // if the chosen operation is successfully performed, the function will return true,
    // otherwise it will return false.

    int index = 0;

    if(operationMode == "&Move" || operationMode == "&Copy")
    {
        qDebug() << "Executing move/copy block.";

        if(!destinationDir.isEmpty())
        {
            destinationDirectory = QDir(destinationDir);
            if(!destinationDirectory.exists())
                destinationDirectory.mkpath(destinationDir);

            foreach(QString fileName, fileNames)
            {
                if(operationMode == "&Move")
                {

                }
                else if(operationMode == "&Copy")
                {
                    QFile file(rootDirectory.absoluteFilePath(fileName));
                    file.copy(destinationDirectory.absolutePath()+fileName);
                }
                index++;
            }
            return true;
        }
        else
            return false;
    }

    else if(oldFileNames.size() == fileNames.size())
    {
        qDebug() << "Executing rename/delete block.";

        foreach(QString fileName, fileNames)
        {
            QFileInfo info(rootDirectory.absolutePath() + "/" + oldFileNames[index]);
            // Perform changes to the files.
            if(operationMode == "&Rename")
            {
                QString newFileName = info.absoluteFilePath().section("/", 0, -2)
                        + "/" + fileName;
                if(rootDirectory.rename(info.absolutePath(), newFileName))
                    changedFiles << info.absolutePath();
                else
                    failedFiles << info.absolutePath();
            }
            else if(operationMode == "&Delete")
            {
                qDebug("Executing delete block.");
            }
        }
        return true;
    }

    else
        return false;
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
        oldFileNames = fileNames.join("\n");
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
