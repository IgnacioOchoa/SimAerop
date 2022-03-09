#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(const QList<Pista>& listaPistas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo),
    btnsEdicionRodaje(new QButtonGroup(this)),
    pistas(listaPistas)
{
    ui->setupUi(this);
    QFile file(":/stylesheets/ssEditorRodajes.qss");
        if(file.open(QFile::ReadOnly)) {
           QString styleSheet = QLatin1String(file.readAll());
           setStyleSheet(styleSheet);
        }
    ui->lbSeleccionCabecera->setFocusPolicy(Qt::ClickFocus);
    ui->lbPistaTrabajo->setFocusPolicy(Qt::ClickFocus);
    ui->lbSeleccionCabecera->installEventFilter(this);
    ui->lbPistaTrabajo->installEventFilter(this);
    ui->leDistancia->installEventFilter(this);
    escena = new RodajeEdicionEscena(ui->gvRodajeEdicion,listaPistas, this);
    configurarWidgets();
    actualizarPanelParametros();
    parametrosIniciales();

}

RodajeEdicionDialogo::~RodajeEdicionDialogo()
{
    delete ui;
}

void RodajeEdicionDialogo::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    escena->graficar();
}

bool RodajeEdicionDialogo::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::FocusIn)
    {
        if(obj == ui->lbSeleccionCabecera) {
            vista->setModSnap(RodajeEdicionVista::modoSnap::CABECERAS);
        }
        else if (obj == ui->lbPistaTrabajo) {
            vista->setModSnap(RodajeEdicionVista::modoSnap::PISTA);
        }
        else if (obj == ui->leDistancia) {
            vista->setModSnap(RodajeEdicionVista::modoSnap::PTOPISTA);
        }
    }
    else if (event->type() == QEvent::FocusOut)
    {
       if(obj == ui->lbSeleccionCabecera) {
           RodajeEdicionVista* rod = qobject_cast<RodajeEdicionVista*>(focusWidget());
           if(!rod) vista->setModSnap(RodajeEdicionVista::modoSnap::NULO);
       }
       else if (obj == ui->lbPistaTrabajo) {
           RodajeEdicionVista* rod = qobject_cast<RodajeEdicionVista*>(focusWidget());
           if(!rod) vista->setModSnap(RodajeEdicionVista::modoSnap::NULO);
       }
       else if (obj == ui->leDistancia)
       {

       }
    }
    return false;
}

void RodajeEdicionDialogo::slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion m)
{
    RodajeParametros rp;
    switch(m) {
    case RodajeEdicionVista::modoEdicion::PISTA:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[0]);
        ui->swPanelParametros->setCurrentIndex(0);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::DOSPUNTOS:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[1]);
        ui->swPanelParametros->setCurrentIndex(1);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::PARALELA:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[2]);
        ui->swPanelParametros->setCurrentIndex(2);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::NULO:
        break;
        //ui->gbParametros->
    default:
        break;
    }
    vista->setModEdicion(m);
}

void RodajeEdicionDialogo::slotCabeceraSeleccionada(QString cabecera) const
{
    ui->lbSeleccionCabecera->setText(cabecera);
}

void RodajeEdicionDialogo::slotPistaSeleccionada(int nroPista)
{
    ui->lbPistaTrabajo->setText(pistas[nroPista].nombre);
}

void RodajeEdicionDialogo::slotBotonModoEdicionAccionado(int nroBoton)
{
    switch(nroBoton) {
    case 0: slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::PISTA);
        break;
    case 1: slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::DOSPUNTOS);
        break;
    case 2: slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::PARALELA);
        break;
    }
}

void RodajeEdicionDialogo::slotDistanciaACabeceraCambiada(float dist)
{
    ui->leDistancia->setText(QString::number(dist,'f',1));
}

void RodajeEdicionDialogo::configurarWidgets()
{
    vista = ui->gvRodajeEdicion;
    RodajeParametros rp;

    ui->cbGrilla->setChecked(false);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje1, 0);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje2, 1);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje3, 2);
    connect(ui->cbGrilla, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotChckMostrarGrilla);
    connect(ui->cbCabeceras, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotMostrarCabeceras);
    connect(btnsEdicionRodaje, QOverload<int>::of(&QButtonGroup::idPressed), this, &RodajeEdicionDialogo::slotBotonModoEdicionAccionado);
    connect(vista, &RodajeEdicionVista::sigCabeceraSeleccionada, this, &RodajeEdicionDialogo::slotCabeceraSeleccionada);
    connect(vista, &RodajeEdicionVista::sigPistaSeleccionada, this, &RodajeEdicionDialogo::slotPistaSeleccionada);
    connect(vista, &RodajeEdicionVista::sigPosEnPistaMovido, this, &RodajeEdicionDialogo::slotDistanciaACabeceraCambiada);
    vista->configEscena(escena);
    ui->pbEditorRodaje1->setToolTip(rp.tiposRodaje[0]);
    ui->pbEditorRodaje2->setToolTip(rp.tiposRodaje[1]);
    ui->pbEditorRodaje3->setToolTip(rp.tiposRodaje[2]);
}

void RodajeEdicionDialogo::actualizarPanelParametros()
{

}

void RodajeEdicionDialogo::parametrosIniciales()
{
    ui->pbEditorRodaje1->setChecked(true);
    vista->setMaxScale(5);
    slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::PISTA);
    vista->setModEdicion(RodajeEdicionVista::modoEdicion::PISTA);
    vista->setModSnap(RodajeEdicionVista::modoSnap::NULO);
    ui->lbSeleccionCabecera->setText(pistas[0].getCabecera(Pista::CAB1));
}
