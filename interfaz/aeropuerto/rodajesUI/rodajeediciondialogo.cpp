#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo)
{
    ui->setupUi(this);

    RodajeParametros rp;
    ui->cbModoEdicion->addItems(rp.tiposRodaje);
}

RodajeEdicionDialogo::~RodajeEdicionDialogo()
{
    delete ui;
}
