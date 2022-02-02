#include "modeloverticesplataformas.h"

ModeloVerticesPlataformas::ModeloVerticesPlataformas(QList<Plataforma>& bl, QObject *parent)
    : QAbstractTableModel(parent),
      buffListaPlataformas(bl)
{

}
