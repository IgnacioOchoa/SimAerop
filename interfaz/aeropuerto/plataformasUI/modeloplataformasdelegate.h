#ifndef MODELOPLATAFORMASDELEGATE_H
#define MODELOPLATAFORMASDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QLineEdit>
#include "modelonombresplataformas.h"

class ModeloPlataformasDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ModeloPlataformasDelegate();
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MODELOPLATAFORMASDELEGATE_H
