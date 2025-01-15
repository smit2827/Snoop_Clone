#include "newdevicedialog.h"
#include "ui_newdevicedialog.h"

#include "devicemanager.h"
#include <QString>
#include <QStringList>
#include "vxlapi.h"
#include <windows.h>
#include <iostream>

NewDeviceDialog::NewDeviceDialog(QWidget *parent, DeviceManager* manager)
    : QDialog(parent), manager(manager)
    , ui(new Ui::NewDeviceDialog)
{
    ui->setupUi(this);

    // Get the available channels
    QStringList channels = getAvailableChannels();

    // Populate the combo box
    ui->comboBox->addItems(channels);
}

NewDeviceDialog::~NewDeviceDialog()
{
    delete ui;
}


void NewDeviceDialog::on_buttonBox_accepted()
{
    // Collect user input from the dialog
    QString name = ui->lineEditName->text();
    int address = ui->lineEditAddress->text().toInt();
    QString network = ui->comboBox->currentText();

    // Use the passed DeviceManager to add the new device
    if (manager) {
        manager->addEcu(name, address, network);
    }

    accept();  // Close the dialog after adding the device
}

QStringList NewDeviceDialog::getAvailableChannels() {
    QStringList channelList;
    XLstatus status;
    // unsigned int channelCount = 0;
    XLdriverConfig xlDriverConfig;

    // Open the driver
    status = xlOpenDriver();
    if (status != XL_SUCCESS) {
        qDebug() << "Error opening Vector XL driver:" << xlGetErrorString(status);
        return channelList;
    }

    // Get the driver configuration
    status = xlGetDriverConfig(&xlDriverConfig);
    if (status != XL_SUCCESS) {
        std::cerr << "Failed to get driver configuration. Error code: " << status << std::endl;
        xlCloseDriver();
    }

    // Populate the channel list
    for (unsigned int i = 0; i < xlDriverConfig.channelCount; i++) {
        QString channelName = QString::fromUtf8(xlDriverConfig.channel[i].name);
        channelList.append(channelName);
    }

    xlCloseDriver();
    return channelList;
}

