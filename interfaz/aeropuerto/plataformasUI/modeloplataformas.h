#ifndef MODELOPLATAFORMAS_H
#define MODELOPLATAFORMAS_H

#include <QAbstractTableModel>

class modeloPlataformas : public QAbstractListModel
{
    Q_OBJECT

public:
    modeloPlataformas(const QStringList &ln, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    private:
        QStringList stringList;
};

#endif // MODELOPLATAFORMAS_H
