#ifndef PISTAPARSER_H
#define PISTAPARSER_H

#include "../estructuras-datos/elementosaerop.h"
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QFile>
#include <QDebug>

class PistaParser
{
public:
    void guardarPista(const QString& file, const QList<Pista> &p);
    void guardarRodaje(const QString& file, const QList<Rodaje> &rod);
    void guardarPlataforma(const QString& file,const QList<Plataforma> &plat);
    void guardarEscenario(const QString& file, const QList<Pista>& pista, const QList<Rodaje>& rod,
                          const QList<Plataforma>& plat);

    QList<Pista>  cargarPista(const QString& file);
    QList<Rodaje> cargarRodaje(const QString& file);
    QList<Plataforma> cargarPlataforma(const QString& file);
    void cargarEscenario(const QString& file, QList<Pista>& p, QList<Rodaje>& rod, QList<Plataforma>& plat);

private:
    QJsonDocument documento;
    QVariantMap pista;
    QVariantMap rodaje;
    QVariantMap plataforma;

    QStringList variablesPista = Pista::getParametros();
    QStringList variablesRodaje = Rodaje::getParametros();
    QStringList variablesPlataforma = {"nombre", "coordPerimetro"};

    const Pista pistaError;
    const Rodaje rodajeError;
    const Plataforma plataformaError = {"", QVector<QPointF> {}};

    void escribirPista(const QList<Pista>& pista);
    void escribirRodaje(const QList<Rodaje>& rod);
    void escribirPlataforma(const QList<Plataforma>& plat);

    void guardarArchivo(const QString& file);
    bool cargarArchivo(const QString& file);
};

#endif // PISTAPARSER_H
