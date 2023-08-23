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
    void performEditOperations(QString action);
    bool isObjectsFound() const;
    QString getObjects() const;
    QDir getDirectory() const;

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects;
    QDir rootFolder;
    bool objectsFound;
    void assignObjects(QStringList objectList);
};

#endif // FILEWIZARDBACKEND_H
