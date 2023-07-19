#include "filewizard-frontend.h"
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

// member function definitions of the filewizard-frontend class.

FileWizardFrontEnd::FileWizardFrontEnd(QWidget *parent) :
    QMainWindow(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    dataField(new QLineEdit("&Filter", this)),
    informationWidget(new QTextEdit(this)),
    data(new FileWizardBackEnd())
{
    // define/declare local objects.
    QLabel *heading, *programInstructions, *dataFieldLabel;
    heading = new QLabel(this);
    programInstructions = new QLabel(this);
    dataFieldLabel = new QLabel("&Filter", this);

    // define properties for the main window.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 600);
    setFont(QFont("Helvetica", 10));

    // define properties for the widgets.
    heading->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    heading->setText("DO WHAT YOUR NORMAL\nFILE SYSTEM CANNOT DO.");
    heading->setAlignment(Qt::AlignCenter);

    dataField->setAlignment(Qt::AlignHCenter);
    dataField->setMaximumSize(100, 30);
    folderButton->setMaximumSize(100, 30);
    editButton->setMaximumSize(100, 30);

    // detailed program instructions for the user.
    programInstructions->setText("PROGRAM INSTRUCTIONS:\n"
                    "\n1) Select the root folder of the objects you"
                    "\n   want to edit."
                    "\n2) Type an extension or a string that is part"
                    "\n   of the object names to filter them."
                    "\n   e.g. '*.zip' or 'recipes.*'"
                    "\n3) Choose an edit option from the 'edit button'.\n");

    // attach a label to the data field.
    dataFieldLabel->setBuddy(dataField);

    // actions to rename, move or delete the object(s).
    QActionGroup* editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/r.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon("icons/a.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon("icons/x.png"), "&Delete", this));
    editGroup->addAction(new QAction(QIcon("icons/c.png"), "&Copy", this));

    // action menu to group the different edit options.
    QMenu* editMenu = new QMenu(this);
    editMenu->addActions(editGroup->actions());
    editButton->setMenu(editMenu);

    // the layout format for the mainwindow.
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    horizontalLayout->insertSpacing(0, 100);
    horizontalLayout->insertWidget(1, dataFieldLabel, Qt::AlignCenter);
    horizontalLayout->insertWidget(2, dataField, Qt::AlignCenter);
    horizontalLayout->insertSpacing(3, 100);

    verticalLayout->addWidget(heading);
    verticalLayout->addWidget(programInstructions);
    verticalLayout->addWidget(folderButton);
    verticalLayout->addWidget(dataField);
    verticalLayout->addLayout(horizontalLayout);
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
