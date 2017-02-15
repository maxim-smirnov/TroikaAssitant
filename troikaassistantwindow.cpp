#include "troikaassistantwindow.hpp"
#include "ui_troikaassistantwindow.h"

#include <QThread>
#include <QFileDialog>

#include <QKeyEvent>

TroikaAssistantWindow::TroikaAssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TroikaAssistantWindow),
    readerConfig_(nullptr),
    chip_(nullptr),

    currentReaderStatus_(new readerStatus()),
    currentCardStatus_(new cardStatus()),
    currentCardStatusThread_(new QThread()),
    currentCardDataReader_(nullptr)
{
    ui->setupUi(this);
    ui->readerStatusLineEdit->setStyleSheet("color: red;");
    ui->cardGroupBox->setEnabled(false);

    currentCardStatus_->moveToThread(currentCardStatusThread_);

    connect(this, &TroikaAssistantWindow::callClearCardInfoSlot,
            this, &TroikaAssistantWindow::clearCardInfo);

    connect(ui->refreshReaderStatusButton, &QPushButton::clicked,
            currentReaderStatus_, &readerStatus::refreshReaderStatus);


    connect(currentReaderStatus_, &readerStatus::sendReaderStatus,
            this, &TroikaAssistantWindow::reciveReaderStatus);

    connect(this, &TroikaAssistantWindow::getChip,
            currentCardStatus_, &cardStatus::startCardWaiting);

    connect(currentCardStatus_, &cardStatus::sendCardStatus,
            this, &TroikaAssistantWindow::reciveChip);

    connect(currentCardStatus_, &cardStatus::sendUID,
            this, &TroikaAssistantWindow::reciveUID);

    currentCardStatusThread_->start();
}

TroikaAssistantWindow::~TroikaAssistantWindow()
{
    delete ui;
    if(currentCardStatusThread_->isRunning())
        currentCardStatusThread_->terminate();


    delete currentReaderStatus_;
    delete currentCardStatus_;

    delete currentCardStatusThread_;

    if(currentCardDataReader_ != nullptr) delete currentCardDataReader_;
    if(currentTroikaCard_ != nullptr) delete currentTroikaCard_;
}

void TroikaAssistantWindow::reciveReaderStatus(std::shared_ptr<logicalaccess::ReaderConfiguration> readerConfig){
    if(readerConfig != nullptr) {
        ui->readerStatusLineEdit->setText("Reader connected");
        ui->readerStatusLineEdit->setStyleSheet("color: green;");
        ui->cardGroupBox->setEnabled(true);
    }
    else {
        ui->readerStatusLineEdit->setText("No reader");
        ui->readerStatusLineEdit->setStyleSheet("color: red;");
        ui->cardGroupBox->setEnabled(false);
    }

    readerConfig_ = readerConfig;
}

void TroikaAssistantWindow::reciveChip(std::shared_ptr<logicalaccess::Chip> chip, QString uid){
    ui->cardGroupBox->setTitle("Card detected");
    chip_ = chip;
    currentCardDataReader_ = new cardDataReader(chip_);

    currentTroikaCard_ = new troikaCard(uid, currentCardDataReader_->getBlockHex(0), currentCardDataReader_->getBlockHex(1));

    ui->balanceLabel->setText(QString::number(currentCardDataReader_->getBalance()));

    ui->block0HexLabel->setText(currentCardDataReader_->getBlockHex(0));
    ui->block1HexLabel->setText(currentCardDataReader_->getBlockHex(1));
    ui->cardNumberLabel->setText(QString::number(currentCardDataReader_->getCardNumber()));
}

void TroikaAssistantWindow::reciveUID(QString uid){
    ui->UIDLabel->setText(uid);
}

void TroikaAssistantWindow::on_readCardButton_clicked(){
    if(readerConfig_ != nullptr) {
        ui->cardGroupBox->setTitle("Waiting for card...");
        emit getChip(readerConfig_);
    }
    else {
        ui->cardGroupBox->setTitle("Reader error");
        emit callClearCardInfoSlot();
    }
}

void TroikaAssistantWindow::clearCardInfo(){
    ui->UIDLabel->clear();
    ui->cardNumberLabel->clear();
    ui->block0HexLabel->clear();
    ui->block1HexLabel->clear();
    ui->balanceLabel->clear();
}

void TroikaAssistantWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Troika Dump File"),tr(".td"),tr("*.td"));
    if(fileName.isEmpty()) return;

    QFile saveFile(fileName);

    saveFile.open(QIODevice::WriteOnly);
    saveFile.write((currentTroikaCard_->getUID() + '\n' +
                   currentTroikaCard_->getHexDataS8B0() + '\n' +
                   currentTroikaCard_->getHexDataS8B1()).toUtf8());
    saveFile.close();
}
