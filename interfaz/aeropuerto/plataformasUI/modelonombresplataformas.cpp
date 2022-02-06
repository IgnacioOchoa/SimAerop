#include "modelonombresplataformas.h"

ModeloNombresPlataformas::ModeloNombresPlataformas(QList<Plataforma> &la, QObject *parent)
    : QAbstractItemModel(parent),
      listaPlataformas(la),
      buffListaPlataformas(la)
{

}

int ModeloNombresPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return buffListaPlataformas.count();
}

int ModeloNombresPlataformas::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _END;
}

QVariant ModeloNombresPlataformas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= buffListaPlataformas.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return buffListaPlataformas.at(index.row()).nombre;
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
    for (int i = 0; i < buffListaPlataformas.count();i++){
        listaPlataformas.append(buffListaPlataformas.at(i));
    }
}
