#include "filewizard-frontend.h"
#include <QFont>
#include <QMenu>
#include <QMenuBar>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QLabel>

// member function definitions of the filewizard-frontend class.

FileWizardFrontEnd::FileWizardFrontEnd(QWidget* parent) : QDialog(parent),
    folderButton(new QPushButton("&Open Folder", this)),
    editButton(new QPushButton("&Edit", this)),
    dataField(new QLineEdit(this)),
    informationWidget(new QTextEdit(this))
{
    // define/declare local objects.
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

    // action menu.
    QMenu* editMenu = new QMenu(this);
    editMenu->addActions(editGroup->actions());
    editButton->setMenu(editMenu);

    // organize the widgets of the main dialog in a vertical structure.
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(heading);
    verticalLayout->addWidget(stepOne);
    verticalLayout->addWidget(folderButton);
    verticalLayout->addWidget(stepTwo);
    verticalLayout->addWidget(dataField);
    verticalLayout->addWidget(editButton);
    verticalLayout->addWidget(informationWidget);
    setLayout(verticalLayout);

    connect(folderButton, SIGNAL(clicked()), this, SLOT(process()));
    connect(editGroup, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)));
}

void FileWizardFrontEnd::handleAction(QAction* a)
{

}

QString FileWizardFrontEnd::process()
{
    // show the file dialog,
    // find the objects in the selected directory
    // and display them.
    displayObjects(QFileDialog::getExistingDirectory
                   (0, "Select Root Folder", QDir::currentPath()));
}

QString FileWizardFrontEnd::displayObjects(QString l)
{
    // display objects on the QTextEdit widget.

}
