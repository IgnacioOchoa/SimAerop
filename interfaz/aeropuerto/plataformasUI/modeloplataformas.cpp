#include "modeloplataformas.h"


modeloPlataformas::modeloPlataformas(const QStringList &ln, QObject *parent)
    : QAbstractListModel(parent), stringList(ln) {}

int modeloPlataformas::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}

QVariant modeloPlataformas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return QVariant();
}
