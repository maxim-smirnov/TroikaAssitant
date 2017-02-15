#ifndef TROIKAASSISTANTWINDOW_HPP
#define TROIKAASSISTANTWINDOW_HPP

#include <QMainWindow>

#include <QThread>

#include <logicalaccess/dynlibrary/librarymanager.hpp>
#include <logicalaccess/readerproviders/readerconfiguration.hpp>

#include <logicalaccess/plugins/cards/mifare/mifarechip.hpp>
#include <logicalaccess/services/storage/storagecardservice.hpp>
#include <logicalaccess/plugins/cards/mifare/mifarelocation.hpp>

#include "readerstatus.hpp"
#include "cardstatus.hpp"
#include "carddatareader.hpp"
#include "troikacard.hpp"

namespace Ui {
class TroikaAssistantWindow;
}

class TroikaAssistantWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TroikaAssistantWindow(QWidget* parent = 0);
    ~TroikaAssistantWindow();

private:
    Ui::TroikaAssistantWindow* ui;
    std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig_;
    std::shared_ptr<logicalaccess::Chip> chip_;

    readerStatus* currentReaderStatus_;
    cardStatus* currentCardStatus_;
    QThread* currentCardStatusThread_;

    cardDataReader* currentCardDataReader_;
    troikaCard* currentTroikaCard_;

signals:
    void getChip(std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig);
    void callClearCardInfoSlot();

private slots:
    void reciveReaderStatus(std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig);
    void reciveChip(std::shared_ptr<logicalaccess::Chip> chip, QString uid);
    void reciveUID(QString uid);
    void on_readCardButton_clicked();
    void clearCardInfo();
    void on_saveButton_clicked();
};

#endif // TROIKAASSISTANTWINDOW_HPP
