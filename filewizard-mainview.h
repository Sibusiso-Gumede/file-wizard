#ifndef FILEWIZARDMAINVIEW_H
#define FILEWIZARDMAINVIEW_H

#include <QMainWindow>
#include <QAction>
#include <QTreeWidget>
#include <QFileSystemModel>

class FileWizardMainView : public QMainWindow {
    Q_OBJECT
public:
    FileWizardMainView();
private slots:
    void handleAction(QAction *a);
private:
    QTreeWidget *fileList;
    QFileSystemModel *fileSystem;
};
#endif // FILEWIZARDMAINVIEW_H
