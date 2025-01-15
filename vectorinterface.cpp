#include "vectorinterface.h"

VectorInterface::VectorInterface()
    : portHandle(0), accessMask(0), driverOpened(false) {}

VectorInterface::~VectorInterface() {
    closeDriver();
}

bool VectorInterface::openDriver() {
    XLstatus status = xlOpenDriver();
    if (status != XL_SUCCESS) {
        qDebug() << "Failed to open Vector driver: " << xlGetErrorString(status);
        return false;
    }
    driverOpened = true;
    qDebug() << "Vector driver opened successfully.";
    return true;
}

bool VectorInterface::closeDriver() {
    if (driverOpened) {
        xlCloseDriver();
        driverOpened = false;
        qDebug() << "Vector driver closed.";
    }
    return true;
}

bool VectorInterface::openChannel(const QString& network) {
    if (!driverOpened) {
        qDebug() << "Driver not opened!";
        return false;
    }

    XLdriverConfig xlDriverConfig;
    memset(&xlDriverConfig, 0, sizeof(XLdriverConfig));
    xlGetDriverConfig(&xlDriverConfig);

    int channelIndex = -1;
    for (unsigned int i = 0; i < xlDriverConfig.channelCount; i++) {
        QString channelName = QString::fromUtf8(xlDriverConfig.channel[i].name);
        if (channelName == network) {
            channelIndex = xlDriverConfig.channel[i].channelIndex;
            accessMask = 1 << channelIndex;
            break;
        }
    }

    if (channelIndex == -1) {
        qDebug() << "Network not found: " << network;
        return false;
    }

    XLstatus status;
    status = xlOpenPort(&portHandle, (char*)"MyApp", accessMask, &accessMask, XL_BUS_TYPE_CAN, XL_INTERFACE_VERSION, 512);
    if (status != XL_SUCCESS) {
        qDebug() << "Failed to open Vector port.";
        return false;
    }

    qDebug() << "Channel opened on network: " << network;
    return true;
}

bool VectorInterface::closeChannel() {
    if (portHandle) {
        xlClosePort(portHandle);
        portHandle = 0;
        qDebug() << "Channel closed.";
        return true;
    }
    return false;
}

bool VectorInterface::startCCPSession() {
    if (!portHandle) {
        qDebug() << "Port not opened!";
        return false;
    }

    unsigned int stationAddress = 0x01;
    unsigned int resourceAccess = 0x02; // Replace with actual CCP flags

    // Call Vector API CCP function (this is an example, modify as needed)
    // XLstatus status = xlCcpConnect(portHandle, stationAddress, resourceAccess);
    // if (status != XL_SUCCESS) {
    //     qDebug() << "Failed to start CCP session.";
    //     return false;
    // }

    qDebug() << "CCP session started.";
    return true;
}

bool VectorInterface::setApplicationConfig(){
    XLstatus status = xlSetApplConfig("Pisnoop_Clone", 1, XL_HWTYPE_VIRTUAL, 0, 0, XL_BUS_TYPE_CAN);
    if (status != XL_SUCCESS) {
        qDebug() << "Failed to set up application config: " << xlGetErrorString(status);
        return false;
    }
    qDebug() << "application configuration set successfully";

    return true;
}
