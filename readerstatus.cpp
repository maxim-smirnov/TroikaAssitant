#include "readerstatus.hpp"

readerStatus::readerStatus(QObject *parent) :
    QObject(parent),
    readerConfig_(new logicalaccess::ReaderConfiguration())
{

}

void readerStatus::refreshReaderStatus(){
    readerConfig_->setReaderProvider(logicalaccess::LibraryManager::getInstance()->getReaderProvider("PCSC"));
    readerConfig_->setReaderUnit(readerConfig_->getReaderProvider()->createReaderUnit());
    if (readerConfig_->getReaderProvider()->getRPType() == "PCSC" &&
            readerConfig_->getReaderProvider()->getReaderList().size() == 0) {
        qDebug("No PCSC readers");

        emit sendReaderStatus(nullptr);
        return;
    }

    readerConfig_->getReaderUnit()->connectToReader();
    qDebug("Reader is connected");

    qRegisterMetaType<std::shared_ptr<logicalaccess::ReaderConfiguration>>();
    emit sendReaderStatus(readerConfig_);
}
