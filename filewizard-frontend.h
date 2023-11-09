#ifndef FILEWIZARDFRONTEND_H
#define FILEWIZARDFRONTEND_H

#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include "filewizard-backend.h"

class FileWizardFrontEnd : public QMainWindow
{
    Q_OBJECT
public:
    FileWizardFrontEnd(QWidget *parent = nullptr);
    ~FileWizardFrontEnd();
private slots:
    void handleAction(QAction *action = nullptr);
    void renameObjects();
private:
    QPushButton *folderButton, *editButton, *saveChangesButton;
    QLineEdit *dataField;
    QFileDialog *fileDialog;
    FileWizardBackEnd *data;
    QDialog *editOperationsDialog;
    QTextEdit *informationWidget;
    QLabel *heading, *programInstructions;
    void displayObjects(QString l);
};
#endif // FILEWIZARDFRONTEND_H
