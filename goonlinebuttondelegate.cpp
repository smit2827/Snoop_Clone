#include "GoOnlineButtonDelegate.h"

#include <QPainter>
#include <QApplication>

GoOnlineButtonDelegate::GoOnlineButtonDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

QWidget* GoOnlineButtonDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QPushButton* button = new QPushButton("Go Online", parent);

    // Emit a signal with the row index when the button is clicked
    QObject::connect(button, &QPushButton::clicked, [index, this]() {
        emit buttonClicked(index.row());
    });

    return button;
}

void GoOnlineButtonDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    // No data to set for the button
}

void GoOnlineButtonDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    // No data is stored in the model for the button
}

void GoOnlineButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // First, call the base class to handle default rendering (e.g., background, borders, etc.)
    QStyledItemDelegate::paint(painter, option, index);

    // Only paint the button in the second column (index 1)
    if (index.column() == 1) {
        // Create a rectangle for the button, adjusting the positioning inside the cell
        QRect buttonRect = option.rect.adjusted(option.rect.width() - 80, 5, -5, -5);

        // Create a QStyleOptionButton for the button, which describes the button's properties
        QStyleOptionButton buttonOption;
        buttonOption.rect = buttonRect;
        buttonOption.text = "Go Online"; // Set button label
        buttonOption.state = QStyle::State_Enabled; // Button is enabled

        // Get the widget's style (this ensures the button looks consistent with the rest of the UI)
        QStyle* style = option.widget ? option.widget->style() : QApplication::style();

        // Use QStyle to draw the button with the specified option
        style->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
    }
}
