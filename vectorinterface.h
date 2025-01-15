#ifndef VECTORINTERFACE_H
#define VECTORINTERFACE_H

#include <windows.h>
#include "vxlapi.h"
#include <QString>
#include <QDebug>

class VectorInterface {
public:
    VectorInterface();
    ~VectorInterface();

    bool openDriver();             // Opens the Vector driver
    bool closeDriver();            // Closes the Vector driver
    bool openChannel(const QString& network);  // Opens a specific CAN channel
    bool closeChannel();           // Closes the active CAN channel
    bool startCCPSession();        // Starts a CCP session
    bool sendMessage();            // Sends a CAN message (Example function)
    bool setApplicationConfig();   // Adds this application to the Vector Hardware Configuration

private:
    XLportHandle portHandle;       // Handle for the Vector hardware
    XLaccess accessMask;           // Bitmask for active channels
    bool driverOpened;             // Flag to track driver state
};

#endif // VECTORINTERFACE_H

