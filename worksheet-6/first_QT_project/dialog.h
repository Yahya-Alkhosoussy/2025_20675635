#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ModelPart.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    void loadFromPart(ModelPart* part);
    void saveToPart(ModelPart* part);

    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
