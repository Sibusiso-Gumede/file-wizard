#include "filewizard-mainview.h"
#include <QDir>
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QStringList>
#include <QLabel>

// member function definitions of the filewizard-mainview class.

FileWizardMainView::FileWizardMainView(QWidget* parent) : QDialog(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    dataField(new QLineEdit(this)),
    informationWidget(new QTextEdit(this)){

    QLabel *heading, *stepOne, *stepTwo;
    heading = new QLabel(this);
    stepOne = new QLabel(this);
    stepTwo = new QLabel(this);

    // define properties for the main dialog.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 600);
    setFont(QFont("Helvetica", 10));

    // define properties for the widgets.
    heading->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    heading->setText("DO WHAT YOUR NORMAL\nFILE SYSTEM CANNOT DO.");
    heading->setAlignment(Qt::AlignCenter);

    stepOne->setText("Please select the folder of the objects to be editted.");
    stepTwo->setText("Please enter a filter to distinguish the objects.\ne.g. '*.zip' or 'cooking.*'");

    // actions to rename, move or delete the object(s).
    QActionGroup* editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/r.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon("icons/a.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon("icons/x.png"), "&Delete", this));
    editGroup->addAction(new QAction(QIcon("icons/c.png"), "&Copy", this));

    // organize the widgets of the main dialog in a vertical structure.
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(heading);
    verticalLayout->addWidget(stepOne);
    verticalLayout->addWidget(folderButton);
    verticalLayout->addWidget(stepTwo);
    verticalLayout->addWidget(editButton);
    verticalLayout->addWidget(dataField);

    verticalLayout->addWidget(informationWidget);
    setLayout(verticalLayout);

    // action menu.
    QMenuBar* menu = new QMenuBar(this);

    //QMenu* fileMenu =;
    //fileMenu->addActions(editGroup->actions());

    connect(folderButton, SIGNAL(clicked()), this, SLOT(popFileDialog()));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
}

void FileWizardMainView::handleAction(QAction* a){

}

void FileWizardMainView::popFileDialog(){
    QString dirName = QFileDialog::getExistingDirectory(this, "Open Root Folder",
    QDir::homePath());

    QDir rootDirectory(dirName);

//    QStringList filters;

}
