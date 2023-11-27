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
    bool performEditOperations(QString destinationDir = NULL);
    void setOperationMode(QString op), setOriginalFileNames(QString names);
    void setNewFileNames(QString n);
    void clearLists();
    bool isFilesFound() const;
    QString getCurrentFiles() const, getChangedFiles() const, getFailedFiles() const;
    QString getOperationMode() const;
    QDir getRootDirectory() const;
private:
    QStringList filters, changedFiles, failedFiles;
    QString operationMode, currentFileNames, newFileNames;
    QDir rootDirectory, destinationDirectory;
    bool filesFound;
    void assignFiles(QStringList fileNames);
};

#endif // FILEWIZARDBACKEND_H
