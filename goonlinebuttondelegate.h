#ifndef GOONLINEBUTTONDELEGATE_H
#define GOONLINEBUTTONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QPainter>
#include <QWidget>

class GoOnlineButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit GoOnlineButtonDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

signals:
    void buttonClicked(int row) const; // Signal emitted when the button is clicked
};

#endif // GOONLINEBUTTONDELEGATE_H

