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
    void performEditOperations(QStringList files);
    void setOperationMode(QString op), setOriginalFileNames(QString names);
    bool isFilesFound() const;
    QString getFiles() const;
    QString getOperationMode() const;
    QDir getRootDirectory() const;

private:
    QStringList filters, changedfiles, failedFiles;
    QString operationMode, originalFileNames, newFileNames;
    QDir directory;
    bool objectsFound;
    void assignFiles(QStringList fileNames);
};

#endif // FILEWIZARDBACKEND_H
