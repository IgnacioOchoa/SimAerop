#include "modelonombresplataformas.h"

ModeloNombresPlataformas::ModeloNombresPlataformas(const QList<Plataforma>& lstPlataformas, QObject *parent)
    : QAbstractListModel(parent),
      listaPlataformas(lstPlataformas),
      buffListaPlataformas(lstPlataformas)
{

}

int ModeloNombresPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return buffListaPlataformas.count();
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

Qt::ItemFlags ModeloNombresPlataformas::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
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
    if(listaPlataformas.count() > buffListaPlataformas.count()) {
        int diff = listaPlataformas.count() - buffListaPlataformas.count();
        beginInsertRows(QModelIndex(),buffListaPlataformas.count(), buffListaPlataformas.count() + diff - 1);
        buffListaPlataformas = listaPlataformas;
        endInsertRows();
    }
}
