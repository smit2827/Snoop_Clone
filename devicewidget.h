// DeviceWidget.h
#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "ecudevice.h"

class DeviceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceWidget(EcuDevice* device, QWidget* parent = nullptr);

private slots:
    void onGoOnlineClicked();

private:
    EcuDevice* device;
    QLabel* nameLabel;
    QPushButton* goOnlineButton;
};

#endif // DEVICEWIDGET_H
