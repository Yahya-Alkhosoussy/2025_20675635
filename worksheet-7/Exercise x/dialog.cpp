#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::loadFromPart(ModelPart* part) {
    ui->nameEdit->setPlainText(part->data(0).toString());
    ui->redSpinBox->setValue(part->getColourR());
    ui->greenSpinBox->setValue(part->getColourG());
    ui->blueSpinBox->setValue(part->getColourB());
    ui->visibleCheckBox->setChecked(part->visible());
}

void Dialog::saveToPart(ModelPart* part) {
    part->set(0, ui->nameEdit->toPlainText());
    part->setColour(
        ui->redSpinBox->value(),
        ui->greenSpinBox->value(),
        ui->blueSpinBox->value()
    );
    part->setVisibleRecursive(ui->visibleCheckBox->isChecked());
}
