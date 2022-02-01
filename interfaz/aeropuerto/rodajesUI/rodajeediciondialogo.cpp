#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo)
{
    ui->setupUi(this);

    RodajeParametros rp;
    ui->cbModoEdicion->addItems(rp.tiposRodaje);

    escena = new QGraphicsScene(this);
    ui->gvRodajeEdicion->setScene(escena);
}

RodajeEdicionDialogo::~RodajeEdicionDialogo()
{
    delete ui;
}

void RodajeEdicionDialogo::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    prepararEscena();
    ui->gvRodajeEdicion->centerOn(0,0);
}

void RodajeEdicionDialogo::prepararEscena()
{
    escena->addRect(QRectF(-100,-100,200,200));
    ui->gvRodajeEdicion->actualizarScRect();
}
