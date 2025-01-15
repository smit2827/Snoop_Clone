#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <vector>
#include <memory>
#include "EcuDevice.h"

class DeviceManager : public QObject
{
    Q_OBJECT

public:
    explicit DeviceManager(QObject* parent = nullptr);

    void addEcu(const QString& name, int slaveAddress, const QString& network);

    // Get all devices
    const std::vector<std::unique_ptr<EcuDevice>>& getDevices() const;

signals:
    void ecuAdded(const QString& name);

private:
    std::vector<std::unique_ptr<EcuDevice>> devices;
};

#endif // DEVICEMANAGER_H
