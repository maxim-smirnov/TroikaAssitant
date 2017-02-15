#include "cardstatus.hpp"

#include <logicalaccess/dynlibrary/librarymanager.hpp>
#include <logicalaccess/readerproviders/readerconfiguration.hpp>
#include <logicalaccess/cards/chip.hpp>

#include <logicalaccess/plugins/cards/mifare/mifarechip.hpp>
#include <logicalaccess/services/storage/storagecardservice.hpp>
#include <logicalaccess/plugins/cards/mifare/mifarelocation.hpp>

cardStatus::cardStatus(QObject *parent) :
    QObject(parent),
    chip_(nullptr)
{

}

void cardStatus::startCardWaiting(std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig){
    if(readerConfig != nullptr){
        if (readerConfig->getReaderUnit()->waitInsertion(0)) {
            if (readerConfig->getReaderUnit()->connect()) {
                chip_ =  readerConfig->getReaderUnit()->getSingleChip();
                std::vector<unsigned char> csn = readerConfig->getReaderUnit()->getNumber(chip_);

                qRegisterMetaType<std::shared_ptr<logicalaccess::Chip>>();
                emit sendCardStatus(chip_, QString::fromStdString(logicalaccess::BufferHelper::getHex(csn)));

                emit sendUID(QString::fromStdString(logicalaccess::BufferHelper::getHex(csn)));
            }
        }
    }
    else{
        qDebug("No reader for card checking");
    }
}
