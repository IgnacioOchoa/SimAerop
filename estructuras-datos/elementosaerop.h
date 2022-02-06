#ifndef ELEMENTOSAEROP_H
#define ELEMENTOSAEROP_H

#include <QMetaType>
#include <QList>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>

struct Pista {
    int largo;
    int ancho;
    int orientacion;
    QString cabecera1;
    QString cabecera2;
    bool operator==(const Pista& p){
        return(largo==p.largo && ancho==p.ancho && orientacion==p.orientacion &&
               cabecera1 == p.cabecera1 && cabecera2 == p.cabecera2);
    }
};

inline QDebug operator<<(QDebug stream, const Pista& p)
{
    stream << "Pista" << Qt::endl;
    stream << "Largo: " << p.largo << "m" << Qt::endl;
    stream << "Ancho: " << p.ancho << "m" << Qt::endl;
    stream << "Orientacion: " << p.orientacion << " grados" << Qt::endl;
    stream << "Cabecera 1: " << p.cabecera1 << Qt::endl;
    stream << "Cabecera 2: " << p.cabecera2 << "\n \n";
    return stream;
}

struct Rodaje {
    QString cabecera;
    float posicion;
    float angulo;
    int ancho;
    int largo;
    int radio;
};

struct RodajeParametros {
    const QStringList tiposRodaje = {"Desde pista", "Paralela a pista", "Dos puntos"};
};

inline QDebug operator<<(QDebug stream, const Rodaje& rod)
{
    stream << "Calle rodaje" << Qt::endl;
    stream << "Cabecera: " << rod.cabecera << Qt::endl;
    stream << "Posicion: " << rod.posicion << "m" << Qt::endl;
    stream << "Largo: " << rod.largo << "m" << Qt::endl;
    stream << "Ancho: " << rod.ancho << "m" << Qt::endl;
    stream << "Radio: " << rod.radio << "m" << Qt::endl;
    stream << "Angulo: " << rod.angulo << " grados" << "\n \n";
    return stream;
}

struct Plataforma {
    Plataforma () = default;
    Plataforma (const QString& n, const QPolygonF& l){nombre = n, coordPerimetro = l;}
    QString nombre;
    QPolygonF coordPerimetro;
};

inline QDebug operator<<(QDebug stream, const Plataforma& plat)
{
    stream << "Plataforma" << Qt::endl;
    stream << "Coordenadas perimetro: " << Qt::endl;
    for (int i=0; i<plat.coordPerimetro.size(); i++)
    {
        stream << "Punto " << i << ": x=" << plat.coordPerimetro[i].x() << " ; y="
               << plat.coordPerimetro[i].y() << Qt::endl;
    }
    return stream;
}

Q_DECLARE_METATYPE(Pista);
Q_DECLARE_METATYPE(Rodaje);
Q_DECLARE_METATYPE(Plataforma);

#endif // ELEMENTOSAEROP_H
