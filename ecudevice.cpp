#include <windows.h>
#include "vxlapi.h"
#include "ecudevice.h"
#include <QString>
#include <QDebug>

EcuDevice::EcuDevice(const QString& name, int slaveAddress, const QString& network)
    : name(name), slaveAddress(slaveAddress), network(network)
{}

QString EcuDevice::getName(){
    return name;
}

bool EcuDevice::goOnline()
{
    // Step 1: Open the Vector hardware channel
    XLstatus status = xlOpenDriver();
    if (status != XL_SUCCESS) {
        qDebug() << "Failed to open Vector hardware driver: " << xlGetErrorString(status);
        return false;
    }

    // Step 2: Retrieve the hardware configuration
    XLdriverConfig xlDriverConfig;
    memset(&xlDriverConfig, 0, sizeof(XLdriverConfig));
    xlGetDriverConfig(&xlDriverConfig);

    // Step 3: Find the channel corresponding to the stored network name
    int channelIndex = -1;
    for (unsigned int i = 0; i < xlDriverConfig.channelCount; i++) {
        QString channelName = QString::fromUtf8(xlDriverConfig.channel[i].name);
        if (channelName == this->network) {
            channelIndex = xlDriverConfig.channel[i].channelIndex;
            break;
        }
    }

    if (channelIndex == -1) {
        qDebug() << "Network not found: " << this->network;
        xlCloseDriver();
        return false;
    }

    // Step 4: Open the corresponding channel
    XLportHandle portHandle = 0;
    // char appName[] = "MyApp";
    XLaccess permissionMask = 0;
    unsigned int rxBufferSize = 1024; // Example buffer size

    status = xlOpenPort(
        &portHandle,
        const_cast<char*>("MyApp"),
        1 << channelIndex,
        &permissionMask,
        rxBufferSize,
        XL_BUS_TYPE_CAN,
        XL_INTERFACE_VERSION
        );

    if (status != XL_SUCCESS) {
        qDebug() << "Failed to open Vector hardware port for channel: " << channelIndex;
        xlCloseDriver();
        return false;
    }

    // Step 5: Start a CCP session
    // CCPStationAddress stationAddress = 0x01; // Example station address
    // CCPResourceAccess resourceAccess = CCP_ACCESS_CALIBRATION | CCP_ACCESS_DAQ;

    // status = xlCcpConnect(portHandle, stationAddress, resourceAccess);
    // if (status != XL_SUCCESS) {
    //     qDebug() << "Failed to initiate CCP session: " << xlGetErrorString(status);
    //     xlClosePort(portHandle);
    //     xlCloseDriver();
    //     return false;
    // }

    // qDebug() << "CCP session started successfully on network:" << this->network;

    // // Store the port handle for future use
    // this->ccpPortHandle = portHandle;

    // qDebug() << "CCP session started successfully.";

    // // Step 5: Keep track of the session for future interactions
    // this->ccpPortHandle = portHandle; // Store handle in a class member for further use

    return true;
}
