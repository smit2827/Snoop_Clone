#ifndef ECUDEVICE_H
#define ECUDEVICE_H

#include <windows.h>
#include "vxlapi.h"
#include "ecudevice.h"
#include <QString>
#include <QDebug>

class EcuDevice
{
public:
    EcuDevice(const QString& name, int slaveAddress, const QString& network);

    // get functions
    QString getName();
    bool goOnline();

private:
    QString name;
    int slaveAddress;
    QString network;
};

#endif // ECUDEVICE_H
