#include "device.h"
#include <QDebug>
#include <QDataStream>

/**
 * @brief Device::Device
 * Generates a pseudo random device id and connects to receivers
 * receive event. timer is used for the simulate measurements
 * changed event. This timer interval is also generated randomly.
 *
 */
Device::Device(QObject *parent) : QObject(parent)
{
    data.mDataPack.devId = generateRn();

    connect(this, &Device::txHanlder, &Receiver::rxHandler);

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &Device::deviceTimerEvent);
    mTimer->setSingleShot(true);
    reRollTimer();
}

/**
 * @brief Generates a voltage measurement between 210 and 230
 *  and current measurement between 5 and 15
 */
void Device::populateMeasurement()
{
    data.mDataPack.voltage  = generateRn(210, 20);
    data.mDataPack.current = generateRn(5, 10);
}

/**
 * @brief Device::generateRn
 * generates a pseudo random unsignedd integer number with
 * offset and span value
 * @param offset - min value
 * @param span - max value is offset + span
 * @return pseudo random unsigned integer
 */
unsigned int Device::generateRn(int offset, int span)
{
    unsigned int result;
    unsigned int rn = QRandomGenerator::global()->generate();

    if(span == 0)
    {
        result = rn;
    } else {
        result = (rn % span) + offset;
    }

    return result;
}

/**
 * @brief Device::reRollTimer
 * generates a random interval and starts the singleshot timer
 * again
 */
void Device::reRollTimer()
{
    mTimer->setInterval(generateRn(8000, 8000));
    mTimer->start();
}

/**
 * @brief Device::deviceTimerEvent
 * simulates the transmit handler. everytime Program hits here,
 * device generates a new measurement and transmits it to receiver
 * last byte of the data is a checksum value
 * (serializing and checksum process seems meaningless but
 * this function is simulating a communication protocol transmit kicker)
 */
void Device::deviceTimerEvent()
{
    QByteArray arr;

    populateMeasurement();

    arr = data.serializeData();

    emit txHanlder(arr);

    reRollTimer();
}
