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
    PistaParser();

    void guardarPista(const QString& file, const Pista &p);
    void guardarRodaje(const QString& file, const QList<Rodaje> &rod);
    void guardarPlataforma(const QString& file,const QList<Plataforma> &plat);
    void guardarEscenario(const QString& file,const Pista& pista, const QList<Rodaje>& rod,
                          const QList<Plataforma>& plat);

    Pista cargarPista(const QString& file);
    QList<Rodaje> cargarRodaje(const QString& file);
    QList<Plataforma> cargarPlataforma(const QString& file);
    void cargarEscenario(const QString& file, Pista& p, QList<Rodaje>& rod, QList<Plataforma>& plat);

private:
    QJsonDocument documento;
    QVariantMap pista;
    QVariantMap rodaje;
    QVariantMap plataforma;
    QString archivo;

    QStringList variablesPista = {"largo", "ancho", "cabecera1", "cabecera2", "orientacion"};
    QStringList variablesRodaje = {"cabecera","posicion","angulo","ancho","largo","radio"};
    QStringList variablesPlataforma = {"nombre", "coordPerimetro"};

    void parsearPista(const Pista& pista);
    void parsearRodaje(const QList<Rodaje>& rod);
    void parsearPlataforma(const QList<Plataforma>& plat);

    void guardar(const QString& file);
    bool cargar(const QString& file);
};

#endif // PISTAPARSER_H
