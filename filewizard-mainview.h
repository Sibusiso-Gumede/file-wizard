#ifndef FILEWIZARDMAINVIEW_H
#define FILEWIZARDMAINVIEW_H

#include <QDialog>
#include <QAction>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QPushButton>
#include <QString>
#include <QFileDialog>

class FileWizardMainView : public QDialog {
    Q_OBJECT
public:
    FileWizardMainView(QWidget* parent = nullptr);
private slots:
    void handleAction(QAction *a);
    void popFileDialog();
private:
    QTreeWidget* fileList;
    QFileSystemModel* fileSystem;
    QPushButton* browseButton;
    QFileDialog* fileDialog;
};
#endif // FILEWIZARDMAINVIEW_H
