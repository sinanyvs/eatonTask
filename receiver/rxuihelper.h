#ifndef RXUIHELPER_H
#define RXUIHELPER_H

#include <QObject>
#include "devicemonitor.h"
#include "datapack.h"

/**
 * @brief The RxUiHelper class
 * only purpose of this class is abstracting User interface.
 * Gets data from actual receiver and holds it to update ui.
 */

class RxUiHelper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList idList MEMBER mIdlist NOTIFY uiUpdated);
    Q_PROPERTY(QStringList voltageList MEMBER mVoltageList NOTIFY uiUpdated);
    Q_PROPERTY(QStringList currentList MEMBER mCurrentList NOTIFY uiUpdated);
    Q_PROPERTY(unsigned int numOfDevice MEMBER mNumOfDevice NOTIFY uiUpdated);
    Q_PROPERTY(unsigned int validMessageCount MEMBER mValidMessageCount NOTIFY messageCountChanged);
    Q_PROPERTY(unsigned int invalidMessageCount MEMBER mInvalidMessageCount NOTIFY messageCountChanged);

public:
    explicit RxUiHelper(QObject *parent = nullptr);


protected:
    static QStringList mIdlist;
    static QStringList mVoltageList;
    static QStringList mCurrentList;
    static unsigned int mValidMessageCount;
    static unsigned int mInvalidMessageCount;
    static unsigned int mNumOfDevice;

    void addNewDevUiList(dataPack_t &data);
    void updateUiList(unsigned int devIndex, dataPack_t &p);
    void increaseValidMessageCount();
    void increaseInvalidMessageCount();

signals:
    void uiUpdated();
    void messageCountChanged();
};

#endif // RXUIHELPER_H
