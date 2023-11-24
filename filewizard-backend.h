#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>
#include <QDir>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    void findFiles(QString dirName = NULL, QString f = NULL);
    bool performEditOperations(QStringList files, QString destinationDir = NULL);
    void setOperationMode(QString op), setOriginalFileNames(QString names);
    bool isFilesFound() const;
    QString getFiles() const;
    QString getOperationMode() const;
    QDir getRootDirectory() const;
private:
    QStringList filters, changedFiles, failedFiles;
    QString operationMode, oldFileNames, newFileNames;
    QDir rootDirectory, destinationDirectory;
    bool objectsFound;
    void assignFiles(QStringList fileNames);
};

#endif // FILEWIZARDBACKEND_H
