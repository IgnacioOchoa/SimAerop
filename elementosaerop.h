#ifndef ELEMENTOSAEROP_H
#define ELEMENTOSAEROP_H

#include <QMetaType>
#include <QList>
#include <QPointF>

struct Pista {
    int largo;
    int ancho;
    int orientacion;
    QString cabecera1;
    QString cabecera2;
};

struct Rodaje {
    QString cabecera;
    float posicion;
    float angulo;
    int ancho;
    int largo;
    int radio;
};

struct Plataforma {
    QList<QPointF> coordPerimetro;
    QList<QPointF> coordParking;
};

Q_DECLARE_METATYPE(Pista);

#endif // ELEMENTOSAEROP_H
