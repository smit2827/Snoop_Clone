#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newchanneldialog.h"
#include "newdevicedialog.h"
#include "GoOnlineButtonDelegate.h"
#include "devicewidget.h"
#include "vectorinterface.h"

#include <iostream>
#include <windows.h>
#include "vxlapi.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , deviceManager(new DeviceManager(this))
    , deviceTable(new DeviceTable(this, deviceManager))
{
    ui->setupUi(this);

    connect(deviceManager, &DeviceManager::ecuAdded, this, &MainWindow::onDeviceAdded);
    //ui->deviceTableView->setModel(deviceTable);

    // Set up the GoOnlineButtonDelegate for the appropriate column
    GoOnlineButtonDelegate* delegate = new GoOnlineButtonDelegate(this);
    //ui->deviceTableView->setItemDelegateForColumn(1, delegate); // Assuming column 1 is for the button

    // Connect the delegate's signal to the appropriate slot
    // connect(delegate, &GoOnlineButtonDelegate::buttonClicked, this, &MainWindow::onDeviceGoOnline);

    //connect(deviceManager, &DeviceManager::ecuAdded, deviceTable, &DeviceTable::addDevice);

    VectorInterface vectorInterface;

    XLstatus xlStatus;
    XLdriverConfig xlDriverConfig;

    // Load the driver configuration
    xlStatus = xlOpenDriver();
    if (xlStatus != XL_SUCCESS) {
        std::cerr << "Failed to open XL Driver. Error code: " << xlStatus << std::endl;
    } else {
        std::cout << "XL Driver opened successfully." << std::endl;
    }

    // Get the driver configuration
    xlStatus = xlGetDriverConfig(&xlDriverConfig);
    if (xlStatus != XL_SUCCESS) {
        std::cerr << "Failed to get driver configuration. Error code: " << xlStatus << std::endl;
        xlCloseDriver();
    }

    // Print information about available hardware
    std::cout << "Number of hardware devices: " << xlDriverConfig.channelCount << std::endl;
    for (unsigned int i = 0; i < xlDriverConfig.channelCount; i++) {
        std::cout << "Device " << i << ": " << xlDriverConfig.channel[i].name
                  << " (" << xlDriverConfig.channel[i].serialNumber << ")" << std::endl;
    }

    xlCloseDriver();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Add Channel
void MainWindow::on_pushButton_2_clicked()
{
    NewChannelDialog dialog(this);  // Create the dialog (pass 'this' as parent)
    dialog.exec();  // Show the dialog modally
}

void MainWindow::on_addDeviceButton_clicked()
{
    NewDeviceDialog dialog(this, deviceManager);

    // Show the dialog and check if it's accepted (i.e., user clicked OK)
    if (dialog.exec() == QDialog::Accepted) {
        // Device was added successfully (if needed, update UI or perform other actions)
    }
}

void MainWindow::onDeviceAdded(const QString& name)
{
    // Find the newly added device by name
    const auto& devices = deviceManager->getDevices();
    auto it = std::find_if(devices.begin(), devices.end(), [&name](const std::unique_ptr<EcuDevice>& device) {
        return device->getName() == name;
    });

    if (it != devices.end()) {
        // Create a DeviceWidget and add it to the layout
        auto* widget = new DeviceWidget(it->get(), this);
        ui->deviceVerticalLayout->addWidget(widget);
    }
}


void MainWindow::on_pushButton_clicked()
{
    vectorInterface->setApplicationConfig();
}

