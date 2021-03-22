#ifndef ELEMENTOSAEROP_H
#define ELEMENTOSAEROP_H

#include<QMetaType>

struct Pista {
    int largo;
    int ancho;
    int nroCallesRodajeCab1;
    int nroCallesRodajeCab2;
};

Q_DECLARE_METATYPE(Pista);

#endif // ELEMENTOSAEROP_H
