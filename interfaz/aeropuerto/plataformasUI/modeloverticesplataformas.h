#ifndef MODELOVERTICESPLATAFORMAS_H
#define MODELOVERTICESPLATAFORMAS_H

#include <QAbstractTableModel>
#include "../../../estructuras-datos/elementosaerop.h"

class ModeloVerticesPlataformas : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModeloVerticesPlataformas(QList<Plataforma>& bl, QObject *parent);

private:
    QList<Plataforma>& buffListaPlataformas;
};

#endif // MODELOVERTICESPLATAFORMAS_H
