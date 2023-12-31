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
    commitChangesButton(new QPushButton("&Commit Changes", this)),
    dataField(new QLineEdit(this)),
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

    // actions to rename, move or delete the file(s).
    QActionGroup *editGroup = new QActionGroup(this);
    editGroup->addAction(new QAction(QIcon("icons/remove.png"), "&Rename", this));
    editGroup->addAction(new QAction(QIcon("icons/move.png"), "&Move", this));
    editGroup->addAction(new QAction(QIcon("icons/delete.png"), "&Delete", this));
    editGroup->addAction(new QAction(QIcon("icons/copy.png"), "&Copy", this));

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
        data->findFiles(QFileDialog::getExistingDirectory(0,
                         "Root directory", QDir::currentPath()));
        displayInformation(data->getCurrentFiles());
    }
    // Otherwise, if there's a filter entered in the
    // dataField and objects are found in the root folder, proceed
    // to perform the chosen edit operation.
    else if(dataField->isModified())
    {
        data->findFiles(data->getRootDirectory().path(), dataField->text());
        if(data->isFilesFound())
        {
            QString operation = action->text();
            QString substring;
            data->setOperationMode(operation);

            if(operation == "&Rename")
                substring = "RENAMED";
            else if(operation == "&Delete")
                substring = "DELETED";
            else if(operation == "&Move" || operation == "&Copy")
            {
                if(operation == "&Move")
                    substring = "MOVED";
                else if(operation == "&Copy")
                    substring = "COPIED";
                data->setDestinationDirectory(QFileDialog::getExistingDirectory(
                0, "Destination directory", data->getRootDirectory().absolutePath()));
            }
            displayInformation(QString("File(s) to be %1:\n").arg(substring)+
                           data->getCurrentFiles());
            informationWidget->setReadOnly(false);
            informationWidget->setUndoRedoEnabled(true);
            informationWidget->selectAll();
        }
        else
            QMessageBox::information(0, "Information", "No files were found.");
    }
}

void FileWizardFrontEnd::displayInformation(QString objects)
{
    // display objects on the QTextEdit widget.
    informationWidget->setAlignment(Qt::AlignCenter);
    informationWidget->setPlainText(objects);
}

void FileWizardFrontEnd::commitChanges()
{
    if(data->isFilesFound())
    {
        data->setNewFileNames(informationWidget->toPlainText());
        if(data->performEditOperations())
        {
            QString information;
            information.append("File(s) successfully edited:\n"
            +data->getChangedFiles()+"\n\n");
            if(!data->getFailedFiles().isEmpty())
            {
                information.append(+"File(s) not successfully edited:"
                                    "\n"+data->getFailedFiles());
            }
            displayInformation(information);            
        }
        else
            displayInformation("Edit operation not successful.");
        // reset the data containers for the next operation.
        data->reset();
    }
    else
        QMessageBox::information(0, "Information", "Please select file(s) to"
                                     " edit.");
}
