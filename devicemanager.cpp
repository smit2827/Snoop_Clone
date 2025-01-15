#include "devicemanager.h"
#include <QString>
#include "ecudevice.h"

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent) {}

void DeviceManager::addEcu(const QString& name, int slaveAddress, const QString& network){
    // Create a new ecu and add it to the list
    devices.push_back(std::make_unique<EcuDevice>(name, slaveAddress, network));

    emit ecuAdded(name);
}

// Get all devices
const std::vector<std::unique_ptr<EcuDevice>>& DeviceManager::getDevices() const {
    return devices;
}
