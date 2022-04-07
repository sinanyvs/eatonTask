#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
#include "datapack.h"
#include "receiver\receiver.h"

#define NUMBER_OF_DEVICE    32

/*
 * This class simulates a single device in the field.
 *
 */

class Receiver;

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);

private:
    DataBuffer data;
    QTimer * mTimer;

    void populateMeasurement();
    unsigned int generateRn(int offset = 0, int span = 0);
    void reRollTimer();

signals:

    void txHanlder(QByteArray p);

public slots:
    void deviceTimerEvent();


};

#endif // DEVICE_H
