#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    QString findObjects(QString dirName, QString f = "None");

private:
    QStringList filters, changedObjects, failedObjects;
    QString objects;
};

#endif // FILEWIZARDBACKEND_H
