#include "vistaconfpista.h"

VistaConfPista::VistaConfPista(QWidget* w) :
    QGraphicsView(w)
{
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    centroVista = QPointF();

    cbActivarCotas = new QCheckBox(this);
    cbActivarCotas->setText("Mostrar cotas");

    QVBoxLayout* vLay = new QVBoxLayout();
    QHBoxLayout* hLay = new QHBoxLayout();
    vLay->addStretch(1);
    hLay->addStretch(1);
    hLay->addWidget(cbActivarCotas);
    vLay->addItem(hLay);
    setLayout(vLay);

    escena = new EscenaConfPista;
    setScene(escena);
}

void VistaConfPista::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
       {
           QPointF movimiento = mapToScene(event->pos())-inicioRueda;
           centroVista -= movimiento;
           centerOn(centroVista);
           inicioRueda = mapToScene(event->pos());
       }
       QGraphicsView::mouseMoveEvent(event);
       viewport()->update(); //Esto es clave para que no sucedan cosas raras en el fondo al mover los items
}

void VistaConfPista::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
    {
        inicioRueda = mapToScene(event->pos());
    }
    QGraphicsView::mousePressEvent(event);
}

void VistaConfPista::wheelEvent(QWheelEvent *event)
{

}

void VistaConfPista::centrarVista(QPointF p)
{
    centerOn(p);
    centroVista = QPointF();
}

void VistaConfPista::ajustarContenidos()
{
    QRectF r1 = scene()->itemsBoundingRect();
    QRectF r2 = mapToScene(viewport()->rect()).boundingRect();

    float cociente1 = r2.x()/r1.x();
    float cociente2 = r2.y()/r1.y();
    float escala = qMin(cociente1,cociente2)*0.9;

    scale(escala,escala);
}

void VistaConfPista::graficarPista(QRectF rectPista)
{
    escena->graficarPista(rectPista);
    ajustarContenidos();
}

void VistaConfPista::vaciarContenido()
{
    escena->clear();
}

void VistaConfPista::contenidoCambiado()
{

}

