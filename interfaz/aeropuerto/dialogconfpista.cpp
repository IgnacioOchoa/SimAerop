#include "dialogconfpista.h"
#include "ui_dialogconfpista.h"

#include <QFileDialog>

DialogConfPista::DialogConfPista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfPista),
    escenaPreliminar(new EscenaConfPista)
{
    ui->setupUi(this);
    configurarWidgets();

    vistaPreliminar->setScene(escenaPreliminar);
    escenaPreliminar->setBackgroundBrush(QBrush("#f5f0f3"));

    connect(botonAceptar, &QPushButton::pressed, this, &DialogConfPista::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &DialogConfPista::dialogoCancelado);
    connect(botonCargar, &QPushButton::pressed, this, &DialogConfPista::seleccionarAbrirArchivo);
    connect(botonGuardar, &QPushButton::pressed, this, &DialogConfPista::seleccionarGuardarArchivo);
    connect(botonReset, &QPushButton::pressed, this, &DialogConfPista::resetDialogoPista);

    connect(botonGraficar, &QAbstractButton::pressed, this, &DialogConfPista::botonGraficarApretado);
    connect(botonCentrarVista, &QAbstractButton::pressed, this, [this](){vistaPreliminar->centrarVista();});

    connect(cbUmbral1, QOverload<int>::of(&QCheckBox::stateChanged),
            [this](int state){
        leUmbral1->setEnabled(state);
        lbUmbral1->setEnabled(state);
    });
    connect(cbUmbral2, QOverload<int>::of(&QCheckBox::stateChanged),
            [this](int state){
        leUmbral2->setEnabled(state);
        lbUmbral2->setEnabled(state);
    });
}

DialogConfPista::~DialogConfPista()
{
    delete ui;
}

void DialogConfPista::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonCargar = ui->pbCargar;
    botonGuardar = ui->pbGuardar;
    botonReset = ui->pbReset;
    botonOpAvanzadas = ui->pbOpcionesAvanzadas;
    botonGraficar = ui->pbGraficar;
    botonCentrarVista = ui->pbCentrarVista;

    leLargoPista = ui->leLargo;
    leLargoPista->setValidator(new QIntValidator(0,7000));

    leAnchoPista = ui->leAncho;
    leAnchoPista->setValidator(new QIntValidator(0,1000));

    leNombreArchivo = ui->leNombreArchivo;
    vistaPreliminar = ui->gvPreVisualizacion;
    layoutDial = ui->vlDial;

    leOrientacion = ui->leOrientacion;
    leOrientacion->setValidator(new QIntValidator(0,360));

    layoutDial->setAlignment(leOrientacion,Qt::AlignCenter);
    cbUmbral1 = ui->chkUmbral1;
    cbUmbral2 = ui->chkUmbral2;
    leUmbral1 = ui->leUmbral1;
    leUmbral2 = ui->leUmbral2;
    lbUmbral1 = ui->lbUmbral1;
    lbUmbral2 = ui->lbUmbral2;

    leUmbral1->setEnabled(false);
    leUmbral2->setEnabled(false);
    lbUmbral1->setEnabled(false);
    lbUmbral2->setEnabled(false);
}

void DialogConfPista::poblarDatos()
{
    leLargoPista->setText(QString::number(pista.largo));
    leAnchoPista->setText(QString::number(pista.ancho));
    leOrientacion->setText(QString::number(pista.orientacion));
}

void DialogConfPista::poblarPista()
{
    pista.largo = leLargoPista->text().toInt();
    pista.ancho = leAnchoPista->text().toInt();
    pista.orientacion = leOrientacion->text().toInt();
}

void DialogConfPista::dibujarPista()
{
    escenaPreliminar->clear();
    QPen borde;
    borde.setWidth(2);
    borde.setCosmetic(true);
    QGraphicsRectItem* rectItm = escenaPreliminar->addRect(QRect(-pista.largo/2,-pista.ancho/2,
                                    pista.largo,pista.ancho),borde);
    ajustarContenido();

    QPointF p1 = {rectItm->rect().x(),rectItm->rect().y()+rectItm->rect().height()};
    QPointF p2 = {rectItm->rect().x()+rectItm->rect().width(),
                  rectItm->rect().y()+rectItm->rect().height()};

    QPointF p3 = {rectItm->rect().x(), rectItm->rect().y()};
    QPointF p4 = {rectItm->rect().x() + rectItm->rect().width(),rectItm->rect().y()};

    CotaGrafica* cota1 = new CotaGrafica(p3,p4,"HOR",-100);
    escenaPreliminar->addItem(cota1);

    CotaGrafica* cota2 = new CotaGrafica(p1,p3,"VER",-100);
    escenaPreliminar->addItem(cota2);
}

