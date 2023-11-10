#include "filewizard-frontend.h"
#include <QMenuBar>
#include <QActionGroup>
#include <QBoxLayout>
#include <QDebug>
#include <QMessageBox>

// function definitions of the filewizard-frontend class.

FileWizardFrontEnd::FileWizardFrontEnd(QWidget *parent) :
    QMainWindow(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    commitChangesButton(new QPushButton("&Save Changes", this)),
    dataField(new QLineEdit(this)),
    fileDialog(new QFileDialog(this, "Root Folder", QDir::currentPath())),
    data(new FileWizardBackEnd()),
    editOperationsDialog(new QDialog(this)),
    informationWidget(new QTextEdit(this)),
    heading(new QLabel(this)),
    programInstructions(new QLabel(this))
{
    // define properties for the main window.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 600);
    setFont(QFont("Helvetica", 10));

    // define properties for the child objects.
    heading->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    heading->setText("DO WHAT YOUR NORMAL\nFILE SYSTEM CANNOT DO.");
    heading->setAlignment(Qt::AlignCenter);
    fileDialog->setFileMode(QFileDialog::Directory);

    // the sizes of the widgets
    folderButton->setMaximumSize(100, 30);
    dataField->setMaximumSize(300, 30);
    dataField->setPlaceholderText("*.zip or recipes*.* or *.mp4");
    editButton->setMaximumSize(100, 30);
    commitChangesButton->setMaximumSize(100, 30);

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
    verticalLayout->addWidget(commitChangesButton, Qt::AlignHCenter);

    centralWidget->setLayout(verticalLayout);
    setCentralWidget(centralWidget);

    connect(folderButton, SIGNAL(clicked()), this, SLOT(handleAction()));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
    connect(commitChangesButton, SIGNAL(clicked()), this, SLOT(commitChanges()));
}

FileWizardFrontEnd::~FileWizardFrontEnd()
{
    delete data;
}

void FileWizardFrontEnd::handleAction(QAction* action)
{
    // When the folderButton is clicked, proceed to display
    // a file dialog and a list of objects found in the chosen
    // directory.
    if(action == nullptr)
    {
        data->findObjects(fileDialog->getExistingDirectory());
        displayObjects(data->getObjects());
    }
    // Otherwise, if there's a filter entered in the
    // dataField and objects are found in the root folder, proceed
    // to perform the chosen edit operation.
    else if(dataField->isModified())
    {
        data->findObjects(data->getRootDirectory().path(), dataField->text());
        if(data->isObjectsFound())
        {
            QString operation = action->text(), substring;
            data->setOperationMode(operation);

            if(operation == "&Rename")
                substring = "RENAMED";
            else if(operation == "&Move")
                substring = "MOVED";
            else if(operation == "&Delete")
                substring = "DELETED";
            else if(operation == "&Copy")
                substring = "COPIED";

            displayObjects(QString("Object(s) to be %1:\n").arg(substring)+
                           data->getObjects());
            informationWidget->setReadOnly(false);
            informationWidget->setUndoRedoEnabled(true);
            informationWidget->selectAll();
        }
        else
            QMessageBox::information(0, "Information", "No files were found.");
    }
    // Or just proceed to display an error message.
    else
        QMessageBox::information(0, "Missing Filter", "Please enter a keyword"
            " in step 2 to filter the objects you intend to modify.");
}

void FileWizardFrontEnd::displayObjects(QString objects)
{
    // display objects on the QTextEdit widget.
    informationWidget->setAlignment(Qt::AlignCenter);
    informationWidget->setPlainText(objects);
}

void FileWizardFrontEnd::commitChanges()
{
    // Perform changes to the objects.

}
