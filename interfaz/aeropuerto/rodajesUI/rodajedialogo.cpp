#include "rodajedialogo.h"
#include "ui_rodajedialogo.h"

RodajeDialogo::RodajeDialogo(QList<Rodaje> &lr, const QList<Pista> &lp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeDialogo),
    listaRodajes(lr),
    listaPistas(lp),
    modelo(new ModeloRodajes(lr, this))
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &RodajeDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &RodajeDialogo::dialogoCancelado);
    connect(botonAgregar, &QPushButton::pressed, this, &RodajeDialogo::slotBotonAgregar);
    connect(botonEliminar, &QPushButton::pressed, this, &RodajeDialogo::slotBotonEliminar);

}

RodajeDialogo::~RodajeDialogo()
{
    delete ui;
}

void RodajeDialogo::showEvent(QShowEvent *event)
{
    modelo->sincListas();
    QWidget::showEvent(event);
}

void RodajeDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonAgregar = ui->pbAgregar;
    botonEliminar = ui->pbEliminar;
    tablaRodaje = ui->twCallesRodaje;
    tablaRodaje->setModel(modelo);
    tablaRodaje->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int anchoMin = tablaRodaje->horizontalHeader()->length();
    tablaRodaje->verticalHeader()->hide();
    tablaRodaje->setMinimumWidth(anchoMin*2);
}

void RodajeDialogo::dialogoAceptado()
{

    this->close();
}

void RodajeDialogo::dialogoCancelado()
{
    this->close();
}

void RodajeDialogo::slotBotonAgregar()
{

}

void RodajeDialogo::slotBotonEliminar()
{

}