void DialogConfPista::botonGraficarApretado()
{
    if(datosCompletos())
    {
        poblarPista();
        dibujarPista();
        vistaPreliminar->centerOn(QPointF(0,0));
    }
    else
    {
        QMessageBox::warning(this,"Datos incompletos", "Los datos de pista no están completos");
        return;
    }
}

void DialogConfPista::ajustarContenido()
{
    QRectF r1 = escenaPreliminar->itemsBoundingRect();
    QRectF r2 = vistaPreliminar->mapToScene(vistaPreliminar->viewport()->rect()).boundingRect();

    float cociente1 = r2.x()/r1.x();
    float cociente2 = r2.y()/r1.y();
    float escala = qMin(cociente1,cociente2)*0.9;

    vistaPreliminar->scale(escala,escala);
}

bool DialogConfPista::datosCompletos()
{
    if(leLargoPista->text().isEmpty() ||
       leAnchoPista->text().isEmpty() ||
       leOrientacion->text().isEmpty()) return false;

    int largo = leLargoPista->text().toInt();
    if (largo < 100 || largo > 10000) return false;

    int ancho = leAnchoPista->text().toInt();
    if (ancho < 10 || ancho>500) return false;

    return true;
}

void DialogConfPista::dialogoAceptado()
{
    if (!datosCompletos())
    {
        QMessageBox::warning(this,"Datos incompletos", "Los datos de pista no están completos");
        return;
    }
    poblarPista();
    emit pistaActualizada(pista);
    this->close();
}

void DialogConfPista::dialogoCancelado()
{
    this->close();
}

void DialogConfPista::poblarCabeceras()
{
    /*for (int i=0; i<18; i++)
    {
        cbCabecera1->addItem(QString::number(i).rightJustified(2,'0'));
        cbCabecera2->addItem(QString::number(i+18).rightJustified(2,'0'));
    }

    connect(cbCabecera1, QOverload<int>::of(&QComboBox::currentIndexChanged), cbCabecera2, &QComboBox::setCurrentIndex);
    connect(cbCabecera2, QOverload<int>::of(&QComboBox::currentIndexChanged), cbCabecera1, &QComboBox::setCurrentIndex);
    */
}

void DialogConfPista::seleccionarAbrirArchivo()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Seleccionar archivo",QDir::currentPath(),"(*.json)");

    if(file_name.isEmpty()) return;

    QUrl direccion(file_name);
    QString nombreArchivo = direccion.fileName();
    int lastPoint = nombreArchivo.lastIndexOf(".");
    QString fileNameNoExt = nombreArchivo.left(lastPoint);
    leNombreArchivo->setText(fileNameNoExt);

    PistaParser pistaParser;
    pista = pistaParser.cargarPista(file_name);

    poblarDatos();
}

void DialogConfPista::seleccionarGuardarArchivo()
{
    if (!datosCompletos())
    {
        QMessageBox::warning(this,"Datos incompletos", "Los datos de pista no están completos");
        return;
    }

    poblarPista();
    QString nombrePista;
    if (leNombreArchivo->text().isEmpty())
        nombrePista = "miNuevaPista";
    else
        nombrePista = leNombreArchivo->text();

    QString file_name = QDir::currentPath() + "/" + nombrePista + ".json";
    file_name = QFileDialog::getSaveFileName(this,"Guardar archivo", file_name,"(*.json)");
    if(file_name.isEmpty()) return;

    PistaParser pistaParser;
    pistaParser.guardarPista(file_name,pista);
}

void DialogConfPista::resetDialogoPista()
{
    escenaPreliminar->clear();
    leNombreArchivo->clear();
    leLargoPista->clear();
    leAnchoPista->clear();
}
