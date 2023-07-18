#include "filewizard-frontend.h"
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>

// member function definitions of the filewizard-frontend class.

FileWizardFrontEnd::FileWizardFrontEnd(QWidget *parent) :
    QMainWindow(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    dataField(new QLineEdit(this)),
    informationWidget(new QTextEdit(this))
{
    data = new FileWizardBackEnd;

    // define/declare local objects.
    QLabel *heading, *stepOne, *stepTwo, *dataFieldLabel;
    heading = new QLabel(this);
    stepOne = new QLabel(this);
    stepTwo = new QLabel(this);
    dataFieldLabel = new QLabel("&Filter", this);

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

    dataFieldLabel->setBuddy(dataField);

    // actions to rename, move or delete the object(s).
    QActionGroup* editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/r.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon("icons/a.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon("icons/x.png"), "&Delete", this));
    editGroup->addAction(new QAction(QIcon("icons/c.png"), "&Copy", this));

    // action menu.
    QMenu* editMenu = new QMenu(this);
    editMenu->addActions(editGroup->actions());
    editButton->setMenu(editMenu);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    // organize the widgets of the mainwindow in a vertical structure.
    verticalLayout->addWidget(heading);
    verticalLayout->addWidget(stepOne);
    verticalLayout->addWidget(folderButton);
    verticalLayout->addWidget(stepTwo);
    verticalLayout->addWidget(dataFieldLabel);
    verticalLayout->addWidget(dataField);
    verticalLayout->addWidget(editButton);
    verticalLayout->addWidget(informationWidget);

    centralWidget->setLayout(verticalLayout);
    setCentralWidget(centralWidget);

    connect(folderButton, SIGNAL(clicked()), this, SLOT(processFolderButton()));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
}

FileWizardFrontEnd::~FileWizardFrontEnd()
{
    delete data;
}

void FileWizardFrontEnd::handleAction(QAction* a)
{
    // check if the data field 'QLineEdit' has a valid value:
    // if yes, then proceed to handle the action;
    // if not, then proceed to display a QMessageBox instructing
    // the user to enter a valid 'object filter.'
    //if(!(dataField->text()).isEmpty())
    //    buffer = data->findObjects(rootFolder, dataField->text());
    //else
        //buffer = "";
}

void FileWizardFrontEnd::processFolderButton()
{
    // show the file dialog,
    // find the objects in the selected directory
    // and display them. 
    displayObjects(data->findObjects(QFileDialog::getExistingDirectory
                     (0, "Select Root Folder", QDir::currentPath())));
}

void FileWizardFrontEnd::displayObjects(QString objects)
{
    // display objects on the QTextEdit widget.
    //informationWidget->
    informationWidget->setPlainText(objects);
}
