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
    // if the chosen operation is successfully performed, the function will return true(that
    // is, in the scenario where atleast one file is successfully processed).
    // otherwise it will return false.

    if(operationMode == "&Move" || operationMode == "&Copy")
    {
        qDebug() << "Executing move/copy block.";

        if(!destinationDir.isEmpty())
        {
            destinationDirectory = QDir(destinationDir);
            // if the destination directory does not exist then construct it.
            if(!destinationDirectory.exists())
                destinationDirectory.mkpath(destinationDir);

            foreach(QString fileName, fileNames)
            {
                // create an object of the source file.
                QFile file(rootDirectory.absoluteFilePath(fileName));
                // if the source file exists, copy it to chosen destination.
                if(file.exists())
                    file.copy(destinationDirectory.absolutePath()+fileName);
                // else, add to the failed files list and continue to process
                // the next file.
                else
                {
                    failedFiles << fileName;
                    continue;
                }

                // delete the source file if it's a move operation.
                if(operationMode == "&Move")
                    file.remove();
                // add filename to the changed files list.
                changedFiles << rootDirectory.absoluteFilePath(fileName);
            }
            if(!changedFiles.isEmpty())
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else if(oldFileNames.size() == fileNames.size())
    {
        qDebug() << "Executing rename/delete block.";

        bool operationSuccessful = false;
        int index = 0;

        foreach(QString fileName, fileNames)
        {
            // rename/delete the file.
            QString oldFileName = static_cast<QChar>(oldFileNames[index]);
            if(operationMode == "&Rename")
            {
                QString newFileName = rootDirectory.absolutePath() + "/" + fileName;

                if(rootDirectory.rename(rootDirectory.absoluteFilePath(oldFileName), newFileName))
                    operationSuccessful = true;
                else
                    operationSuccessful = false;
            }
            else if(operationMode == "&Delete")
            {
                if(rootDirectory.remove(fileName))
                    operationSuccessful = true;
                else
                    operationSuccessful = false;
            }

            if(operationSuccessful)
                changedFiles << rootDirectory.absoluteFilePath(oldFileName);
            else
                failedFiles << rootDirectory.absoluteFilePath(oldFileName);

            index++;
        }
        if(!changedFiles.isEmpty())
            return true;
        else
            return false;
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
