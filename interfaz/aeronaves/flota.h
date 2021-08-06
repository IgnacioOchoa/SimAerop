#ifndef FLOTA_H
#define FLOTA_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QXmlStreamReader>
#include <QList>
#include <QMessageBox>

#include "aeronave.h"

class Flota : public QObject
{
    Q_OBJECT

public:
    Flota(const QString &nombre = "",
          const QList<Aeronave> &listaAeronaves = QList<Aeronave>());

    void setNombre(const QString &nombre);
    void cargadorFlota(QFile &f);
    void guardadorFlota(QString &filename);
    QString getNombre() const;
    const QList<Aeronave>& getListaFlota() const {return nListaAeronaves;}

private:
    void agregaAeronave(const Aeronave &aeronave);

    QString nNombre;
    QList<Aeronave> nListaAeronaves;
    enum{
        ID,
        NOMBRE,
        ENVERGADURA,
        APPSPD,
        LDA,
        MTOW,
        PORCENTAJE,
    };
};

#endif // FLOTA_H
