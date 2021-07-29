#ifndef FLOTA_H
#define FLOTA_H

#include "aeronave.h"
#include <QObject>
#include <QDebug>

class Flota : public QObject
{
    Q_OBJECT

public:
    Flota();

public slots:
    void slotCargarFlota();
    void slotGuardarFlota();

private:
    void agregaAeronave(const Aeronave &aeronave);
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
