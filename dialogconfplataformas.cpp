#include "dialogconfplataformas.h"
#include "ui_dialogconfplataformas.h"

DialogConfPlataformas::DialogConfPlataformas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfPlataformas)
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &DialogConfPlataformas::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &DialogConfPlataformas::dialogoCancelado);
}

void DialogConfPlataformas::dialogoAceptado()
{
    this->close();
}

void DialogConfPlataformas::dialogoCancelado()
{
    this->close();
}

DialogConfPlataformas::~DialogConfPlataformas()
{
    delete ui;
}

void DialogConfPlataformas::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
}
