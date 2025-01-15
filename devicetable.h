#ifndef DEVICETABLE_H
#define DEVICETABLE_H

#include <QAbstractTableModel>

#include "devicemanager.h"

class DeviceTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DeviceTable(QObject *parent = nullptr, DeviceManager* manager = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addDevice();

private:
    DeviceManager* manager;
};

#endif // DEVICETABLE_H
