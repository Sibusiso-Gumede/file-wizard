#ifndef FILEWIZARDFRONTEND_H
#define FILEWIZARDFRONTEND_H

#include <QMainWindow>
#include <QAction>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QTreeView>
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
    QPushButton *folderButton, *editButton, *omitButton, *insertButton;
    QLineEdit *dataField;
    QFileDialog *fileDialog;
    FileWizardBackEnd *data;
    QMessageBox *editModeBox;
    QDialog *editOperationsDialog;
    QTextEdit *informationWidget;
    QFileSystemModel *fileSystemModel;
    QTreeView *treeView;
    void displayObjects(QString l);
};
#endif // FILEWIZARDFRONTEND_H
