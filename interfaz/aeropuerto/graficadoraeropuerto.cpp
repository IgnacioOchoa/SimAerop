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

    //GRAFICA EL CONJUNTO DE LOS PAVIMENTOS
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    //Agrega Pista
    for (int i = 0; i <ps.size(); ++i) {
        QPolygonF *pista = new QPolygonF(poligonoVector(ps.at(i).getPuntoCabecera(Pista::CAB1), ps.at(i).getPuntoCabecera(Pista::CAB2), ps.at(i).ancho/2.0));
        path.addPolygon(*pista);
        //ARREGLAR ORIENTACIÓN
//        graficarMargenes(ps.at(i));
    }
    //Agrega Plataformas
    for (int i = 0; i <as.size(); ++i) {
        QPolygonF *plataforma = new QPolygonF(as.at(i).coordPerimetro);
        path.addPolygon(poligonoHorario(*plataforma));
    }
    //Agrega Rodajes
    for (int i = 0; i <rs.size(); ++i) {
        QPolygonF *rodaje = new QPolygonF(poligonoVector(rs.at(i).coordInicio, rs.at(i).coordFinal, rs.at(i).ancho/2.0));
        path.addPolygon(*rodaje);
    }

    path = path.simplified();
    QGraphicsPathItem* pavRigido = escenaAeropuerto->addPath(path, *bordeNegro, *colorPavimento);

    //Grafica la pintura de las pistas
    // ARREGLAR ORIENTACIÓN
//    graficarPinturaPista(ps.at(0));

    vistaAeropuerto->actualizarEntorno();
    vistaAeropuerto->centrarVista();

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

qreal GraficadorAeropuerto::anguloVector(const QPointF ini, const QPointF fin)
{
    qreal num = fin.y()-ini.y();
    qreal den = fin.x()-ini.x();
    int quad;
    if (num >= 0 and den > 0){
        quad = 1;
    }
    if (num >= 0 and den < 0){
        quad = 2;
    }
    if (num < 0 and den < 0){
        quad = 3;
    }
    if (num < 0 and den > 0){
        quad = 4;
    }
    if (den == 0){
        if (num > 0){
            quad = 5;
        }
        else{
            quad = 6;
        }
    }

    switch(quad)
    {
    case 1:
        return qAtan((fin.y()-ini.y())/(fin.x()-ini.x()));
        break;
    case 2:
        return M_PI+qAtan((fin.y()-ini.y())/(fin.x()-ini.x()));
        break;
    case 3:
        return -M_PI+qAtan((fin.y()-ini.y())/(fin.x()-ini.x()));
        break;
    case 4:
        return qAtan((fin.y()-ini.y())/(fin.x()-ini.x()));
        break;
    case 5:
        return M_PI_2;
        break;
    case 6:
        return -M_PI_2;
        break;
    }
}

QVector<QPointF> GraficadorAeropuerto::poligonoVector(const QPointF ini, const QPointF fin, qreal offset){
    float x1 = static_cast<float>(ini.x());
    float y1 = static_cast<float>(ini.y());
    float x2 = static_cast<float>(fin.x());
    float y2 = static_cast<float>(fin.y());
    QPointF ini1 = QPointF(x1+qCos(anguloVector(ini, fin)+M_PI_2)*offset, y1+qSin(anguloVector(ini, fin)+M_PI_2)*offset);
    QPointF ini2 = QPointF(x1+qCos(anguloVector(ini, fin)-M_PI_2)*offset, y1+qSin(anguloVector(ini, fin)-M_PI_2)*offset);
    QPointF fin1 = QPointF(x2+qCos(anguloVector(ini, fin)+M_PI_2)*offset, y2+qSin(anguloVector(ini, fin)+M_PI_2)*offset);
    QPointF fin2 = QPointF(x2+qCos(anguloVector(ini, fin)-M_PI_2)*offset, y2+qSin(anguloVector(ini, fin)-M_PI_2)*offset);
    QVector<QPointF> poliVector({ini1, fin1, fin2, ini2, ini1});
    return poliVector;
}

qreal GraficadorAeropuerto::areaPoligono(const QPolygonF poli)
{
    qreal area = 0;
    int j;
    for (int i = 0; i < poli.size(); i++){
        if (i == poli.size()-1){
            j = 0;
        }
        else {
            j = i + 1;
        }
        area = area + poli.at(i).x()*poli.at(j).y()-poli.at(i).y()*poli.at(j).x();
    }
    area = area/2.0;
    return area;
}

QPolygonF GraficadorAeropuerto::poligonoHorario(const QPolygonF& poli)
{
    QPolygonF poliHorario;
    if (areaPoligono(poli) > 0){
        for (int i = poli.size()-1; i >= 0; i--){
            poliHorario.append(poli.at(i));
        }
    }
    else {
        poliHorario = poli;
    }
    return poliHorario;
}
