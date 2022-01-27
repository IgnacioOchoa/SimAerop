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
    return 6;
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
            return buffListaRodajes.at(index.row()).cabecera;
            break;
        case 1:
            return buffListaRodajes.at(index.row()).posicion;
            break;
        case 2:
            return buffListaRodajes.at(index.row()).angulo;
            break;
        case 3:
            return buffListaRodajes.at(index.row()).ancho;
            break;
        case 4:
            return buffListaRodajes.at(index.row()).largo;
            break;
        case 5:
            return buffListaRodajes.at(index.row()).radio;
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
    return QAbstractTableModel::insertRows(row, count, parent);
}

bool ModeloRodajes::removeRows(int row, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::removeRows(row, count, parent);
}

void ModeloRodajes::sincListas()
{
    buffListaRodajes = listaRodajes;
    beginInsertRows(QModelIndex(),0,buffListaRodajes.count()-1);
    endInsertRows();
}
