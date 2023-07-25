#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>
#include <QDir>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    QString findObjects(QString dirName, QString f = NULL);
    QString getRootFolder() const;

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects;
    QDir rootFolder;
};

#endif // FILEWIZARDBACKEND_H
