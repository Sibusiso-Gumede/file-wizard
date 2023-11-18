#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>
#include <QDir>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    void findObjects(QString dirName = NULL, QString f = NULL);
    void performEditOperations(QStringList objectNames);
    void setOperationMode(QString op);
    bool isObjectsFound() const;
    QString getObjects() const, getOperationMode() const;
    QDir getRootDirectory() const;

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects, operationMode;
    QDir rootDirectory;
    bool objectsFound;
    void assignObjects(QStringList objectList);
};

#endif // FILEWIZARDBACKEND_H
