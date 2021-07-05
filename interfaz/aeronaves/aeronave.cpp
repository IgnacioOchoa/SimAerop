#include "aeronave.h"

Aeronave::Aeronave(const QString &id,
                   const QString &nombre,
                   const QString &envergadura,
                   const QString &vel_app,
                   const QString &lda,
                   const QString &mtow,
                   const QString &perc)
{
    nId = id;
    nNombre = nombre;
    nEnvergadura = envergadura;
    nVel_app = vel_app;
    nLda = lda;
    nMtow = mtow;
    nPerc = perc;
}

void Aeronave::setId(const QString &id)
{
    nId = id;
}

void Aeronave::setNombre(const QString &nombre)
{
    nNombre = nombre;
}

void Aeronave::setEnvergadura(const QString &envergadura)
{
    nEnvergadura = envergadura;
}

void Aeronave::setVel_app(const QString &vel_app)
{
    nVel_app = vel_app;
}

void Aeronave::setLda(const QString &lda)
{
    nLda = lda;
}

void Aeronave::setMtow(const QString &mtow)
{
    nMtow = mtow;
}

void Aeronave::setPerc(const QString &perc)
{
    nPerc = perc;
}

QString Aeronave::getId() const
{
    return nId;
}

QString Aeronave::getNombre() const
{
    return nNombre;
}

QString Aeronave::getEnvergadura() const
{
    return nEnvergadura;
}

QString Aeronave::getVel_app() const
{
    return nVel_app;
}

QString Aeronave::getLda() const
{
    return nLda;
}

QString Aeronave::getMtow() const
{
    return nMtow;
}

QString Aeronave::getPerc() const
{
    return nPerc;
}
