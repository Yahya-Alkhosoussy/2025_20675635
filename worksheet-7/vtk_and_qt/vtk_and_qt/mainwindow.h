#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkNew.h>
#include "ModelPartList.h"
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
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
};
#endif // MAINWINDOW_H
