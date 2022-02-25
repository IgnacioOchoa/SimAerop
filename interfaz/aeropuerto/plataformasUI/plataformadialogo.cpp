#include "plataformadialogo.h"
#include "ui_plataformadialogo.h"

PlataformaDialogo::PlataformaDialogo(QList<Pista>& lp, QList<Plataforma> &la, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlataformaDialogo),
    listaPlat(la)
    //modelo(new ModeloPlataformas(la, this)),
    //modeloProxy(new ModeloProxyPlataformas(modelo,this))

{
    ui->setupUi(this);
    escena = new PlataformaEscena(ui->gvPlataforma, lp, this);

    configurarWidgets();
    connect(botonAceptar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoCancelado);
    connect(botonAgregarPlat, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonAgregarPlat);
    connect(botonEliminarPlat, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonEliminarPlat);
    connect(botonAgregarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonAgregarVert);
    connect(botonEliminarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonEliminarVert);
}

PlataformaDialogo::~PlataformaDialogo()
{
    delete ui;
}

void PlataformaDialogo::showEvent(QShowEvent *event)
{
    modelo = new ModeloPlataformas(listaPlat, this);
    modeloProxy = new ModeloProxyPlataformas(modelo,this);
    listaNombres->setModel(modelo);
    tablaVertices->setModel(modeloProxy);
    modelo->sincListas();
    escena->limpiarEscena();
    QItemSelectionModel* selectionModel = listaNombres->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, modeloProxy,
            &ModeloProxyPlataformas::slotPlatCambiada);
    QWidget::showEvent(event);
    escena->graficar();
}

void PlataformaDialogo::configurarWidgets()
{
    vista = ui->gvPlataforma;
    vista->configEscena(escena);

    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonAgregarPlat = ui->pbAgregarPlat;
    botonEliminarPlat = ui->pbEliminarPlat;
    botonAgregarVert = ui->pbAgregarVert;
    botonEliminarVert = ui->pbEliminarVert;

    listaNombres = ui->lvNombres;
    listaNombres->setSelectionBehavior(QAbstractItemView::SelectRows);
    listaNombres->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaNombres->viewport()->installEventFilter(this);

    tablaVertices = ui->tvVertices;
    tablaVertices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int anchoMin = tablaVertices->horizontalHeader()->length();
    tablaVertices->verticalHeader()->hide();
    tablaVertices->setMinimumWidth(anchoMin*2);
    tablaVertices->setMinimumHeight(300);
    tablaVertices->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablaVertices->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablaVertices->viewport()->installEventFilter(this);
}

void PlataformaDialogo::slotBotonAgregarPlat()
{
    int row = listaNombres->currentIndex().row();
    modelo->insertRows(row,1,QModelIndex());
}

void PlataformaDialogo::slotBotonEliminarPlat()
{
    int row = listaNombres->currentIndex().row();
    modelo->removeRows(row,1,QModelIndex());
}

void PlataformaDialogo::slotBotonAgregarVert()
{

}

void PlataformaDialogo::slotBotonEliminarVert()
{

}

void PlataformaDialogo::dialogoAceptado()
{
    modelo->guardarLista();
    this->close();
}

void PlataformaDialogo::dialogoCancelado()
{
    this->close();
}
