#include "carddatawriter.hpp"

cardDataWriter::cardDataWriter(QObject *parent) :
    QObject(parent)
{

}

cardDataWriter::cardDataWriter(std::shared_ptr<logicalaccess::Chip> chip) :
    chip_(chip),
    storage_(std::dynamic_pointer_cast<logicalaccess::StorageCardService>(chip->getService(logicalaccess::CST_STORAGE))),
    mifareLocation_(new logicalaccess::MifareLocation()),
    mifareAccessInfoToUse_(new logicalaccess::MifareAccessInfo())
{
}

//cardDataWriter::writeCard(cardDataReader cardData){

//}
