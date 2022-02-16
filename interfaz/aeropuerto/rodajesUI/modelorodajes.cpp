#include "modelorodajes.h"

ModeloRodajes::ModeloRodajes(const QList<Rodaje>& lstRodaje, QObject *parent)
    : QAbstractTableModel(parent),
      listaRodajes(lstRodaje),
      buffListaRodajes(lstRodaje)
{

}

int ModeloRodajes::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listaHeaders.size();
}

int ModeloRodajes::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return buffListaRodajes.count();
}

QVariant ModeloRodajes::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= buffListaRodajes.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch(index.column()) {
        case 0:
            return buffListaRodajes.at(index.row()).nombre;
            break;
        case 1:
            return buffListaRodajes.at(index.row()).grupo;
            break;
        case 2:
            return buffListaRodajes.at(index.row()).pista;
            break;
        case 3:
            return buffListaRodajes.at(index.row()).tipo;
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
        return QVariant();
}

QVariant ModeloRodajes::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return listaHeaders[section];
    else
        return QVariant();
}

Qt::ItemFlags ModeloRodajes::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

bool ModeloRodajes::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    beginInsertRows(QModelIndex(), row+1, row+1);
    buffListaRodajes.insert(row+1, rodajeDefault);
    endInsertRows();
    return true;
}

bool ModeloRodajes::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    if (buffListaRodajes.count() == 0) return true;
    beginRemoveRows(QModelIndex(), row, row);
    buffListaRodajes.removeAt(row);
    endRemoveRows();
    return true;
}

void ModeloRodajes::sincListas()
{
    if(listaRodajes.count() > buffListaRodajes.count()) {
        int diff = listaRodajes.count() - buffListaRodajes.count();
        beginInsertRows(QModelIndex(),buffListaRodajes.count(), buffListaRodajes.count() + diff - 1);
        buffListaRodajes = listaRodajes;
        endInsertRows();
    }
}

void ModeloRodajes::setCabecerasActivas(const QString &c1, const QString &c2)
{
//    cabActiva1 = c1;
//    cabActiva2 = c2;
//    rodajeDefault.cabecera = c1;
}
