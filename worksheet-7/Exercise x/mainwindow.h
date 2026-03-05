#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "modelPartList.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public slots:
        void handleButton();
        void handleButton2();
        void handleTreeClicked();
        void on_actionOpen_file_triggered();
        void on_actionItem_Options_triggered();
        void populateTree();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
signals:
    void statusUpdateMessage(const QString& message, int timeout);

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;
};
#endif // MAINWINDOW_H
