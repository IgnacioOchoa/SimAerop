#include "plataformadialogo.h"
#include "ui_plataformadialogo.h"

PlataformaDialogo::PlataformaDialogo(QList<Plataforma> &la, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlataformaDialogo),
    modelo1(new ModeloNombresPlataformas(la, this))
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoCancelado);
    connect(botonAgregarPlat, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonAgregarPlat);
    connect(botonEliminarPlat, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonEliminarPlat);
    connect(botonAgregarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonAgregarVert);
    connect(botonEliminarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonEliminarVert);

    QItemSelectionModel* selectionModel = ui->lvNombres->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, modelo1, &ModeloNombresPlataformas::sloSeleccionCambiada);
}

PlataformaDialogo::~PlataformaDialogo()
{
    delete ui;
}

void PlataformaDialogo::showEvent(QShowEvent *event)
{
    modelo1->sincListas();
    QWidget::showEvent(event);
}

void PlataformaDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonAgregarPlat = ui->pbAgregarPlat;
    botonEliminarPlat = ui->pbEliminarPlat;
    botonAgregarVert = ui->pbAgregarVert;
    botonEliminarVert = ui->pbEliminarVert;
    listaNombres = ui->lvNombres;
    tablaVertices = ui->tvVertices;
    listaNombres->setModel(modelo1);
    tablaVertices->setModel(modelo1);
    tablaVertices->setItemDelegate(new ModeloPlataformasDelegate);
    listaNombres->setSelectionBehavior(QAbstractItemView::SelectRows);
    listaNombres->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaNombres->viewport()->installEventFilter(this);
}

//void PlataformaDialogo::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
//{
//    Q_UNUSED(deselected)

//    qDebug() << "Selección";

//}

void PlataformaDialogo::slotBotonAgregarPlat()
{
    int row = listaNombres->currentIndex().row();
    modelo1->insertRows(row,1,QModelIndex());
}

void PlataformaDialogo::slotBotonEliminarPlat()
{
    int row = listaNombres->currentIndex().row();
    modelo1->removeRows(row,1,QModelIndex());
}

void PlataformaDialogo::slotBotonAgregarVert()
{

}

void PlataformaDialogo::slotBotonEliminarVert()
{

}

void PlataformaDialogo::dialogoAceptado()
{
    modelo1->guardarLista();
    this->close();
}

void PlataformaDialogo::dialogoCancelado()
{
    this->close();
}
