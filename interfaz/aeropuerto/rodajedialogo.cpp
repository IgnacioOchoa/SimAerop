#include "rodajedialogo.h"
#include "ui_rodajedialogo.h"

RodajeDialogo::RodajeDialogo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeDialogo)
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &RodajeDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &RodajeDialogo::dialogoCancelado);
}

RodajeDialogo::~RodajeDialogo()
{
    delete ui;
}

void RodajeDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
}

void RodajeDialogo::dialogoAceptado()
{
    this->close();
}

void RodajeDialogo::dialogoCancelado()
{
    this->close();
}
