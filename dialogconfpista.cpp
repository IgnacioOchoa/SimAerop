#include "dialogconfpista.h"
#include "ui_dialogconfpista.h"

#include <QFileDialog>

DialogConfPista::DialogConfPista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfPista),
    escenaPreliminar(new QGraphicsScene)
{
    ui->setupUi(this);
    configurarWidgets();
    //poblarCabeceras();

    connect(botonAceptar, &QPushButton::pressed, this, &DialogConfPista::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &DialogConfPista::dialogoCancelado);
    connect(botonCargar, &QPushButton::pressed, this, &DialogConfPista::seleccionarAbrirArchivo);

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
    botonOpAvanzadas = ui->pbOpcionesAvanzadas;
    leLargoPista = ui->leLargo;
    leAnchoPista = ui->leAncho;
    leNombreArchivo = ui->leNombreArchivo;
    leRutaArchivo = ui->leRutaArchivo;
    vistaPreliminar = ui->gvPreVisualizacion;
    layoutDial = ui->vlDial;
    leOrientacion = ui->leOrientacion;
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

void DialogConfPista::dialogoAceptado()
{
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
    QUrl direccion(file_name);
    QString nombreArchivo = direccion.fileName();
    int lastPoint = nombreArchivo.lastIndexOf(".");
    QString fileNameNoExt = nombreArchivo.left(lastPoint);
    leNombreArchivo->setText(fileNameNoExt);
    leRutaArchivo->setText(direccion.adjusted(QUrl::RemoveFilename).url());
    leRutaArchivo->setCursorPosition(0);

    PistaParser pistaParser;
    pista = pistaParser.cargarPista(file_name);

    poblarDatos();
}
