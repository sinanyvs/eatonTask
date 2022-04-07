#include "rxuihelper.h"

unsigned int RxUiHelper::mValidMessageCount = 0;
unsigned int RxUiHelper::mInvalidMessageCount = 0;
QStringList RxUiHelper::mIdlist;
QStringList RxUiHelper::mVoltageList;
QStringList RxUiHelper::mCurrentList;
unsigned int RxUiHelper::mNumOfDevice = 0;

RxUiHelper::RxUiHelper(QObject *parent) : QObject(parent)
{

}

/**
 * @brief RxUiHelper::addNewDevUiList
 * Puts a new device to related vectors. Every vector member with same index
 * holds the same device data.
 * @param data - data package
 */
void RxUiHelper::addNewDevUiList(dataPack_t &data)
{
    mIdlist.push_back(QString::number(data.devId));
    mVoltageList.push_back(QString::number(data.voltage));
    mCurrentList.push_back(QString::number(data.current));
    mNumOfDevice++;
    emit uiUpdated();
}

/**
 * @brief RxUiHelper::updateUiList
 * Function updates the existing device in the list
 * @param devIndex - index of related device
 * @param p - updated data package
 */
void RxUiHelper::updateUiList(unsigned int devIndex, dataPack_t &p)
{
    if(p.devId == mIdlist.at(devIndex).toUInt())
    {
        mVoltageList.removeAt(devIndex);
        mCurrentList.removeAt(devIndex);
        mVoltageList.insert(devIndex, QString::number(p.voltage));
        mCurrentList.insert(devIndex, QString::number(p.current));
        emit uiUpdated();
    }
}

/**
 * @brief RxUiHelper::increaseValidMessageCount
 * Increases valid message count the print on GUI.
 */
void RxUiHelper::increaseValidMessageCount()
{
    mValidMessageCount++;
    emit messageCountChanged();
}

/**
 * @brief RxUiHelper::increaseInvalidMessageCount
 * Increases valid message count the print on GUI.
 * In this application this function will never be called.
 * In real life data can be corrupted during the transmision.
 */
void RxUiHelper::increaseInvalidMessageCount()
{
    mInvalidMessageCount++;
    emit messageCountChanged();
}
