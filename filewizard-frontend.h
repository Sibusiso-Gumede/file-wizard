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
#include <QFileSystemModel>
#include <QTreeView>
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
private:
    QPushButton *folderButton, *editButton;
    QLineEdit *dataField;
    QFileDialog *fileDialog;
    FileWizardBackEnd *data;
    QDialog *editOperationsDialog;
    QTextEdit *informationWidget;
    QFileSystemModel *fileSystemModel;
    QTreeView *treeView;
    QLabel *heading, *programInstructions;
    void displayObjects(QString l);
};
#endif // FILEWIZARDFRONTEND_H
