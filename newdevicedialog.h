#ifndef NEWDEVICEDIALOG_H
#define NEWDEVICEDIALOG_H

#include <QDialog>
#include "devicemanager.h"
#include <windows.h>
#include "vxlapi.h"

namespace Ui {
class NewDeviceDialog;
}

class NewDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDeviceDialog(QWidget *parent = nullptr, DeviceManager* manager = nullptr);
    ~NewDeviceDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewDeviceDialog *ui;
    DeviceManager* manager;

    QStringList getAvailableChannels();
};

#endif // NEWDEVICEDIALOG_H
