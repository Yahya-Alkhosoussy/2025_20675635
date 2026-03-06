#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeView>
#include <QPushButton>
#include <QStatusBar>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    this->partList = new ModelPartList("PartsList");

    populateTree();
    
    /* Link it to the tree view in the GUI */
    ui->treeView->setModel(this->partList);
    ui->treeView->addAction(ui->actionItem_Options);
    
    /* Link a render window with the Qt widget */
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    /* Add a renderer */
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    /* Create cylinder */
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1., 0., 0.35);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);

    /* Reset camera */
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
}

void MainWindow::populateTree(){
    
    /* Manually create a model tree */
    ModelPart* rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart* childItem = new ModelPart({name, visible});

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({name, visible});

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }
}

void MainWindow::on_actionItem_Options_triggered() {
    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    if (selectedPart != nullptr) {
        Dialog dialog(this);
        dialog.loadFromPart(selectedPart);

        if (dialog.exec() == QDialog::Accepted) {
            dialog.saveToPart(selectedPart);
            emit statusUpdateMessage(QString("Item updated"), 0);
            ui->treeView->viewport()->update();
        }
    } else {
        emit statusUpdateMessage(QString("No item selected"), 0);
    }
}

void MainWindow::handleButton() {
    emit statusUpdateMessage(QString("A Button was clicked!"), 0);
}

void MainWindow::handleButton2() {
    Dialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted"), 0);
    } else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }
}

void MainWindow::handleTreeClicked() {
    /* Get the index of the selected item */
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index */
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    /* Retrieve the name string from the internal QVariant data array */
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
}


void MainWindow::on_actionOpen_file_triggered(){
    emit statusUpdateMessage(QString("Open File triggered"), 0);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("STL files (*.stl);;Text files (*.txt)"));
    
    if (!fileName.isEmpty()) {
        QModelIndex index = ui->treeView->currentIndex();
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
        if (selectedPart != nullptr) {
            QFileInfo fileInfo(fileName);
            QString justFileName = fileInfo.fileName();
            selectedPart->set(0, justFileName);
            emit statusUpdateMessage(QString("Opened: ") + justFileName, 0);

            /* Refresh the treeview to show the updated name */
            ui->treeView->viewport()->update();
        } else {
            emit statusUpdateMessage(QString("No item selected in tree"), 0);
        }
    }
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

