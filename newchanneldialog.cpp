#include "newchanneldialog.h"
#include "ui_newchanneldialog.h"
#include "vxlapi.h"
#include <windows.h>
#include <QPushButton>
#include <iostream>



NewChannelDialog::NewChannelDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewChannelDialog)
{
    ui->setupUi(this);

    // Get the available channels
    QStringList channels = getAvailableChannels();

    // Populate the combo box
    ui->newChannelSelectComboBox->addItems(channels);

    // Handle case when no channels are found
    if (channels.isEmpty()) {
        // Access the OK button in the QDialogButtonBox
        QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
        if (okButton) {
            okButton->setEnabled(false);  // Disable the OK button
        }
    }
}

NewChannelDialog::~NewChannelDialog()
{
    delete ui;
}

QStringList NewChannelDialog::getAvailableChannels() {
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
