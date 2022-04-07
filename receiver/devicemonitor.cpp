#include "devicemonitor.h"


DeviceMonitor::DeviceMonitor(QObject *parent) : QObject(parent)
{

}

DeviceMonitor::DeviceMonitor(unsigned int id)
{
    data.devId = id;
}

void DeviceMonitor::setData(dataPack_t &newData)
{
    if(newData.devId == data.devId)                  // double check if correct device is called.
        data = newData;
}

dataPack_t DeviceMonitor::getData()
{
    return data;
}


