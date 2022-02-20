#include "graficadoraeropuerto.h"

GraficadorAeropuerto::GraficadorAeropuerto(AeropuertoVista *gv) :
    vistaAeropuerto(gv)
{
    escenaAeropuerto = static_cast<AeropuertoEscena*>(gv->scene());
    colorPavimento = new QBrush(Qt::lightGray);
    colorMargen = new QBrush(Qt::darkGray);
    bordeNegro = new QPen(Qt::black, 0);
    bordeBlanco = new QPen(Qt::white, 0);
    bordeTransparente = new QPen(Qt::black, 0, Qt::NoPen);
}

void GraficadorAeropuerto::actualizarAeropuerto(const QList<Pista>& ps, const QList<Rodaje>& rs, const QList<Plataforma>& as)
{
    escenaAeropuerto->clear();
    listaGraficosRodajes.clear();
    listaGraficosPlataformas.clear();
    listaGraficosPistas.clear();

    //RECTANGULOS RODAJES
    for (int i = 0; i < rs.size(); ++i) {
        listaGraficosRodajes.append(poligonoVector(rs.at(i).coordInicio, rs.at(i).coordFinal, rs.at(i).ancho/2));
    }

    //POLIGONOS PLATAFORMA
    for (int i = 0; i < as.size(); ++i) {
        listaGraficosPlataformas.append(as.at(i).coordPerimetro);
    }

    //RECTANGULO PISTA
    for (int i = 0; i < ps.size(); ++i) {
        QRectF* pavPista = new QRectF(-ps.at(i).largo/2.0,-ps.at(i).ancho/2.0,ps.at(i).largo,ps.at(i).ancho);
        listaGraficosPistas.append(*pavPista);
        graficarMargenes(ps.at(i));
    }

    //GRAFICA EL CONJUNTO DE LOS PAVIMENTOS. ALGO NO FUNCIONA CON SIMPLIFIED()
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    //Agrega Pista
    for (int i = 0; i <listaGraficosPistas.size(); ++i) {
        path.addRect(listaGraficosPistas.at(i));
    }
    //Agrega Plataformas
    for (int i = 0; i <listaGraficosPlataformas.size(); ++i) {
        path.addPolygon(listaGraficosPlataformas.at(i));
    }
    //Agrega Rodajes
    for (int i = 0; i <listaGraficosRodajes.size(); ++i) {
        path.addPolygon(listaGraficosRodajes.at(i));
    }
    path = path.simplified();
    QGraphicsPathItem* pavRigido = escenaAeropuerto->addPath(path, *bordeNegro, *colorPavimento);

    vistaAeropuerto->fitInView(pavRigido,Qt::KeepAspectRatio);

    //Grafica la pintura de la pista 0 solamente
//    graficarPinturaPista(ps.at(0));

    vistaAeropuerto->actualizarEntorno();
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

void GraficadorAeropuerto::graficarPinturaPista(const Pista & p)
{
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

    //Nota: Dada la definición de centerline, y con el fin de facilitar la graficación, se fija el valor del
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

    vistaAeropuerto->actualizarEntorno();
}

void GraficadorAeropuerto::graficarMargenes(const Pista& p)
{
    //Grafica márgenes de pista1 y áreas anterior al umbral
    if(p.ancho <60){
        escenaAeropuerto->addRect(-p.largo/2.0-30,-p.ancho/2.0-(60-p.ancho)/2.0,p.largo+60,60, *bordeTransparente, *colorMargen);
    }
    else{
        escenaAeropuerto->addRect(-p.largo/2.0-30,-p.ancho/2.0,p.largo+60,p.ancho, *bordeTransparente, *colorMargen);
    }

    vistaAeropuerto->actualizarEntorno();
}

qreal GraficadorAeropuerto::largoVector(const QPointF ini, const QPointF fin)
{
    qreal largo = qSqrt(qPow(ini.x()-fin.x(), 2) + qPow(ini.y()-fin.y(), 2));
    return largo;
}

qreal GraficadorAeropuerto::anguloVector(const QPointF ini, const QPointF fin)
{
    qreal angulo = qAtan((fin.y()-ini.y())/(fin.x()-ini.x()));
    return angulo;
}

QPolygonF GraficadorAeropuerto::poligonoVector(const QPointF ini, const QPointF fin, qreal offset)
{
    QPointF ini1 = QPointF(ini.x()+qCos(anguloVector(ini, fin)+M_PI_2)*offset, ini.y()+qSin(anguloVector(ini, fin)+M_PI_2)*offset);
    QPointF ini2 = QPointF(ini.x()+qCos(anguloVector(ini, fin)-M_PI_2)*offset, ini.y()+qSin(anguloVector(ini, fin)-M_PI_2)*offset);
    QPointF fin1 = QPointF(fin.x()+qCos(anguloVector(ini, fin)+M_PI_2)*offset, fin.y()+qSin(anguloVector(ini, fin)+M_PI_2)*offset);
    QPointF fin2 = QPointF(fin.x()+qCos(anguloVector(ini, fin)-M_PI_2)*offset, fin.y()+qSin(anguloVector(ini, fin)-M_PI_2)*offset);
    QPolygonF polyRodaje({ini1, fin1, fin2, ini2, ini1});
    return polyRodaje;
}
