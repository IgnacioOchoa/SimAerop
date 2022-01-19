#include "rodajedialogo.h"
#include "ui_rodajedialogo.h"

RodajeDialogo::RodajeDialogo(QList<Rodaje> &lr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeDialogo),
    listaRodajes(lr)
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &RodajeDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &RodajeDialogo::dialogoCancelado);
    connect(botonAgregar, &QPushButton::pressed, this, &RodajeDialogo::slotBotonAgregar);
    connect(botonEliminar, &QPushButton::pressed, this, &RodajeDialogo::slotBotonEliminar);

    poblarTabla();
}

RodajeDialogo::~RodajeDialogo()
{
    delete ui;
}

void RodajeDialogo::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    poblarTabla();
}

void RodajeDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonAgregar = ui->pbAgregar;
    botonEliminar = ui->pbEliminar;
    tablaRodaje = ui->twCallesRodaje;

    tablaRodaje->setColumnCount(6);
    tablaRodaje->setHorizontalHeaderLabels({"Cabecera","Posición","Ángulo","Ancho","Largo","Radio"});
    tablaRodaje->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i=0; i<6; i++) {
        tablaRodaje->setColumnWidth(i,150);
    }

    int anchoMin = tablaRodaje->horizontalHeader()->length();
    tablaRodaje->verticalHeader()->hide();
    tablaRodaje->setMinimumWidth(anchoMin);
    tablaRodaje->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void RodajeDialogo::poblarTabla()
{
    tablaRodaje->setRowCount(listaRodajes.size());
    for (int i=0; i < listaRodajes.size(); i++)
    {
        tablaRodaje->setItem(i,0, new QTableWidgetItem("Cabecera 1"));
        tablaRodaje->setItem(i,1, new QTableWidgetItem(QString::number(listaRodajes[i].posicion)));
        tablaRodaje->setItem(i,2, new QTableWidgetItem(QString::number(listaRodajes[i].angulo)));
        tablaRodaje->setItem(i,3, new QTableWidgetItem(QString::number(listaRodajes[i].ancho)));
        tablaRodaje->setItem(i,4, new QTableWidgetItem(QString::number(listaRodajes[i].largo)));
        tablaRodaje->setItem(i,5, new QTableWidgetItem(QString::number(listaRodajes[i].radio)));
    }

    tablaRodaje->setItemDelegateForColumn(0, new RodajeCabeceraDelegate);
    tablaRodaje->setEditTriggers(QAbstractItemView::DoubleClicked
                                 | QAbstractItemView::CurrentChanged);

}

void RodajeDialogo::dialogoAceptado()
{
    //Vaciar listaRodajes para que al hacer el append no se repitan rodajes
    listaRodajes.clear();

    //Llenar lista de rodajes
    for (int i=0; i<tablaRodaje->rowCount(); i++)
    {
        Rodaje rod {
            tablaRodaje->item(i,0)->data(Qt::DisplayRole).toString(),
            tablaRodaje->item(i,1)->data(Qt::DisplayRole).toFloat(),
            tablaRodaje->item(i,2)->data(Qt::DisplayRole).toFloat(),
            tablaRodaje->item(i,3)->data(Qt::DisplayRole).toInt(),
            tablaRodaje->item(i,4)->data(Qt::DisplayRole).toInt(),
            tablaRodaje->item(i,5)->data(Qt::DisplayRole).toInt()
        };
        listaRodajes.append(rod);
    }

    foreach(Rodaje r, listaRodajes)
    {
        qInfo() << r;
    }

    this->close();
}

void RodajeDialogo::dialogoCancelado()
{
    this->close();
}

void RodajeDialogo::slotBotonAgregar()
{
    tablaRodaje->insertRow(tablaRodaje->rowCount());
}

void RodajeDialogo::slotBotonEliminar()
{
    tablaRodaje->removeRow(tablaRodaje->currentRow());
}
