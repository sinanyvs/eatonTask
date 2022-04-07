#include "receiver.h"
#include "windows.h"
#include "conio.h"

Receiver * Receiver::mInstance;


#include <QDebug>

Receiver::Receiver(QObject *parent): RxUiHelper(parent)
{
    mInstance = this;
}

Receiver::~Receiver()
{
    QVector<DeviceMonitor *>::iterator it;

    for(it = devList.begin(); it != devList.end(); ++it)
    {
        delete *it;
    }
}

/**
 * @brief Receiver::updateDeviceVector
 * devList is a member vector that holds the uniqe devices.
 * This function updates devList vector if device registered before.
 * If not, creates and appends a new DeviceMonitor object to the end
 * of the devList. This function assumes that every device sends
 * unique device id and it never changes unless it ends up with a memory leak.
 * @param p - datapack
 */
void Receiver::updateDeviceVector(dataPack_t &p)
{
    QVector<DeviceMonitor *>::iterator it;
    bool found = false;

    for(it = devList.begin(); it != devList.end(); ++it)
    {
        if((*it)->getData().devId == p.devId)
        {
            (*it)->setData(p);
            mInstance->updateUiList(it - devList.begin(), p);
            found = true;
        }
    }

    if(!found)
    {
        devList.push_back(new DeviceMonitor(p.devId));
        devList.last()->setData(p);
        mInstance->addNewDevUiList(p);
    }
}

/**
 * @brief Receiver::rxHandler
 *
 * Receive handling event. Gets raw bytes and applies
 * checksum. Counts valid and invalid(wrong checksum)
 * messages.
 * @param p - raw received bytes
 */
void Receiver::rxHandler(QByteArray p)
{
    if(!mInstance->data.deserializeData(p))
    {
        mInstance->increaseInvalidMessageCount();
        return;
    }

    mInstance->increaseValidMessageCount();

    mInstance->updateDeviceVector(mInstance->data.mDataPack);
}

