#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>
#include <QDir>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    bool objectsFound(QString dirName, QString f = NULL);
    QString getRootFolder() const;
    QString getObjects() const;
    void performEditOperations(QString files);

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects;
    QDir rootFolder;
};

#endif // FILEWIZARDBACKEND_H
