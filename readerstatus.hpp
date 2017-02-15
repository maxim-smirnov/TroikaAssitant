#ifndef READERSTATUS_HPP
#define READERSTATUS_HPP

#include <QObject>
#include <qglobal.h>

#include <logicalaccess/dynlibrary/librarymanager.hpp>
#include <logicalaccess/readerproviders/readerconfiguration.hpp>

class readerStatus : public QObject
{
    Q_OBJECT

private:
    std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig_;

public:
    explicit readerStatus(QObject *parent = 0);

signals:
    void sendReaderStatus(std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig);

public slots:
    void refreshReaderStatus();
};

Q_DECLARE_METATYPE(std::shared_ptr<logicalaccess::ReaderConfiguration>)

#endif // READERSTATUS_HPP
