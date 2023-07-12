#include "filewizard-mainview.h"
#include <QDir>
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QActionGroup>
#include <QVBoxLayout>

// member function definitions of the filewizard-mainview class.

FileWizardMainView::FileWizardMainView(QWidget* parent) : QDialog(parent), fileList(new QTreeWidget(this)),
    fileSystem(new QFileSystemModel(this)), browseButton(new QPushButton("&Browse", this)),
    fileDialog(new QFileDialog(this, "Open Root Folder", QDir::currentPath(), "*.*")){

    // properties for the main window.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 600);
    setFont(QFont("Helvetica", 10));

    // propeties for the widgets.
    //fileList->setMinimumSize(500, 250);

    // organize the widgets of the main window in a vertical structure.
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(fileList);
    verticalLayout->addWidget(browseButton);
    setLayout(verticalLayout);

    // actions to rename, move or delete the file(s).
    QActionGroup* editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon(workingDir+"/icons/o.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon(workingDir+"/icons/c.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon(workingDir+"/icons/x.png"), "&Delete", this));

    // action menu.
    QMenuBar* menu = new QMenuBar(this);
    QMenu* fileMenu = menu->addMenu("&File");
    fileMenu->addActions(editGroup->actions());

    connect(browseButton, SIGNAL(clicked()), this, SLOT(popFileDialog(workingDir)));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
}

void FileWizardMainView::handleAction(QAction* a){

}

void FileWizardMainView::popFileDialog(){
    QString dirName = fileDialog->getExistingDirectory();
    QDir* rootDirectory = new QDir(dirName);

    QStringList filters;
}
