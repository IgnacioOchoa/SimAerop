#include "pistavista.h"

PistaVista::PistaVista(QWidget* w) :
    VistaGraficaBase(w)
{
    cbActivarCotas = new QCheckBox(this);
    cbActivarCotas->setText("Mostrar cotas");

    QVBoxLayout* vLay = new QVBoxLayout();
    QHBoxLayout* hLay = new QHBoxLayout();
    vLay->addStretch(1);
    hLay->addStretch(1);
    hLay->addWidget(cbActivarCotas);
    vLay->addItem(hLay);
    setLayout(vLay);

    escena = new PistaEscena;
    setScene(escena);

    connect(cbActivarCotas, &QCheckBox::stateChanged, this, &PistaVista::chBoxCotasAccionada);
}

void PistaVista::graficarPista(Pista p)
{
    escena->graficarPista(p);
    escena->mostrarCotas(cbActivarCotas->isChecked());
    centrarVista();
    actualizarScRect();
    contenidoGraficado = true;
}

void PistaVista::borrar()
{
    escena->limpiar();
    contenidoGraficado = false;
}

void PistaVista::chBoxCotasAccionada(int state)
{
    escena->mostrarCotas(state == 0 ? false : true);
}
