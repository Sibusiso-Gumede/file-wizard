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
    return oldFileNames;
}

QDir FileWizardBackEnd::getRootDirectory() const
{
    return directory;
}

void FileWizardBackEnd::performEditOperations(QStringList fileNames, QString destinationDir)
{
    QDir destDirectory;

    if(!destinationDir.isNull())
        destDirectory = QDir(destinationDir);

    int index = 0;
    foreach(QString fileName, fileNames)
    {
        if(destDirectory.exists())
        {
            if(operationMode == "&Move")
            {
                QString ;
            }
            else if(operationMode == "&Copy")
            {
                QFileInfo destinationFile = QFileInfo(destDirectory, fileName);
                QFile fileCopy();
            }
        }
        else if(oldFileNames.size() == fileNames.size())
        {
            QFileInfo info(directory.absolutePath() + "/" + oldFileNames[index]);
            // Perform changes to the files.
            if(operationMode == "&Rename")
            {
                QString newFileName = info.absoluteFilePath().section("/", 0, -2)
                        + "/" + fileName;
                if(directory.rename(info.absolutePath(), newFileName))
                    changedFiles << info.absolutePath();
                else
                    failedFiles << info.absolutePath();
            }
            else if(operationMode == "&Delete")
            {
                qDebug("Executing delete block.");
            }
        }
        index++;
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
