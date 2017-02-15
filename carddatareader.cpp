#include "carddatareader.hpp"

cardDataReader::cardDataReader(QObject *parent) :
    QObject(parent)
{

}

cardDataReader::cardDataReader(std::shared_ptr<logicalaccess::Chip> chip) :
    chip_(chip),
    storage_(std::dynamic_pointer_cast<logicalaccess::StorageCardService>(chip->getService(logicalaccess::CST_STORAGE))),
    mifareLocation_(new logicalaccess::MifareLocation()),
    mifareAccessInfoToUse_(new logicalaccess::MifareAccessInfo())
{
    mifareAccessInfoToUse_->keyA->fromString("a7 3f 5d c1 d3 33");

    mifareLocation_->sector = 8;
    mifareLocation_->block = 0;
    readDataSector8B0_ = storage_->readData(mifareLocation_, mifareAccessInfoToUse_, 16, logicalaccess::CB_DEFAULT);


    mifareLocation_->sector = 8;
    mifareLocation_->block = 1;
    readDataSector8B1_ = storage_->readData(mifareLocation_, mifareAccessInfoToUse_, 16, logicalaccess::CB_DEFAULT);

}

int cardDataReader::getBalance(){
    QString balanceHex;
    int balance;
    bool convertSuccess = false;

    if(readDataSector8B0_.at(7) == 25){
        for(std::size_t i=7; i<11; ++i)
            balanceHex.push_back(QString("%1").arg(readDataSector8B1_.at(i), 2, 16, QLatin1Char('0')));

        balance = balanceHex.toInt(&convertSuccess,16) / 6400;
    }
    else if(readDataSector8B0_.at(7) == 9){
        balanceHex.push_back(QString("%1").arg(readDataSector8B1_.at(8)&0xF, 2, 16, QLatin1Char('0')));
        balanceHex.push_back(QString("%1").arg(readDataSector8B1_.at(9), 2, 16, QLatin1Char('0')));
        balanceHex.push_back(QString("%1").arg(readDataSector8B1_.at(10)&0xF8, 2, 16, QLatin1Char('0')));

        balance = balanceHex.toInt(&convertSuccess,16) / 200;
    }

    if(convertSuccess)
        return balance;
    else
        return -1;
}

long cardDataReader::getCardNumber(){
    QString cardNumberHex;

    cardNumberHex.push_back(QString::number(readDataSector8B0_.at(2)&0xF, 16));
    for(std::size_t i=3; i<7; ++i)
        cardNumberHex.push_back(QString("%1").arg(readDataSector8B0_.at(i), 2, 16, QLatin1Char('0')));

    bool convertSuccess;
    long cardNumber = cardNumberHex.toInt(&convertSuccess, 16) >> 4;

    if(convertSuccess)
        return cardNumber;
    else
        return -1;

}

QString cardDataReader::getBlockHex(int block){
    QString hexData;
    if(block == 0){
        for(std::size_t i=0; i<16; ++i){
            hexData.push_back(QString("%1").arg(readDataSector8B0_.at(i), 2, 16, QLatin1Char('0')));
            hexData.push_back(' ');
        }
        return hexData;
    }
    if(block == 1){
        for(std::size_t i=0; i<16; ++i){
            hexData.push_back(QString("%1").arg(readDataSector8B1_.at(i), 2, 16, QLatin1Char('0')));
            hexData.push_back(' ');
        }
        return hexData;
    }
    return QString("Error");
}


