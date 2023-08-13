#include "filewizard-frontend.h"
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QActionGroup>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include <QMessageBox>

// function definitions of the filewizard-frontend class.

FileWizardFrontEnd::FileWizardFrontEnd(QWidget *parent) :
    QMainWindow(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    dataField(new QLineEdit(this)),
    informationWidget(new QTextEdit(this)),
    fileDialog(new QFileDialog(this, "Root Folder", QDir::currentPath())),
    data(new FileWizardBackEnd())
{
    // define/declare local objects.
    QLabel *heading, *programInstructions;
    heading = new QLabel(this);
    programInstructions = new QLabel(this);

    // define properties for the main window.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 600);
    setFont(QFont("Helvetica", 10));

    // define properties for the widgets.
    heading->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    heading->setText("DO WHAT YOUR NORMAL\nFILE SYSTEM CANNOT DO.");
    heading->setAlignment(Qt::AlignCenter);
    fileDialog->setFileMode(QFileDialog::Directory);

    // the sizes of the widgets
    folderButton->setMaximumSize(100, 30);
    dataField->setMaximumSize(300, 30);
    dataField->setPlaceholderText("*.zip/recipes.*/*.mp4");
    editButton->setMaximumSize(100, 30);

    // detailed program instructions for the user.
    programInstructions->setText("PROGRAM INSTRUCTIONS:\n"
                    "\n1) Select the root folder of the objects you"
                    "\n   want to edit."
                    "\n2) Type an extension or a string that is part"
                    "\n   of the object names to filter them."
                    "\n3) Choose an edit option from the 'edit button'.\n");

    // actions to rename, move or delete the object(s).
    QActionGroup *editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/r.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon("icons/a.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon("icons/x.png"), "&Delete", this));
    editGroup->addAction(new QAction(QIcon("icons/c.png"), "&Copy", this));

    // action menu to group the different edit options.
    QMenu* editMenu = new QMenu(this);
    editMenu->addActions(editGroup->actions());
    editButton->setMenu(editMenu);

    // the layout format of the mainwindow.
    QWidget *centralWidget = new QWidget(this);
    QBoxLayout *verticalLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QBoxLayout *horizontalLayout1 = new QBoxLayout(QBoxLayout::LeftToRight, this);
    QBoxLayout *horizontalLayout2 = new QBoxLayout(QBoxLayout::LeftToRight, this);
    QBoxLayout *horizontalLayout3 = new QBoxLayout(QBoxLayout::LeftToRight, this);

    // FIX: align each action widget to the center.
    horizontalLayout1->addSpacing(300);
    horizontalLayout1->addWidget(folderButton, Qt::AlignHCenter);
    horizontalLayout1->addSpacing(300);

    horizontalLayout2->addSpacing(300);
    horizontalLayout2->addWidget(dataField, Qt::AlignHCenter);
    horizontalLayout2->addSpacing(300);

    horizontalLayout3->addSpacing(300);
    horizontalLayout3->addWidget(editButton, Qt::AlignHCenter);
    horizontalLayout3->addSpacing(300);

    verticalLayout->addWidget(heading);
    verticalLayout->addWidget(programInstructions);
    verticalLayout->addLayout(horizontalLayout1);
    verticalLayout->addLayout(horizontalLayout2);
    verticalLayout->addLayout(horizontalLayout3);
    verticalLayout->addWidget(informationWidget);

    centralWidget->setLayout(verticalLayout);
    setCentralWidget(centralWidget);

    connect(folderButton, SIGNAL(clicked()), this, SLOT(handleAction()));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
}

FileWizardFrontEnd::~FileWizardFrontEnd()
{
    delete data;
}

void FileWizardFrontEnd::handleAction(QAction* a)
{
    // TODO: add routines for the different actions.
    // check if the data field 'QLineEdit' has a valid value:
    // if yes, then proceed to handle the action;
    // if not, then proceed to display a QMessageBox instructing
    // the user to enter a valid 'object filter.'

    QString buffer;

    if(a == nullptr)
        buffer = data->findObjects(fileDialog->getExistingDirectory());
    else if(dataField->isModified()){
        while(true){
            buffer = data->getRootFolder();
            if(!buffer.isEmpty()){
                if(a->text() == "Rename"){
                    buffer = data->findObjects(buffer, dataField->text());
                    break;
                }
                else if(a->text() == "Move"){
                    buffer = data->findObjects(buffer, dataField->text());
                    break;
                }
                else if(a->text() == "Delete"){
                    buffer = data->findObjects(buffer, dataField->text());
                    break;
                }

            }
            else{
                QMessageBox::information(0, "Root Folder", "Please select"
                " the root folder of the files you want to edit before "
                "proceeding.");
                data->findObjects(fileDialog->getExistingDirectory());
            }
        }
    }
    displayObjects(buffer);
}

void FileWizardFrontEnd::displayObjects(QString objects)
{
    // display objects on the QTextEdit widget.
    informationWidget->setPlainText(objects);
}
