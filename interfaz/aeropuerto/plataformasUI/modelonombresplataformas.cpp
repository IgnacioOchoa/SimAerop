#include "modelonombresplataformas.h"

ModeloNombresPlataformas::ModeloNombresPlataformas(QList<Plataforma> &la, QObject *parent)
    : QAbstractItemModel(parent),
      listaPlataformas(la),
      buffListaPlataformas(la),
      ultimoSeleccionado(-1)
{

}

int ModeloNombresPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug() << buffListaPlataformas.count();
    return buffListaPlataformas.count();
}

int ModeloNombresPlataformas::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _END;
}

QVariant ModeloNombresPlataformas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if (index.row() >= buffListaPlataformas.size()){
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        return buffListaPlataformas.at(index.row()).nombre;
    }
    if (role == tablaRol)
    {
        const auto& poligono = buffListaPlataformas.at(ultimoSeleccionado).coordPerimetro;
        switch (index.column()) {
        case E_POS_X:
            qDebug() << "Pos X";
            return poligono.at(index.row()).x();
            break;
        case E_POS_Y:
            qDebug() << "Pos Y";
            return poligono.at(index.row()).y();
            break;
        default:
            break;
        }
    }
    else
        return QVariant();
}

bool ModeloNombresPlataformas::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    beginInsertRows(QModelIndex(), row+1, row+1);
    buffListaPlataformas.insert(row+1, plataformaDefault);
    endInsertRows();
    return true;
}

bool ModeloNombresPlataformas::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    if (buffListaPlataformas.count() == 0) return true;
    beginRemoveRows(QModelIndex(), row, row);
    buffListaPlataformas.removeAt(row);
    endRemoveRows();
    return true;
}

void ModeloNombresPlataformas::sincListas()
{
    beginInsertRows(QModelIndex(),0, buffListaPlataformas.count() - 1);
    buffListaPlataformas = listaPlataformas;
    endInsertRows();
}

void ModeloNombresPlataformas::guardarLista()
{
    listaPlataformas.clear();
    listaPlataformas = buffListaPlataformas;
}

void ModeloNombresPlataformas::sloSeleccionCambiada(const QItemSelection& itemSeleccion, const QItemSelection& itemDeseleccion)
{
    ultimoSeleccionado = itemSeleccion.indexes()[0].row();
    qDebug() << "Ultimo Seleccionado" << ultimoSeleccionado;
}
