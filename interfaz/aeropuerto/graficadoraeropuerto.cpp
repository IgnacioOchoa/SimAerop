#include "graficadoraeropuerto.h"

GraficadorAeropuerto::GraficadorAeropuerto(AeropuertoVista *gv) :
    vistaAeropuerto(gv)
{
    escenaAeropuerto = static_cast<AeropuertoEscena*>(gv->scene());
    gradienteFondoPista = new QLinearGradient(QPointF(-1000, -1000), QPointF(1000, 1000));
    gradienteFondoPista->setColorAt(0, "#faf0e3");
    gradienteFondoPista->setColorAt(1, "#e0d1bc");
    fondoPista = new QBrush(*gradienteFondoPista);
    colorPavimento = new QBrush("#A4B3B6");
    colorMargen = new QBrush("#828282");
    escenaAeropuerto->setBackgroundBrush(*fondoPista);
    bordeNegro = new QPen(Qt::black, 0);
    bordeBlanco = new QPen(Qt::white, 0);
    bordeTransparente = new QPen(Qt::black, 0, Qt::NoPen);
}

void GraficadorAeropuerto::actualizarAeropuerto(const Pista& p, const Rodaje& r, const Plataforma& a)
{
    escenaAeropuerto->clear();
    escenaAeropuerto->setBackgroundBrush(*fondoPista);

    //RECTANGULO RODAJE
    QRectF* primitivaRodaje = new QRectF(r.posicion,-r.ancho/2.0,r.largo,r.ancho);
    QTransform t = QTransform().translate( r.posicion,0 ).rotate( -r.angulo ).translate(-r.posicion,0 );
    QRectF pavRodaje = t.mapRect(*primitivaRodaje);

    //RECTANGULO PLATAFORMA
    QRectF* pavPlataforma = new QRectF(-150,-300,300,100);

    //RECTANGULO PISTA
    QRectF* pavPista = new QRectF(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho);

    //GRAFICADOR DE PISTA
    //Grafica márgenes de pista y áreas anterior al umbral
    QGraphicsRectItem* pavFlexible = new QGraphicsRectItem;
    if(p.ancho <60){
        pavFlexible = escenaAeropuerto->addRect(-p.largo/2.0-30,-p.ancho/2.0-(60-p.ancho)/2.0,p.largo+60,60, *bordeTransparente, *colorMargen);
    }
    else{
        pavFlexible = escenaAeropuerto->addRect(-p.largo/2.0-30,-p.ancho/2.0,p.largo+60,p.ancho, *bordeTransparente, *colorMargen);
    }

    //Grafica el conjunto de los pavimentos
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    //Agrega Pista
    path.addRect(*pavPista);
    //Agrega Plataforma
    path.addRect(*pavPlataforma);
    //Agrega Rodaje
    path.addRect(pavRodaje);

    QPainterPath path2;
    path2 = path.simplified();

    QGraphicsPathItem* pavRigido = escenaAeropuerto->addPath(path2, *bordeNegro, *colorPavimento);

    //Area invisible que engloba la pista
    escenaAeropuerto->addRect(-p.largo/2.0 - 200, -p.ancho/2.0, p.largo + 400, p.ancho, *bordeTransparente);

    //GRAFICADOR DE PINTURA DE PISTA

    //Determinación de Parámetros según ancho de pista
    if (p.ancho<23){
        fajas = 2;
        anchoFajasLa = 0.3;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else if(p.ancho<30){
        fajas = 3;
        anchoFajasLa = 0.45;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else if(p.ancho<45){
        fajas = 4;
        anchoFajasLa = 0.9;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else if(p.ancho<60){
        fajas = 6;
        anchoFajasLa = 0.9;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else {
        fajas = 8;
        anchoFajasLa = 0.9;
        anchoFajasUm = (54.0)/(fajas*4);
    }

    //Determinación de Parámetros según largo de pista
    if (p.largo<800){
        distanciaUmVi = 150;
        anchoFajasVi = 4;
        espaciadoFajasVi = 6;
    }
    else if(p.largo<1200){
        distanciaUmVi = 250;
        anchoFajasVi = 6;
        espaciadoFajasVi = 9;
    }
    else if(p.largo<2400){
        distanciaUmVi = 300;
        anchoFajasVi = 6;
        espaciadoFajasVi = 18;
    }
    else {
        distanciaUmVi = 400;
        anchoFajasVi = 10;
        espaciadoFajasVi = 22.5;
    }

    //Graficación de barras de umbral
    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraUm1 = escenaAeropuerto->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, *bordeBlanco, QBrush("white"));
        barraUm1->moveBy(-(p.largo/2.0 - 21),-(p.ancho/2.0 - 3  -anchoFajasUm/2) + i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm2 = escenaAeropuerto->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, *bordeBlanco, QBrush("white"));
        barraUm2->moveBy(-(p.largo/2.0 - 21),(p.ancho/2.0 - 3  -anchoFajasUm/2) - i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm3 = escenaAeropuerto->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, *bordeBlanco, QBrush("white"));
        barraUm3->moveBy((p.largo/2.0 - 21),-(p.ancho/2.0 - 3 - anchoFajasUm/2) + i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm4 = escenaAeropuerto->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, *bordeBlanco, QBrush("white"));
        barraUm4->moveBy((p.largo/2.0 - 21),(p.ancho/2.0 - 3 - anchoFajasUm/2) - i*anchoFajasUm*2);
    }

    //Graficación de fajas transversales de umbral y fajas laterales de pista
    //Nota: No se programó limitación a 60 m de ancho de pista.
    QPainterPath outer;
    outer.addRect(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho);
    QPainterPath inner;
    inner.addRect(-p.largo/2.0+1.8,-p.ancho/2.0+anchoFajasLa,p.largo-3.6,p.ancho-anchoFajasLa*2);
    outer = outer.subtracted(inner);

    QGraphicsPathItem* fajasTransyLat = escenaAeropuerto->addPath(outer, *bordeBlanco,  QBrush("white"));

    //Graficación de centerline

    //Nota: Dadas la definición de centerline, y con el fin de facilitar la graficación, se fija el valor del
    //intervalo a 2/3 de la longitud de la faja de eje. Dada la formulación matemática, el valor del largo de
    //faja de eje se mantendrá entre 30 y 35 m para pistas de mas de 500 m. ANCHO DEPENDE DE CAT APP.

    largoEjes = (p.largo-138)/(5*((p.largo-138+20)/50)/3.0-2/3.0);

    for (int i=0; i<(p.largo-138+20)/50; i++)
    {
        QGraphicsRectItem* ejePista = escenaAeropuerto->addRect(-largoEjes/2.0,-0.45,largoEjes,0.9, *bordeBlanco, QBrush("white"));
        ejePista->moveBy(-(p.largo/2.0-69-largoEjes/2.0)+5*largoEjes*i/3.0,0);
    }

    //Graficación de puntos de visada
    //Nota: En esta versión se simplifica la graficación. Algunos de los parámetros deberían poder variar en rangos determinados.

    QGraphicsRectItem* barraVi1 = escenaAeropuerto->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, *bordeBlanco, QBrush("white"));
    barraVi1->moveBy(-(p.largo/2.0-distanciaUmVi+22.5),(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    QGraphicsRectItem* barraVi2 = escenaAeropuerto->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, *bordeBlanco, QBrush("white"));
    barraVi2->moveBy(-(p.largo/2.0-distanciaUmVi+22.5),-(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    QGraphicsRectItem* barraVi3 = escenaAeropuerto->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, *bordeBlanco, QBrush("white"));
    barraVi3->moveBy((p.largo/2.0-distanciaUmVi+22.5),(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    QGraphicsRectItem* barraVi4 = escenaAeropuerto->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, *bordeBlanco, QBrush("white"));
    barraVi4->moveBy((p.largo/2.0-distanciaUmVi+22.5),-(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    //Grafica centro de la pista
    escenaAeropuerto->addLine(QLineF(-5,-5,5,5), *bordeNegro);
    escenaAeropuerto->addLine(QLineF(-5,5,5,-5), *bordeNegro);

    vistaAeropuerto->fitInView(pavFlexible,Qt::KeepAspectRatio);
    //vistaPista->scale(0.98, 0.98);

}

void GraficadorAeropuerto::reportarDatosEscena()
{
    qInfo() << "escenaPista->sceneRect() = " << escenaAeropuerto->sceneRect();
    qInfo() << "ui->graficoPista->sceneRect() = " << vistaAeropuerto->sceneRect();
    qInfo() << "Item at (0,0): " << vistaAeropuerto->itemAt(vistaAeropuerto->mapFromScene(0,0));
    qInfo() << "ui->graficoPista->transform() = " << vistaAeropuerto->transform();
    qInfo() << "ui->graficoPista->rect() (from QWidget) = " << vistaAeropuerto->rect();
    qInfo() << "ui->graficoPista->contentsRect() (from QWidget) = " << vistaAeropuerto->contentsRect();
    qInfo() << "ui->graficoPista->mapToScene(ui->graficoPista->viewport()->geometry()).boundingRect() "
               "(from QAbstractScrollArea) = "
            << vistaAeropuerto->mapToScene(vistaAeropuerto->viewport()->geometry()).boundingRect();

}
