#include "modeloproxyplataformas.h"

ModeloProxyPlataformas::ModeloProxyPlataformas(QObject *parent)
    : QAbstractProxyModel(parent)
{

}

int ModeloProxyPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
//    return;
}

int ModeloProxyPlataformas::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _END;
}

QVariant ModeloProxyPlataformas::data(const QModelIndex &index, int role) const
{
    qDebug() << index;
    qDebug() << role;
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
