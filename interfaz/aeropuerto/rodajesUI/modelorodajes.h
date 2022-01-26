#ifndef MODELORODAJES_H
#define MODELORODAJES_H

#include <QAbstractTableModel>

class modeloRodajes : public QAbstractTableModel
{
    Q_OBJECT

public:
    modeloRodajes(QObject *parent);
};

#endif // MODELORODAJES_H
