#include "filewizard-mainview.h"
#include <QDir>
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QActionGroup>
#include <QVBoxLayout>

// member function definitions of the filewizard-mainview class.

FileWizardMainView::FileWizardMainView() : fileList(new QTreeWidget(this)),
    fileSystem(new QFileSystemModel(this)), browseButton(new QPushButton("&Browse", this)){

    // define properties for the main window.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 200);
    setFont(QFont("Helvetica", 10));
    browseButton->setAutoDefault(true);

    // organize the widgets of the main window in a vertical structure.
    QVBoxLayout* widgetLayout = new QVBoxLayout(this);
    widgetLayout->addWidget(fileList);
    widgetLayout->addWidget(browseButton);
    //fileSystem->setRootPath(QDir::)

    // action for setting up the root folder.
    QAction* browse = new QAction(QIcon("icons/root.png"), "&Browse", this);
    browseButton->addAction(browse);

    // actions to rename, move or delete the file(s).
    QActionGroup* editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/rename.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon("icons/move.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon("icons/delete.png"), "&Delete", this));

    // action menu.
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addActions(editGroup->actions());

    connect(browse, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
}

void FileWizardMainView::handleAction(QAction* a){

}
