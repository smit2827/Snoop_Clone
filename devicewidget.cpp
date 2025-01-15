#include "devicewidget.h"
#include "ecudevice.h"

DeviceWidget::DeviceWidget(EcuDevice* device, QWidget* parent)
    : QWidget(parent),
    device(device),
    nameLabel(new QLabel(device->getName(), this)),
    goOnlineButton(new QPushButton("Go Online", this))
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(goOnlineButton);

    connect(goOnlineButton, &QPushButton::clicked, this, &DeviceWidget::onGoOnlineClicked);
}

void DeviceWidget::onGoOnlineClicked()
{
    // Handle Go Online action
    qDebug() << "Go Online clicked for" << nameLabel->text();
}
