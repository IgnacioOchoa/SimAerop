#ifndef RODAJEEDICIONDIALOGO_H
#define RODAJEEDICIONDIALOGO_H

#include <QDialog>
#include "../../../estructuras-datos/elementosaerop.h"

namespace Ui {
class RodajeEdicionDialogo;
}

class RodajeEdicionDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit RodajeEdicionDialogo(QWidget *parent = nullptr);
    ~RodajeEdicionDialogo();

private:
    Ui::RodajeEdicionDialogo *ui;
};

#endif // RODAJEEDICIONDIALOGO_H
