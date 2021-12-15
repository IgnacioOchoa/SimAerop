#include "dialpista.h"
#include "cmath"
#define PI 3.141592
#define NroPtos 36

DialPista::DialPista(QWidget* parent) :
QDial(parent)
{
    setValue(0);
    setRange(0,NroPtos-1);
}

void DialPista::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);
    qreal angulo = 3*PI/2.0 - (2*PI)/NroPtos * value();
    QPainter painter(this);

    //Circulo exterior
    painter.setBrush(brushFondo);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(this->width()/2, this->height()/2);
    painter.drawEllipse(QPointF(0,0),QDial::height()/2-4 , QDial::height()/2-4);

    //Rect pista
    painter.setBrush(brushPista);
    painter.setPen(penLineaBlanca);

    painter.save();

    painter.rotate(-(angulo*180/PI));
    painter.drawRect(-45,-7,90,14);

    //Lineas de umbrales
    painter.setPen(penLineaBlanca);
    for(int y = -6; y<=6; y+=3) {
        painter.drawLine(-42, y, -32, y);
        painter.drawLine(32, y, 42, y);
    }

    //Linea central
    painter.setPen(penLineaBlancaPunteada);
    painter.drawLine(-40,0,40,0);

    painter.restore();
    emit(sliderMoved(value()));

}
