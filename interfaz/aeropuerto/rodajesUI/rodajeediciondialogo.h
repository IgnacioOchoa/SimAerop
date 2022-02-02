#ifndef RODAJEEDICIONDIALOGO_H
#define RODAJEEDICIONDIALOGO_H

#include <QDialog>
#include "rodajeedicionescena.h"
#include "rodajeedicionvista.h"
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
    virtual void showEvent(QShowEvent *event) override;

private:
    void prepararEscena();
    Ui::RodajeEdicionDialogo *ui;
    RodajeEdicionEscena* escena;
};

#endif // RODAJEEDICIONDIALOGO_H