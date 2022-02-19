#ifndef ELEMENTOSAEROP_H
#define ELEMENTOSAEROP_H

#include <QMetaType>
#include <QList>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>

struct Pista {
    Pista(QString nombre = "---",
          int largo = 0,
          int ancho = 0,
          int orientacion = 0,
          QPointF puntoOrigen = QPointF())
    {
        this->nombre = nombre;
        this->largo = largo;
        this->ancho = ancho;
        this->orientacion = orientacion;
        this->puntoOrigen = puntoOrigen;
    }
    QString nombre;
    int largo;
    int ancho;
    int orientacion;
    QPointF puntoOrigen;
    static QStringList getParametros() {return {"nombre", "largo", "ancho", "orientacion", "puntoOrigen"};}
    bool operator==(const Pista& p){
        return(nombre==p.nombre && largo==p.largo && ancho==p.ancho && orientacion==p.orientacion &&
               puntoOrigen==p.puntoOrigen);
    }
    QString getCabecera1() const {
        int nro = (90 - orientacion)/10;
        if (nro < 0) nro += 36;
        if (nro == 0) nro = 36;
        return QString::number(nro).rightJustified(2,'0');
    }
    QString getCabecera2() const {
        int nro = (90 - orientacion)/10;
        if (nro < 0) nro += 36;
        if (nro == 0) nro = 36;
        nro = (nro + 18) % 36;
        return QString::number(nro).rightJustified(2,'0');
    }
};

inline QDebug operator<<(QDebug stream, const Pista& p)
{
    stream << "Pista" << Qt::endl;
    stream << "Nombre: " << p.nombre << Qt::endl;
    stream << "Largo: " << p.largo << "m" << Qt::endl;
    stream << "Ancho: " << p.ancho << "m" << Qt::endl;
    stream << "Orientacion: " << p.orientacion << " grados" << Qt::endl;
    return stream;
}

struct Rodaje {
    Rodaje(QString nombre = "---",
           QPointF coordInicio = QPointF(),
           QPointF coordFinal = QPointF(),
           int ancho = 0,
           QString grupo = QString(),
           QString pista = QString(),
           QString tipo = QString(),
           int radio1 = 0,
           int radio2 = 0,
           int radio3 = 0,
           int radio4 = 0)
    {
        this->nombre = nombre;
        this->coordInicio = coordInicio;
        this->coordFinal = coordFinal;
        this->ancho = ancho;
        this->grupo = grupo;
        this->pista = pista;
        this->tipo = tipo;
        this->radio1 = radio1; this->radio2 = radio2;
        this->radio3 = radio3; this->radio4 = radio4;
    }
    QString nombre;
    QPointF coordInicio;
    QPointF coordFinal;
    int ancho;
    QString grupo;
    QString pista;
    QString tipo;
    int radio1;
    int radio2;
    int radio3;
    int radio4;
    static QStringList getParametros() { return {"nombre", "coordInicio", "coordFinal", "ancho", "grupo", "pista",
                                   "tipo", "radio1", "radio2", "radio3", "radio4"}; }
};

struct RodajeParametros {
    const QStringList tiposRodaje = {"Rodaje desde pista", "Rodaje paralelo a pista", "Rodaje entre dos puntos"};
};

inline QDebug operator<<(QDebug stream, const Rodaje& rod)
{
    stream << "Calle rodaje" << Qt::endl;
    stream << "Nombre: " << rod.nombre << Qt::endl;
    stream << "Coord Inicio: " << rod.coordInicio;
    stream << "Coord Final: " << rod.coordFinal;
    stream << "Grupo: " << rod.grupo << Qt::endl;
    stream << "Pista: " << rod.pista << Qt::endl;
    stream << "Tipo: " << rod.tipo << Qt::endl;
    stream << "Radio1: " << rod.radio1 << " m" << Qt::endl;
    stream << "Radio2: " << rod.radio2 << " m" << Qt::endl;
    stream << "Radio3: " << rod.radio3 << " m" << Qt::endl;
    stream << "Radio4: " << rod.radio4 << " m" << Qt::endl;
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
