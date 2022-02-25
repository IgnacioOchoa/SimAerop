#ifndef MODELOPLATAFORMAS_H
#define MODELOPLATAFORMAS_H

#include <QAbstractTableModel>
#include "modeloverticesplataformas.h"
#include "../../../estructuras-datos/elementosaerop.h"
#include "QItemSelectionModel"

class ModeloPlataformas : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Columns
    {
        E_NOMBRE,
        E_VERTICES,
        _END
    };

    enum CustomRoles
    {
        rolPlataforma = Qt::UserRole
    };

    ModeloPlataformas(QList<Plataforma>& bl, QObject *parent);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sincListas();
    void guardarLista();

    QList<Plataforma> buffListaPlataformas; // CHANCHADA. SE PONE ACÁ PARA QUE SEA ACCESIBLE DESDE DIALOGOPLATAFORMA

private:
    QList<Plataforma> &listaPlataformas;
    //QItemSelectionModel* selectionModel;
    Plataforma  plataformaDefault = Plataforma {"Foo", QVector<QPointF> {{500,500}, {500,450}, {450,450}, {450,500}}};

};
#endif // MODELOPLATAFORMAS_H
