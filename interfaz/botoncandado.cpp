#include "botoncandado.h"

BotonCandado::BotonCandado(QWidget* parent) :
    QPushButton(parent)
{
    QPixmap imagenCerrado(":/imagenes/imagenes/candado.png");
    iconoCerrado = QIcon(imagenCerrado);

    QPixmap imagenAbierto(":/imagenes/imagenes/candado2.png");
    iconoAbierto = QIcon(imagenAbierto);
    setIcon(iconoAbierto);

    setCheckable(true);
    setStyleSheet("BotonCandado{background-color: transparent; border: none; padding: 2}"
                  "BotonCandado:hover{background-color: gray; border: none}"
                  "BotonCandado:checked{background-color: #b5f5b8}");
    connect(this, &QAbstractButton::toggled, this, &BotonCandado::slotActualizarIcono);

}

void BotonCandado::slotActualizarIcono(bool checked)
{
    if(checked)
    {
        setIcon(iconoCerrado);
        emit sigValorFijado(true);
    }
    else {
        setIcon(iconoAbierto);
        emit sigValorFijado(false);
    }
}

void BotonCandado::slotCerrarCandado()
{
    setChecked(true);
}
