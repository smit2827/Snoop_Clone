#include "devicetable.h"
#include "devicemanager.h"
#include "ecudevice.h"

DeviceTable::DeviceTable(QObject *parent, DeviceManager* manager)
    : QAbstractTableModel(parent), manager(manager)
{}

QVariant DeviceTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0)
            return "Device Name";
        else if (section == 1)
            return "Actions";
    }
    return QVariant();
}

int DeviceTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return manager ? manager->getDevices().size() : 0;
}

int DeviceTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2; // Displaying only the device name for now
}

QVariant DeviceTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !manager)
        return QVariant();

    const auto& devices = manager->getDevices(); // Get the vector of unique_ptr<EcuDevice>
    if (index.row() < 0 || index.row() >= static_cast<int>(devices.size()))
        return QVariant();

    const auto& device = devices[index.row()]; // Access the unique_ptr
    if (!device) // Safety check for null unique_ptr
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            // First column: Device name
            return device->getName();
        }
        if (index.column() == 1) {
            // Second column: Return placeholder for button (optional)
            return "_";
        }
    }

    return QVariant();
}

void DeviceTable::addDevice()
{
    if (!manager)
        return;

    // Get the current number of rows (new row will be at the end)
    int row = rowCount(); // This gives us the current number of devices

    // Notify the model about the insertion of a new row at the end
    beginInsertRows(QModelIndex(), row, row);  // Begin inserting a new row
    endInsertRows();  // Finish the insertion

    // Optionally, refresh the table's data if needed
    // This can be done by calling dataChanged() for the entire range
}
