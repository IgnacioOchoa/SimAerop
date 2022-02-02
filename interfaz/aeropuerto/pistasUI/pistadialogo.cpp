#include "pistadialogo.h"
#include "ui_pistadialogo.h"

#include <QFileDialog>

PistaDialogo::PistaDialogo(QList<Pista>& listaP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PistaDialogo),
    listaPistas(listaP)
{
    ui->setupUi(this);
    configurarWidgets();
    conectarSlots();
}

PistaDialogo::~PistaDialogo()
{
    delete ui;
}

void PistaDialogo::showEvent(QShowEvent *event)
{
    poblarDatos();
    QWidget::showEvent(event);
}

void PistaDialogo::poblarDatos()
{
    if(pista == pistaDefault) {
        if(!listaPistas.isEmpty()) {
            pista = listaPistas.last();
        }
    }
    leLargoPista->setText(pista.largo == 0 ? "" : QString::number(pista.largo));
    leAnchoPista->setText(pista.ancho == 0 ? "" : QString::number(pista.ancho));
    //leOrientacion->setText(pista.orientacion == 0 ? "" : QString::number(pista.orientacion));
}

void PistaDialogo::poblarPista()
{
    pista.largo = leLargoPista->text().toInt();
    pista.ancho = leAnchoPista->text().toInt();
    int angulo = 90 - (dialPista->value()%18)*10;
    if (angulo < 0) angulo += 180;
    pista.orientacion = angulo;
    pista.cabecera1 = cabecera1;
    pista.cabecera2 = cabecera2;
}

void PistaDialogo::dibujarPista()
{
    vistaPreliminar->graficarPista(pista);
    maxUmbral1 = maxUmbral2 = pista.largo;
}

void PistaDialogo::botonGraficarApretado()
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

void PistaDialogo::actualizarUmbrales(const QString& s1, const QString& s2)
{
    cabecera1 = s1;
    cabecera2 = s2;
    cbUmbral1->setText("Umbral Cabecera " + s1);
    cbUmbral2->setText("Umbral Cabecera " + s2);
}

void PistaDialogo::actualizarLEOrientacion(int value)
{
    QString s1 = QString::number(value%18).rightJustified(2,'0');
    QString s2 = QString::number(value%18+18).rightJustified(2,'0');
    if (s1=="00")
    {
        s1 = s2;
        s2 = "36";
    }
    leOrientacion->setText(s1 + " - " + s2);
    actualizarUmbrales(s1,s2);
}

void PistaDialogo::leUmbralModificado()
{
    int valor = static_cast<QLineEdit*>(sender())->text().toInt();
    int nroUmbral = sender()->property("NroUmbral").toInt();
    switch (nroUmbral) {
    case 1:
        if(!verificarUmbrales(PistaEscena::Umbral::UMBRAL1, valor))
        {
            static_cast<QLineEdit*>(sender())->setText(QString::number(valor));
        }
        desplUmbral1 = valor;
        emit sigUmbralActualizado(PistaEscena::Umbral::UMBRAL1, valor);
        break;
    case 2:
        if(!verificarUmbrales(PistaEscena::Umbral::UMBRAL2, valor))
        {
            static_cast<QLineEdit*>(sender())->setText(QString::number(valor));
        }
        desplUmbral2 = valor;
        emit sigUmbralActualizado(PistaEscena::Umbral::UMBRAL2, valor);
        break;
    }
    actualizarMaxUmbrales();
}

void PistaDialogo::slotLineaUmbralMovida(PistaEscena::Umbral um, int valor)
{
    if(um == PistaEscena::Umbral::UMBRAL1)
    {
        if(cbUmbral1->isChecked()) leUmbral1->setText(QString::number(valor));
        desplUmbral1 = valor;
    }
    else if(um == PistaEscena::Umbral::UMBRAL2)
    {
        if(cbUmbral2->isChecked()) leUmbral2->setText(QString::number(valor));
        desplUmbral2 = valor;
    }
    actualizarMaxUmbrales();
}

bool PistaDialogo::verificarUmbrales(PistaEscena::Umbral umbral, int &desplazamiento)
{
    switch(umbral) {
    case PistaEscena::Umbral::UMBRAL1:
        {
            if (desplazamiento > maxUmbral1-margenMinUmbral) {desplazamiento = maxUmbral1-margenMinUmbral; return false;}
            else if (desplazamiento < 0) {desplazamiento = 0; return false;}
            return true;
        }
    case PistaEscena::Umbral::UMBRAL2:
        {
            if (desplazamiento > maxUmbral2-margenMinUmbral) {desplazamiento = maxUmbral2-margenMinUmbral; return false;}
            else if (desplazamiento < 0) {desplazamiento = 0; return false;}
            return true;
        }
    }
    return true;
}

void PistaDialogo::actualizarMaxUmbrales()
{
    maxUmbral1 = pista.largo - desplUmbral2 - margenMinUmbral;
    maxUmbral2 = pista.largo - desplUmbral1 - margenMinUmbral;
    emit sigUmbralMaxActualizado(maxUmbral1,maxUmbral2);
}

bool PistaDialogo::datosCompletos()
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

void PistaDialogo::dialogoAceptado()
{
    if (!datosCompletos())
    {
        QMessageBox::warning(this,"Datos incompletos", "Los datos de pista no están completos");
        return;
    }
    poblarPista();
    listaPistas.append(pista);
    emit sigPistaActualizada();
    this->close();
}

void PistaDialogo::dialogoCancelado()
{
    this->close();
}

