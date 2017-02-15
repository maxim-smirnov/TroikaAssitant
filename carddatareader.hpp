#ifndef CARDDATAREADER_HPP
#define CARDDATAREADER_HPP

#include <QObject>
#include <qglobal.h>

#include <logicalaccess/dynlibrary/librarymanager.hpp>
#include <logicalaccess/readerproviders/readerconfiguration.hpp>
#include <logicalaccess/cards/chip.hpp>

#include <logicalaccess/plugins/cards/mifare/mifarechip.hpp>
#include <logicalaccess/services/storage/storagecardservice.hpp>
#include <logicalaccess/plugins/cards/mifare/mifarelocation.hpp>

class cardDataReader : public QObject
{
    Q_OBJECT
private:
    std::shared_ptr<logicalaccess::Chip> chip_;
    std::shared_ptr<logicalaccess::StorageCardService> storage_;

    std::shared_ptr<logicalaccess::MifareLocation> mifareLocation_;
    std::shared_ptr<logicalaccess::MifareAccessInfo> mifareAccessInfoToUse_;

    std::vector<uint8_t> readDataSector8B0_;
    std::vector<uint8_t> readDataSector8B1_;

public:
    explicit cardDataReader(QObject *parent = 0);
    cardDataReader(std::shared_ptr<logicalaccess::Chip> chip);

    int getBalance();
    long getCardNumber();
    QString getBlockHex(int block);

signals:

};

#endif // CARDDATAREADER_HPP
