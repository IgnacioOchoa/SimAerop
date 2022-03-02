#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(const QList<Pista>& listaPistas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo),
    btnsEdicionRodaje(new QButtonGroup(this)),
    pistas(listaPistas)
{
    ui->setupUi(this);
    setStyleSheet("QLabel#lbSeleccionCabecera { background-color: transparent; border-color: black; "
                  "border-width: 2; border-style: solid; border-radius: 10;"
                  "color: blue }"
                  "QLabel#lbSeleccionCabecera:hover {background-color: #e1eaeb}"
                  "QLabel#lbSeleccionCabecera:focus { background-color: #defdff}");
    ui->lbSeleccionCabecera->setFocusPolicy(Qt::ClickFocus);
    ui->lbSeleccionCabecera->installEventFilter(this);
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
    if(obj == ui->lbSeleccionCabecera && event->type() == QEvent::FocusIn)
    {
        slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::SNAP_CABECERAS);
    }
    else if (obj == ui->lbSeleccionCabecera && event->type() == QEvent::FocusOut)
    {
        RodajeEdicionVista* rod = qobject_cast<RodajeEdicionVista*>(focusWidget());
        if(!rod) slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::PISTA);
    }
    return false;
}

void RodajeEdicionDialogo::slotModoEdicionCambiado(int m)
{
    RodajeParametros rp;
    RodajeEdicionVista::modoEdicion modo = static_cast<RodajeEdicionVista::modoEdicion>(m);
    switch(modo) {
    case RodajeEdicionVista::modoEdicion::PISTA:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[0]);
        ui->swPanelParametros->setCurrentIndex(0);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::SNAP_CABECERAS:
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
    vista->slotSetModEdicion(m);
}

void RodajeEdicionDialogo::slotCabeceraSeleccionada(QPointF pto) const
{
    ui->lbSeleccionCabecera->setText(pistas[0].getCabecera(pto));
}

void RodajeEdicionDialogo::configurarWidgets()
{
    vista = ui->gvRodajeEdicion;
    RodajeParametros rp;

    ui->gvRodajeEdicion->configEscena(escena);
    ui->cbGrilla->setChecked(false);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje1, RodajeEdicionVista::modoEdicion::PISTA);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje2, RodajeEdicionVista::modoEdicion::DOSPUNTOS);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje3, RodajeEdicionVista::modoEdicion::PARALELA);
    connect(ui->cbGrilla, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotChckMostrarGrilla);
    connect(ui->cbCabeceras, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotMostrarCabeceras);
    connect(btnsEdicionRodaje, QOverload<int>::of(&QButtonGroup::idPressed), this, &RodajeEdicionDialogo::slotModoEdicionCambiado);
    connect(vista, QOverload<int>::of(&RodajeEdicionVista::sigCambiarModo), this, &RodajeEdicionDialogo::slotModoEdicionCambiado);
    connect(vista, QOverload<QPointF>::of(&RodajeEdicionVista::sigCabeceraSeleccionada), this, &RodajeEdicionDialogo::slotCabeceraSeleccionada);
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
    slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::PISTA);
    vista->slotSetModEdicion(RodajeEdicionVista::modoEdicion::PISTA);
    for (int i = 0; i<pistas.count(); i++)
    {
        Pista p = pistas[i];
        escena->seleccionarCabecera(i, p.getPuntoCabecera(Pista::CAB1));
    }
    ui->lbSeleccionCabecera->setText(pistas[0].getCabecera(Pista::CAB1));

}
