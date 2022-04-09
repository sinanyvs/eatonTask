#ifndef DATAPACK_H
#define DATAPACK_H
#include <QDataStream>


/**
 * this structure holds all measuring items and device id.
 * pragma pack helps for padding.
 * */
#pragma pack(push, 1)

typedef struct {
    unsigned int voltage;
    unsigned int current;
    unsigned int devId;
}dataPack_t;

#pragma pack(pop)

/**
 * @brief The DataBuffer class
 * This is a simple data buffer class. Holds the data,
 * converts dataPack_t to byte array. Also during serialization
 * calculates the checksum for avoiding data corruption and
 * appends to byte array, vice-versa.
 */
class DataBuffer
{

public:
    dataPack_t mDataPack;

    DataBuffer(){
        memset(&mDataPack, 0, sizeof (dataPack_t));
    }

    /**
     * @brief serializeData
     * Applies a conversion from dataPack_t to byte array.
     * @return
     */
    QByteArray serializeData(){

        char buffer[sizeof (dataPack_t)];
        QByteArray result;

        memcpy(buffer, &mDataPack, sizeof (dataPack_t));

        result = QByteArray(buffer, sizeof (dataPack_t));

        result.append(calcCheckSum(result));

        return result;
    }

    /**
     * @brief deserializeData
     * Applies a conversion from byte array to dataPack_t
     * @param b - byte array with the checksum byte
     * @return - false if checksum fails.
     */
    bool deserializeData(QByteArray b)
    {
        char crc = b[b.size() - 1];
        bool result = true;

        b.remove(b.size() - 1, 1);

        if(crc == calcCheckSum(b))
        {
            dataPack_t * m = reinterpret_cast<dataPack_t*>(b.data());
            this->mDataPack = *m;
        } else {
            result = false;
        }

        return result;
    }

    /**
     * @brief calcCheckSum
     * simple check sum calculator which applies exclusive or
     * to entire array and returns result.
     * @param ar -
     * @return
     */
    char calcCheckSum(QByteArray &ar)
    {
        unsigned int size = sizeof(dataPack_t);
        char result = 0;

        for(unsigned int i = 0; i < size; i++)
        {
            result = result^ar[i];
        }

        return result;
    }
};

#endif // DATAPACK_H
