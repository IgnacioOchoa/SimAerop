#include "vistagraficabase.h"

VistaGraficaBase::VistaGraficaBase(QWidget* w) :
    QGraphicsView(w),
    contenidoGraficado(false)
{
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setRenderHints(QPainter::Antialiasing);
    setMouseTracking(true);
    centroVista = QPointF();
}

void VistaGraficaBase::mouseMoveEvent(QMouseEvent *event)
{
    if(!contenidoGraficado) return; // Cuando no hay nada graficado no tiene sentido scrollear
    if (event->buttons() == Qt::MidButton || (event->buttons () == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier))
    //CORREGIR CUANDO HAYA RUEDA
    {
           QPointF movimiento = mapToScene(event->pos())-inicioRueda;
           centroVista -= movimiento;

           //Esto limita el movimiento del viewport para que no se salga fuera de la escena
           centroVista.setX(qMax(centroVista.x(),sceneXmin+vpRectW/2));
           centroVista.setX(qMin(centroVista.x(),sceneXmax-vpRectW/2));
           centroVista.setY(qMax(centroVista.y(),sceneYmin+vpRectH/2));
           centroVista.setY(qMin(centroVista.y(),sceneYmax-vpRectH/2));

           centerOn(centroVista);
           inicioRueda = mapToScene(event->pos());
           emit centroMovido();
       }
       QGraphicsView::mouseMoveEvent(event);
       viewport()->update(); //Esto es clave para que no sucedan cosas raras en el fondo al mover los items
}

void VistaGraficaBase::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton || event->buttons() == Qt::LeftButton) //CORREGIR CUANDO HAYA RUEDA
    {
        inicioRueda = mapToScene(event->pos());
    }
    QGraphicsView::mousePressEvent(event);
}

void VistaGraficaBase::wheelEvent(QWheelEvent *event)
{
    if(!contenidoGraficado) return; // Cuando no hay nada graficado no tiene sentido hacer zoom
    QPoint puntoMouseEnView1 = event->pos();
    QPointF puntoMouseEnScene1 = mapToScene(puntoMouseEnView1);
    qreal sc = 1+event->angleDelta().y()/(10000.0 / SENS_WHEEL); //SENS_WHEEL regula la sensibilidad

    // Esto es solo un sanity check
    double scHor = transform().m11(); //Escala horizontal
    double scVer = transform().m22(); //Escala vertical
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

void VistaGraficaBase::resizeEvent(QResizeEvent *event)
{
    if (contenidoGraficado) actualizarScRect();
    moverAOrigien();
    QGraphicsView::resizeEvent(event);
}

void VistaGraficaBase::centrarVista()
{
    QRectF r1 = scene()->itemsBoundingRect();
    QRectF r2 = mapToScene(viewport()->rect()).boundingRect();

    //Calculo cuánto tengo que ampliar o reducir la escala para que mi
    //bounding rect entre apretado en el viewport
    double cociente1 = r2.width()/r1.width();
    double cociente2 = r2.height()/r1.height();
    double escala = qMin(cociente1,cociente2)*0.9;
    scale(escala,escala);

    moverAOrigien();
}

void VistaGraficaBase::actualizarScRect(QRectF rectElementos)
{
    // La idea es que la escena sea lo suficientemente grande como para permitir un
    // movimiento fluido del viewport por sobre ella. Para eso el viewport en su maximo
    // tamaño (que corresponde a la minima escala del contenido) debe poder scrollear
    // completamente en la escena. Ver Viewport&graphicsScene.png.

    if(!contenidoGraficado) return;

    double vpMaxHeight;
    double vpMaxWidth;
    double brW;
    double brH;

    if(rectElementos == QRectF()) rectElementos = scene()->itemsBoundingRect();

    brW = rectElementos.width();
    brH = rectElementos.height();

    double brR = brH/brW;  //Relacion de aspecto del items bounding rect

    vpRect = mapToScene(viewport()->rect()).boundingRect();
    vpRectW = vpRect.width();
    vpRectH = vpRect.height();

    double vpR = vpRectH/vpRectW; //Relacion de aspecto del viewport

    double sc = 1; // Factor de escala a aplicar, el default es no escalar

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
    QPointF centroDibujo = rectElementos.center();
    sceneXmin = centroDibujo.x() - sceneWidth/2;
    sceneYmin = centroDibujo.y() - sceneHeight/2;
    sceneXmax = centroDibujo.x() + sceneWidth/2;
    sceneYmax = centroDibujo.y() + sceneHeight/2;
    scene()->setSceneRect(sceneXmin,sceneYmin,sceneWidth,sceneHeight);

    //Ajusto la escala, puede que sc=1 con lo cual no pasa nada
    scale(sc,sc);

//    Debug
//    qInfo() << "m11" << transform().m11();
//    qInfo() << "vpRectW / vpMaxWidth (sc) = " << sc;
//    qInfo() << "    vpRectW = " << vpRectW;
//    qInfo() << "    vpRectH = " << vpRectH;
//    qInfo() << "    brW     = " << brW;
//    qInfo() << "    brH     = " << brH;
//    qInfo() << "        scWidth = " << sceneWidth;
//    qInfo() << "        scHeight = " << sceneHeight;
//    qInfo() << "            vpMaxWidth = " << vpMaxWidth;
//    qInfo() << "            vpMaxHeight = " << vpMaxHeight;
//    qInfo() << "            REL_VACIO = " << REL_VACIO;
//    qInfo() << "                suma elementos = " << 2*vpRectW + rectElementos.width();
}
