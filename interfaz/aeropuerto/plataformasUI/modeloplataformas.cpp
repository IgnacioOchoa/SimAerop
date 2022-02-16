#include "modeloplataformas.h"

ModeloPlataformas::ModeloPlataformas(QList<Plataforma> &la, QObject *parent)
    : QAbstractTableModel(parent),
      listaPlataformas(la),
      buffListaPlataformas(la)
{

}

int ModeloPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return buffListaPlataformas.count();
}

int ModeloPlataformas::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _END;
}

QVariant ModeloPlataformas::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= buffListaPlataformas.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        const auto& plataforma = buffListaPlataformas.at(index.row());
        switch(index.column()) {
        case 0:
            return plataforma.nombre;
            break;
        case 1:
            return "Vertice";
            break;
        default:
            return QVariant();
            break;
        }
     }
    else
        return QVariant();
}

bool ModeloPlataformas::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    beginInsertRows(QModelIndex(), row+1, row+1);
    buffListaPlataformas.insert(row+1, plataformaDefault);
    endInsertRows();
    return true;
}

bool ModeloPlataformas::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(count);
    if (buffListaPlataformas.count() == 0) return true;
    beginRemoveRows(QModelIndex(), row, row);
    buffListaPlataformas.removeAt(row);
    endRemoveRows();
    return true;
}

void ModeloPlataformas::sincListas()
{
    buffListaPlataformas.clear();
    beginInsertRows(QModelIndex(),0, listaPlataformas.count() - 1);
    buffListaPlataformas = listaPlataformas;
    endInsertRows();
}

void ModeloPlataformas::guardarLista()
{
    listaPlataformas.clear();
    for (int i = 0; i < buffListaPlataformas.count();i++){
        listaPlataformas.append(buffListaPlataformas.at(i));
    }
}