void PistaDialogo::seleccionarAbrirArchivo()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Seleccionar archivo",QDir::currentPath(),"(*.json)");

    if(file_name.isEmpty()) return;

    QUrl direccion(file_name);
    QString nombreArchivo = direccion.fileName();
    int lastPoint = nombreArchivo.lastIndexOf(".");
    QString fileNameNoExt = nombreArchivo.left(lastPoint);
    leNombreArchivo->setText(fileNameNoExt);

    PistaParser pistaParser;
    pista = pistaParser.cargarPista(file_name)[0];
    poblarDatos();
}

void PistaDialogo::seleccionarGuardarArchivo()
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
    pistaParser.guardarPista(file_name, listaPistas);
}

void PistaDialogo::resetDialogoPista()
{
    vistaPreliminar->borrar();
    leNombreArchivo->clear();
    leLargoPista->clear();
    leAnchoPista->clear();
    leUmbral1->setText("0");
    leUmbral2->setText("0");
}

void PistaDialogo::configurarWidgets()
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
    leAnchoPista->setValidator(new QIntValidator(0,100));

    dialPista = ui->dialPista;

    leNombreArchivo = ui->leNombreArchivo;
    vistaPreliminar = ui->gvPreVisualizacion;
    layoutDial = ui->vlDial;

    leOrientacion = ui->leOrientacion;
    leOrientacion->setReadOnly(true);

    layoutDial->setAlignment(leOrientacion,Qt::AlignCenter);
    cbUmbral1 = ui->chkUmbral1;
    cbUmbral2 = ui->chkUmbral2;
    leUmbral1 = ui->leUmbral1;
    QIntValidator* intVal1 = new QIntValidator(this);
    leUmbral1->setValidator(intVal1);
    leUmbral1->setProperty("NroUmbral", 1);
    leUmbral2 = ui->leUmbral2;
    QIntValidator* intVal2 = new QIntValidator(this);
    leUmbral2->setValidator(intVal2);
    leUmbral2->setProperty("NroUmbral", 2);
    lbUmbral1 = ui->lbUmbral1;
    lbUmbral2 = ui->lbUmbral2;

    leUmbral1->setEnabled(false);
    leUmbral2->setEnabled(false);
    lbUmbral1->setEnabled(false);
    lbUmbral2->setEnabled(false);
}

void PistaDialogo::conectarSlots()
{
    // conexión de los botones
    connect(botonAceptar, &QPushButton::pressed, this, &PistaDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &PistaDialogo::dialogoCancelado);
    connect(botonCargar, &QPushButton::pressed, this, &PistaDialogo::seleccionarAbrirArchivo);
    connect(botonGuardar, &QPushButton::pressed, this, &PistaDialogo::seleccionarGuardarArchivo);
    connect(botonReset, &QPushButton::pressed, this, &PistaDialogo::resetDialogoPista);
    connect(botonGraficar, &QAbstractButton::pressed, this, &PistaDialogo::botonGraficarApretado);
    connect(botonCentrarVista, &QAbstractButton::pressed, this, [this](){vistaPreliminar->centrarVista();});

    //activa o desactiva el LineEdit en funcion si el checkBox esta checkeado o no
    connect(cbUmbral1, QOverload<int>::of(&QCheckBox::stateChanged),
            [this](int state){
        leUmbral1->setEnabled(state);
        lbUmbral1->setEnabled(state);
        state ? leUmbral1->setText(QString::number(desplUmbral1)) : leUmbral1->setText("");
    });

    //Le envía una señal a la escena para que muestre o esconda la línea de umbral
    connect(cbUmbral1, QOverload<int>::of(&QCheckBox::stateChanged),
            [this](int state){
            static_cast<PistaEscena*>(vistaPreliminar->scene())->slotUmbralActivado(PistaEscena::Umbral::UMBRAL1,state);}
    );

    //Guarda el valor ingresado en el LineEdit
    connect(leUmbral1, &QLineEdit::editingFinished, this, &PistaDialogo::leUmbralModificado);
    connect(leUmbral2, &QLineEdit::editingFinished, this, &PistaDialogo::leUmbralModificado);

    //activa o desactiva el LineEdit en funcion si el checkBox esta checkeado o no
    connect(cbUmbral2, QOverload<int>::of(&QCheckBox::stateChanged),
            [this](int state){
        leUmbral2->setEnabled(state);
        lbUmbral2->setEnabled(state);
        state ? leUmbral2->setText(QString::number(desplUmbral2)) : leUmbral2->setText("");
    });

    //Le envía una señal a la escena para que muestre o esconda la línea de umbral
    connect(cbUmbral2, QOverload<int>::of(&QCheckBox::stateChanged),
            [this](int state){
            static_cast<PistaEscena*>(vistaPreliminar->scene())->slotUmbralActivado(PistaEscena::Umbral::UMBRAL2,state);}
    );

    connect(this, &PistaDialogo::sigUmbralActualizado, static_cast<PistaEscena*>(vistaPreliminar->scene()), &PistaEscena::slotUmbralModificado);

    //Actualiza el LineEdit de orientacion cuando se mueve el dial
    connect(dialPista, &QDial::sliderMoved, this, &PistaDialogo::actualizarLEOrientacion);

    // Conecta a la señal de la escena que avisa cuando la línea de umbral se movió con un slot propio para
    // actualizar los LineEdits
    connect(static_cast<PistaEscena*>(vistaPreliminar->scene()), &PistaEscena::sigLineaUmbralMovida,
            this, &PistaDialogo::slotLineaUmbralMovida);

    connect(this, &PistaDialogo::sigUmbralMaxActualizado,static_cast<PistaEscena*>(vistaPreliminar->scene()),
            &PistaEscena::slotSetLimUmbrales);
}