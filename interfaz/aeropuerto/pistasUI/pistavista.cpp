#include "pistavista.h"

PistaVista::PistaVista(QWidget* w) :
    QGraphicsView(w),
    contenidoGraficado(false)
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

    escena = new PistaEscena;
    setScene(escena);

    connect(cbActivarCotas, &QCheckBox::stateChanged, this, &PistaVista::chBoxCotasAccionada);
}

void PistaVista::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
       {
           QPointF movimiento = mapToScene(event->pos())-inicioRueda;
           centroVista -= movimiento;

           //Esto limita el movimiento del viewport para que no se salgar fuera de la escena
           centroVista.setX(qMax(centroVista.x(),sceneXmin+vpRectW/2));
           centroVista.setX(qMin(centroVista.x(),sceneXmax-vpRectW/2));
           centroVista.setY(qMax(centroVista.y(),sceneYmin+vpRectH/2));
           centroVista.setY(qMin(centroVista.y(),sceneYmax-vpRectH/2));

           centerOn(centroVista);
           inicioRueda = mapToScene(event->pos());
       }
       QGraphicsView::mouseMoveEvent(event);
       viewport()->update(); //Esto es clave para que no sucedan cosas raras en el fondo al mover los items
}

void PistaVista::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
    {
        inicioRueda = mapToScene(event->pos());
    }
    QGraphicsView::mousePressEvent(event);
}

void PistaVista::wheelEvent(QWheelEvent *event)
{
    QPoint puntoMouseEnView1 = event->pos();
    QPointF puntoMouseEnScene1 = mapToScene(puntoMouseEnView1);
    qreal sc = 1+event->angleDelta().y()/(10000.0 / SENS_WHEEL); //SENS_WHEEL regula la sensibilidad

    // Esto es solo un sanity check
    float scHor = transform().m11(); //Escala horizontal
    float scVer = transform().m22(); //Escala vertical
    if (std::abs(1 - std::abs(scHor/scVer))>0.0001) qInfo() << "El escalado vert y hor no es proporcional";

    // Si la escala que obtendría al aplicar sc me hiciera estar por debajo de la escala mínima, solo lo escalo
    // hasta llegar a la escala mínima
    if (scHor*sc < minScale) {
        scale(minScale/transform().m11(),minScale/transform().m11());
    }
    else
    {
        scale(sc,sc);
    }

    //Esto es para que el punto fijo al escalar sea el punto abajo del puntero del mouse
    QPointF puntoMouseEnScene2 = mapToScene(puntoMouseEnView1);
    QPointF desplazamiento = puntoMouseEnScene1 - puntoMouseEnScene2;
    centroVista += desplazamiento;
    centerOn(centroVista);
}

void PistaVista::resizeEvent(QResizeEvent *event)
{
    if (contenidoGraficado) actualizarScRect();
    moverAOrigien();
    QGraphicsView::resizeEvent(event);
}

void PistaVista::centrarVista()
{
    QRectF r1 = scene()->itemsBoundingRect();
    QRectF r2 = mapToScene(viewport()->rect()).boundingRect();

    //Calculo cuánto tengo que ampliar o reducir la escala para que mi
    //bounding rect entre apretado en el viewport
    float cociente1 = r2.width()/r1.width();
    float cociente2 = r2.height()/r1.height();
    float escala = qMin(cociente1,cociente2)*0.9;
    scale(escala,escala);

    moverAOrigien();
}

void PistaVista::graficarPista(Pista p)
{
    escena->graficarPista(p);
    escena->mostrarCotas(cbActivarCotas->isChecked());
    centrarVista();
    actualizarScRect();
    contenidoGraficado = true;
}

void PistaVista::vaciarContenido()
{
    escena->limpiar();
    contenidoGraficado = false;
}

void PistaVista::chBoxCotasAccionada(int state)
{
    escena->mostrarCotas(state == 0 ? false : true);
}

void PistaVista::actualizarScRect()
{
    // La idea es que la escena sea lo suficientemente grande como para permitir un
    // movimiento fluido del viewport por sobre ella. Para eso el viewport en su maximo
    // tamaño (que corresponde a la minima escala del contenido) debe poder scrollear
    // completamente en la escena. Ver Viewport&graphicsScene.png.

    int vpMaxHeight;
    int vpMaxWidth;

    float brW = scene()->itemsBoundingRect().width();
    float brH = scene()->itemsBoundingRect().height();
    float brR = brH/brW;  //Relacion de aspecto del items bounding rect

    vpRect = mapToScene(viewport()->rect()).boundingRect();
    vpRectW = vpRect.width();
    vpRectH = vpRect.height();

    float vpR = vpRectH/vpRectW; //Relacion de aspecto del viewport

    float sc = 1; // Factor de escala a aplicar, el default es no escalar

    // El item es mas esbelto que el viewport, entonces chequeamos que el elemento
    // entre REL_VACIO veces en el alto del viewpot
    if (brR > vpR) {
        vpMaxHeight = REL_VACIO * brH; //REL_VACIO es las veces que puede entrar el brect del item en el viewport
        vpMaxWidth = vpMaxHeight / vpR;
        //Hay que ajustar la escala minima. transform().m11() es la escala actual.
        minScale = vpRectH/vpMaxHeight * transform().m11();
        //En el caso de que en la situacion actual ya me esté pasando del tamaño máximo, tengo que ajustar la escala
        if (vpRectH > vpMaxHeight) {
            sc = vpRectH/vpMaxHeight;
        }
    }
    // El item es mas achatado que el viewport, entonces chequeamos que el elemento
    // entre REL_VACIO veces en el ancho del viewpot
    else {
        vpMaxWidth = REL_VACIO * brW;
        vpMaxHeight = vpMaxWidth * vpR;
        //Hay que ajustar la escala minima. transform().m11() es la escala actual.
        minScale = vpRectW/vpMaxWidth * transform().m11();
        //En el caso de que en la situacion actual ya me esté pasando del tamaño máximo, tengo que ajustar la escala
        if (vpRectW > vpMaxWidth) {
            sc = vpRectW/vpMaxWidth;
        }
    }

    //La escena tiene que ser tan grande como para contenter dos veces el viewport y una vez el bounding rect
    sceneWidth = vpMaxWidth*2 + brW;
    sceneHeight = vpMaxHeight*2 + brH;

    //Ajusto la escena con respecto al centro del gráfico
    QPointF centroDibujo = scene()->itemsBoundingRect().center();
    sceneXmin = centroDibujo.x() - sceneWidth/2;
    sceneYmin = centroDibujo.y() - sceneHeight/2;
    sceneXmax = centroDibujo.x() + sceneWidth/2;
    sceneYmax = centroDibujo.y() + sceneHeight/2;
    scene()->setSceneRect(sceneXmin,sceneYmin,sceneWidth,sceneHeight);

    //Ajusto la escala, puede que sc=1 con lo cual no pasa nada
    scale(sc,sc);
}

