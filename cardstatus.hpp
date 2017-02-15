#ifndef CARDSTATUS_HPP
#define CARDSTATUS_HPP

#include <QObject>
#include <qglobal.h>

#include <logicalaccess/dynlibrary/librarymanager.hpp>
#include <logicalaccess/readerproviders/readerconfiguration.hpp>
#include <logicalaccess/cards/chip.hpp>

#include <logicalaccess/plugins/cards/mifare/mifarechip.hpp>
#include <logicalaccess/services/storage/storagecardservice.hpp>
#include <logicalaccess/plugins/cards/mifare/mifarelocation.hpp>

class cardStatus : public QObject
{
    Q_OBJECT

private:
    std::shared_ptr<logicalaccess::Chip> chip_;

public:
    explicit cardStatus(QObject *parent = 0);

signals:
    void sendCardStatus(std::shared_ptr<logicalaccess::Chip> chip, QString uid);
    void sendUID(QString uid);

public slots:
    void startCardWaiting(std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig);

};

Q_DECLARE_METATYPE(std::shared_ptr<logicalaccess::Chip>)

#endif // CARDSTATUS_HPP
