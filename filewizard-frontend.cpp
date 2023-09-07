#include "filewizard-frontend.h"
//#include <QFont>
#include <QMenuBar>
#include <QActionGroup>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include <QDebug>

// function definitions of the filewizard-frontend class.

FileWizardFrontEnd::FileWizardFrontEnd(QWidget *parent) :
    QMainWindow(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    omitButton(new QPushButton(this)),
    insertButton(new QPushButton(this)),
    dataField(new QLineEdit(this)),
    fileDialog(new QFileDialog(this, "Root Folder", QDir::currentPath())),
    data(new FileWizardBackEnd()),
    editModeBox(new QMessageBox(this)),
    editOperationsDialog(new QDialog(this)),
    informationWidget(new QTextEdit(this)),
    fileSystemModel(new QFileSystemModel(this)),
    treeView(new QTreeView(this))
{
    // define/declare local objects.
    QLabel *heading, *programInstructions;
    heading = new QLabel(this);
    programInstructions = new QLabel(this);

    // define properties for the main window.
    setWindowTitle("File Wizard");
    setMinimumSize(800, 600);
    setFont(QFont("Helvetica", 10));

    // define properties for the child objects.
    heading->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    heading->setText("DO WHAT YOUR NORMAL\nFILE SYSTEM CANNOT DO.");
    heading->setAlignment(Qt::AlignCenter);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileSystemModel->setRootPath(QDir::currentPath());
    treeView->setModel(fileSystemModel);

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
    QBoxLayout *horizontalLayout4 = new QBoxLayout(QBoxLayout::LeftToRight, this);

    horizontalLayout1->addSpacing(300);
    horizontalLayout1->addWidget(folderButton, Qt::AlignHCenter);
    horizontalLayout1->addSpacing(300);

    horizontalLayout2->addSpacing(300);
    horizontalLayout2->addWidget(dataField, Qt::AlignHCenter);
    horizontalLayout2->addSpacing(300);

    horizontalLayout3->addSpacing(300);
    horizontalLayout3->addWidget(editButton, Qt::AlignHCenter);
    horizontalLayout3->addSpacing(300);

    horizontalLayout4->addWidget(treeView);
    horizontalLayout4->addWidget(informationWidget);

    verticalLayout->addWidget(heading);
    verticalLayout->addWidget(programInstructions);
    verticalLayout->addLayout(horizontalLayout1);
    verticalLayout->addLayout(horizontalLayout2);
    verticalLayout->addLayout(horizontalLayout3);
    verticalLayout->addLayout(horizontalLayout4);

    centralWidget->setLayout(verticalLayout);
    setCentralWidget(centralWidget);

    connect(folderButton, SIGNAL(clicked()), this, SLOT(handleAction()));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
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

    // Under the condition that there's a filter entered in the
    // dataField and objects are found in the root folder, proceed
    // to perform the chosen edit operation.

    else if(dataField->isModified())
    {
        data->findObjects(data->getRootDirectory().path(), dataField->text());
        displayObjects(data->getObjects());

        if(data->isObjectsFound())
        {
            if(action->text() == "&Rename")
            {
                editModeBox->setText("Do you intend to omit"
                                    " or insert a substring from the filenames?");
                omitButton = editModeBox->addButton(tr("Omit"), QMessageBox::ActionRole);
                insertButton = editModeBox->addButton(tr("Insert"), QMessageBox::ActionRole);
                editModeBox->exec();
                // TODO: Add a textcursor in the information widget.
                if(omitButton == editModeBox->clickedButton())
                {
                    informationWidget->setReadOnly(false);
                    informationWidget->setTextCursor();
                }

                else if(insertButton == editModeBox->clickedButton())
                {

                }

                //foreach(QString filename, data->getObjects().split("\n"))
                //{
                //    QFileInfo info(data->getDirectory().absolutePath()
                //                   + "/" + filename);

                //}
            }
            else if(action->text() == "&Move")
            {
                qDebug("Executing move block.");
            }
            else if(action->text() == "&Delete")
            {
            }
            else if(action->text() == "&Copy")
            {
            }
        }
    }

    else
        editModeBox->information(this, "Missing Filter", "Please enter a keyword"
            " in step 2 to filter the objects you intend to modify.");
}

void FileWizardFrontEnd::displayObjects(QString objects)
{
    // display objects on the QTextEdit widget.
    informationWidget->setPlainText(objects);
}
