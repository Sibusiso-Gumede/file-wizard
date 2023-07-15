#ifndef FILEWIZARDBACKEND_H
#define FILEWIZARDBACKEND_H

#include <QString>
#include <QStringList>

class FileWizardBackEnd
{
public:
    FileWizardBackEnd();
    QString findObjects(QString dirName, QString f);

private:
    QStringList filters, objects, changedObjects, failedObjects;
};

#endif // FILEWIZARDBACKEND_H
