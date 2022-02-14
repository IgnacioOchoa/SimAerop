#ifndef MODELOPLATAFORMASDELEGATE_H
#define MODELOPLATAFORMASDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>
#include "modelonombresplataformas.h"

class ModeloPlataformasDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ModeloPlataformasDelegate(QObject* parent = nullptr);
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;  
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // MODELOPLATAFORMASDELEGATE_H
