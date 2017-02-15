#include "troikacard.hpp"

troikaCard::troikaCard(QObject *parent) :
    QObject(parent)
{

}

troikaCard::troikaCard(QString uid, QString hexDataS8B0, QString hexDataS8B1) :
    uid_(uid),
    hexDataS8B0_(hexDataS8B0),
    hexDataS8B1_(hexDataS8B1)
{

}

QString troikaCard::getUID() { return uid_; }
QString troikaCard::getHexDataS8B0() { return hexDataS8B0_; }
QString troikaCard::getHexDataS8B1() { return hexDataS8B1_; }

