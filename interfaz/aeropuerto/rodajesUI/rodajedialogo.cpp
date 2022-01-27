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
    int n1;
    QString cabeceras;
    foreach(Pista p, listaPistas)
    {
        if(p.orientacion > 89) n1 = 9+(180-p.orientacion)/10;
        else if(p.orientacion >= 0) n1 = (90-p.orientacion)/10;
        QString c1 = QString::number(n1).rightJustified(2,'0');
        QString c2 = QString::number(n1+18).rightJustified(2,'0');
        cabeceras = c1 + " - " + c2;
        ui->cbPista->addItem(cabeceras);
        modelo->setCabecerasActivas(c1, c2);
    }
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
    tablaRodaje->setSelectionBehavior(QAbstractItemView::SelectRows);
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
    int row = tablaRodaje->currentIndex().row();
    modelo->insertRows(row,1,QModelIndex());
}

void RodajeDialogo::slotBotonEliminar()
{
    int row = tablaRodaje->currentIndex().row();
    modelo->removeRows(row,1,QModelIndex());
}
