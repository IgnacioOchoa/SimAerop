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

    escala = 1;

    connect(cbActivarCotas, &QCheckBox::stateChanged, this, &VistaConfPista::chBoxCotasAccionada);
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
    QPoint puntoMouseEnView1 = event->pos();
    QPointF puntoMouseEnScene1 = this->mapToScene(puntoMouseEnView1);
    qreal sc = 1+event->angleDelta().y()/1000.0;

    escala *= sc;
    if (escala < 0.3)
    {
        sc = 1;
        escala = 0.3;
    }

    this->scale(sc,sc);

    QPointF puntoMouseEnScene2 = this->mapToScene(puntoMouseEnView1);

    QPointF desplazamiento = puntoMouseEnScene1 - puntoMouseEnScene2;
    centroVista += desplazamiento;
    centerOn(centroVista);

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

void VistaConfPista::graficarPista(Pista p)
{
    escena->graficarPista(p);
    escena->mostrarCotas(cbActivarCotas->isChecked());
    ajustarContenidos();
}

void VistaConfPista::dibujarUmbral(float pos, EscenaConfPista::Lado lado)
{
    escena->graficarUmbral(pos, lado);
}

void VistaConfPista::vaciarContenido()
{
    escena->limpiar();
}

void VistaConfPista::chBoxCotasAccionada(int state)
{
    escena->mostrarCotas(state == 0 ? false : true);
}

