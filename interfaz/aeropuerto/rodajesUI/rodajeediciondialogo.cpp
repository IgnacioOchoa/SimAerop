#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo),
    escena(new RodajeEdicionEscena(this))
{
    ui->setupUi(this);

    RodajeParametros rp;
    ui->cbModoEdicion->addItems(rp.tiposRodaje);
    ui->gvRodajeEdicion->configEscena(escena);
    escena->graficar();
    connect(ui->pbGrid, &QAbstractButton::pressed, escena, &RodajeEdicionEscena::actualizarGrid);
}

RodajeEdicionDialogo::~RodajeEdicionDialogo()
{
    delete ui;
}

void RodajeEdicionDialogo::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    ui->gvRodajeEdicion->actualizarVista();
}
