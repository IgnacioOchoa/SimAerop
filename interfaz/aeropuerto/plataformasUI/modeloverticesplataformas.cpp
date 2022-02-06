#include "modeloverticesplataformas.h"

ModeloVerticesPlataformas::ModeloVerticesPlataformas(const QModelIndex& index, QObject *parent)
    : QAbstractItemModel(parent)
//    plataforma()
{

}

int ModeloVerticesPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return plataforma->coordPerimetro.count();
}

int ModeloVerticesPlataformas::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _END;
}

QVariant ModeloVerticesPlataformas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= plataforma->coordPerimetro.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        const auto& vertice = plataforma->coordPerimetro.at(index.row());
        switch (index.column()) {
        case E_POS_X:
            return vertice.x();
        case E_POS_Y:
            return vertice.y();
        }
    }
    else
        return QVariant();
}
bool ModeloVerticesPlataformas::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    beginInsertRows(QModelIndex(), row+1, row+1);
    plataforma->coordPerimetro.insert(row+1, puntoDefault);
    endInsertRows();
    return true;
}

bool ModeloVerticesPlataformas::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    if (plataforma->coordPerimetro.count() == 0) return true;
    beginRemoveRows(QModelIndex(), row, row);
    plataforma->coordPerimetro.removeAt(row);
    endRemoveRows();
    return true;
}
