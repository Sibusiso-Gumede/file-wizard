#ifndef FILEWIZARDFRONTEND_H
#define FILEWIZARDFRONTEND_H

#include <QDialog>
#include <QAction>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include "filewizard-backend.h"

class FileWizardFrontEnd : public QDialog {
    Q_OBJECT
public:
    FileWizardFrontEnd(QWidget* parent = nullptr);
private slots:
    void handleAction(QAction *a);
    QString process();
private:
    QPushButton *folderButton, *editButton;
    QLineEdit *dataField;
    QTextEdit *informationWidget;
    QFileDialog *fileDialog;
    FileWizardBackEnd *data;
    QString displayObjects(QString l);
};
#endif // FILEWIZARDFRONTEND_H
