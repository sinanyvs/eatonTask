#ifndef DEVICEMONITOR_H
#define DEVICEMONITOR_H

#include <QObject>
#include <QVector>
#include <datapack.h>

/**
 * @brief The DeviceMonitor class
 * This class holds updated unique device
 * measurements and device id. Will be
 * created one for every monitored device
 */
class DeviceMonitor : public QObject
{
    Q_OBJECT

public:
    explicit DeviceMonitor(QObject *parent = nullptr);
    DeviceMonitor(unsigned int id);

    void setData(dataPack_t &newData);
    dataPack_t getData();

private:

    dataPack_t data;

};

#endif // DEVICEMONITOR_H
