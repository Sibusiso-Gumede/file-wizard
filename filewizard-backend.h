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
    QString getRootFolder() const;
    QString getObjects() const;
    void performEditOperations(QString action);
    bool isObjectsFound() const;
    void assignObjects(QStringList objectList);

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects;
    QDir rootFolder;
    bool objectsFound;
};

#endif // FILEWIZARDBACKEND_H
