#include "filewizard-mainview.h"
#include <QDir>
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QActionGroup>

FileWizardMainView::FileWizardMainView() : fileList(new QTreeWidget(this)),
    fileSystem(new QFileSystemModel(this)){
    setWindowTitle("File Wizard");
    setMinimumSize(800, 200);
    setFont(QFont("Helvetica", 10));

    // choose the root folder.
    QAction* root = new QAction(QIcon("icons/root.png"), "&Root Folder", this);

    // choose the type of objects to be edited.
    QActionGroup* editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/folder.png"), "&Folder", this));
    editGroup->addAction(new QAction(QIcon("icons/file.png"), "&File", this));

    // options menu.
    QMenu* editMenu = menuBar()->addMenu("&Edit");
    editMenu->addActions()
    //fileList.
    //fileSystem->setRootPath(QDir::)
}
