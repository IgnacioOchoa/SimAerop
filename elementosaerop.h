#ifndef ELEMENTOSAEROP_H
#define ELEMENTOSAEROP_H

#include <QMetaType>
#include <QList>
#include <QPointF>
#include <QDebug>

struct Pista {
    int largo;
    int ancho;
    int orientacion;
    QString cabecera1;
    QString cabecera2;
};

inline QDebug operator<<(QDebug stream, const Pista& p)
{
    stream << "Pista" << endl;
    stream << "Largo: " << p.largo << "m" << endl;
    stream << "Ancho: " << p.ancho << "m" << endl;
    stream << "Orientacion: " << p.orientacion << " grados" << endl;
    stream << "Cabecera 1: " << p.cabecera1 << endl;
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

inline QDebug operator<<(QDebug stream, const Rodaje& rod)
{
    stream << "Calle rodaje" << endl;
    stream << "Cabecera: " << rod.cabecera << endl;
    stream << "Posicion: " << rod.posicion << "m" << endl;
    stream << "Largo: " << rod.largo << "m" << endl;
    stream << "Ancho: " << rod.ancho << "m" << endl;
    stream << "Radio: " << rod.radio << "m" << endl;
    stream << "Angulo: " << rod.angulo << " grados" << "\n \n";
    return stream;
}

struct Plataforma {
    QList<QPointF> coordPerimetro;
    QList<QPointF> coordParking;
};

inline QDebug operator<<(QDebug stream, const Plataforma& plat)
{
    stream << "Plataforma" << endl;
    stream << "Coordenadas perimetro: " << endl;
    for (int i=0; i<plat.coordPerimetro.size(); i++)
    {
        stream << "Punto " << i << ": x=" << plat.coordPerimetro[i].x() << " ; y="
               << plat.coordPerimetro[i].y() << endl;
    }
    stream << "Coordenadas puntos de parking: " << endl;
    for (int i=0; i<plat.coordParking.size(); i++)
    {
        stream << "Punto " << i << ": x=" << plat.coordParking[i].x() << " ; y="
               << plat.coordParking[i].y() << endl;
    }

    return stream;
}

Q_DECLARE_METATYPE(Pista);

#endif // ELEMENTOSAEROP_H
