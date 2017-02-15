#ifndef TROIKACARD_HPP
#define TROIKACARD_HPP

#include <QObject>
#include <qglobal.h>

class troikaCard : public QObject
{
    Q_OBJECT

private:
    QString uid_;
    QString hexDataS8B0_;
    QString hexDataS8B1_;

public:
    explicit troikaCard(QObject *parent = 0);
    troikaCard(QString uid, QString hexDataS8B0, QString hexDataS8B1);

    QString getUID();
    QString getHexDataS8B0();
    QString getHexDataS8B1();

};

#endif // TROIKACARD_HPP
