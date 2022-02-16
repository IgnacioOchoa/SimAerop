#include "modeloproxyplataformas.h"

ModeloProxyPlataformas::ModeloProxyPlataformas(QObject *parent)
    : QAbstractProxyModel(parent)
{

}

int ModeloProxyPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

int ModeloProxyPlataformas::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _END;
}

QVariant ModeloProxyPlataformas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

//    if (index.row() >= buffListaPlataformas.size())
//        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch(index.column()) {
        case 0:
            return index.row();
            break;
        case 1:
            return index.column();
            break;
        default:
            return QVariant();
            break;
        }
     }
    else
        return QVariant();
}

bool ModeloProxyPlataformas::insertRows(int row, int count, const QModelIndex &parent)
{

}

bool ModeloProxyPlataformas::removeRows(int row, int count, const QModelIndex &parent)
{

}

QModelIndex ModeloProxyPlataformas::mapFromSource(const QModelIndex &sourceIndex) const
{
}

QModelIndex ModeloProxyPlataformas::mapToSource(const QModelIndex &proxyIndex) const
{
}
