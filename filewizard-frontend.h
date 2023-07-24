#ifndef FILEWIZARDFRONTEND_H
#define FILEWIZARDFRONTEND_H

#include <QMainWindow>
#include <QAction>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include "filewizard-backend.h"

class FileWizardFrontEnd : public QMainWindow
{
    Q_OBJECT
public:
    FileWizardFrontEnd(QWidget *parent = nullptr);
    ~FileWizardFrontEnd();
private slots:
    void handleAction(QAction *a = nullptr);
private:
    QPushButton *folderButton, *editButton;
    QLineEdit *dataField;
    QTextEdit *informationWidget;
    QFileDialog *fileDialog;
    FileWizardBackEnd *data;
    void displayObjects(QString l);
};
#endif // FILEWIZARDFRONTEND_H
