#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>
#include <QDir>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    void findObjects(QString dirName, QString f = NULL);
    QString getRootFolder() const;
    QString getObjects() const;
    void performEditOperations(QString files, QString action);
    bool isObjectsFound() const;

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects;
    QDir rootFolder;
    bool objectsFound;
};

#endif // FILEWIZARDBACKEND_H
