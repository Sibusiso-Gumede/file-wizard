#ifndef FILEWIZARDMAINVIEW_H
#define FILEWIZARDMAINVIEW_H

#include <QMainWindow>
#include <QAction>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QPushButton>

class FileWizardMainView : public QMainWindow {
    Q_OBJECT
public:
    FileWizardMainView(QString workingDir);
private slots:
    void handleAction(QAction *a);
private:
    QTreeWidget* fileList;
    QFileSystemModel* fileSystem;
    QPushButton* browseButton;
};
#endif // FILEWIZARDMAINVIEW_H
