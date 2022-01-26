#ifndef MODELOPISTAS_H
#define MODELOPISTAS_H

#include <QAbstractTableModel>

class modeloPistas : public QAbstractTableModel
{
    Q_OBJECT

public:
    modeloPistas(QObject *parent);
};

#endif // MODELOPISTAS_H
