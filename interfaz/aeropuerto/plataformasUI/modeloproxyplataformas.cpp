#include "modeloproxyplataformas.h"

ModeloProxyPlataformas::ModeloProxyPlataformas(ModeloPlataformas* mod, QObject *parent)
    : QAbstractProxyModel(parent)
{
    setSourceModel(mod);
    currentRow = 0;
    setNumRows();
}

int ModeloProxyPlataformas::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return numRows;
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

    if (role == Qt::DisplayRole)
    {
        QVariant plat = sourceModel()->data(sourceModel()->index(currentRow,0),ModeloPlataformas::rolPlataforma);
        //if (plat.canConvert<Plataforma>()) qInfo() << "Se puede convertir QVariant en Plataforma";
        Plataforma p = qvariant_cast<Plataforma>(plat);
        switch(index.column()) {
        case 0:
            return p.coordPerimetro[index.row()].x();
            break;
        case 1:
            return p.coordPerimetro[index.row()].y();
            break;
        default:
            return QVariant();
            break;
        }
     }
    else
        return QVariant();
}

void ModeloProxyPlataformas::slotPlatCambiada(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected)
    currentRow = selected.indexes()[0].row();
    beginRemoveRows(QModelIndex(),0,numRows-1);
    endRemoveRows();
    setNumRows();
    beginInsertRows(QModelIndex(),0,numRows-1);
    endInsertRows();
}

void ModeloProxyPlataformas::setNumRows()
{
    QVariant var = sourceModel()->data(sourceModel()->index(currentRow,0),ModeloPlataformas::rolPlataforma);
    Plataforma p = qvariant_cast<Plataforma>(var);
    numRows = p.coordPerimetro.size();
}
