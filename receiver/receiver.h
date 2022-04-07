#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QProcess>
#include <QVector>
#include <QStringList>
#include "datapack.h"
#include "devicemonitor.h"
#include "rxuihelper.h"

/**
 * @brief The Receiver class
 * This class is a bridge between transmitter and
 * devicemonitor class. Receiver part of the software
 * is creating a new DeviceMonitor object to hold the data.
 * Reciever is resposible of creating that objects and putting
 * data into the related object. Also gui updates triggered by
 * this class.
 */

class Receiver : public RxUiHelper
{
    Q_OBJECT

public:

    explicit Receiver(QObject *parent = nullptr);
    ~Receiver();

private:

    static Receiver * mInstance;
    DataBuffer data;
    QVector<DeviceMonitor *> devList;
    void updateDeviceVector(dataPack_t &p);

public slots:

    static void rxHandler(QByteArray p);

signals:

};

#endif // RECEIVER_H
