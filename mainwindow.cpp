#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newchanneldialog.h"

#include <iostream>
#include <windows.h>
#include "vxlapi.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

