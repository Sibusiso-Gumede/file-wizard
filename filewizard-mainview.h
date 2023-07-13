#ifndef FILEWIZARDMAINVIEW_H
#define FILEWIZARDMAINVIEW_H

#include <QDialog>
#include <QAction>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>

class FileWizardMainView : public QDialog {
    Q_OBJECT
public:
    FileWizardMainView(QWidget* parent = nullptr);
private slots:
    void handleAction(QAction *a);
    void popFileDialog();
private:
    QPushButton* folderButton, editButton;
    QTextEdit* informationWidget;
};
#endif // FILEWIZARDMAINVIEW_H
