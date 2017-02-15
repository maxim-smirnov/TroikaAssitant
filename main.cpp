#include "troikaassistantwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TroikaAssistantWindow w;
    w.show();

    return a.exec();
}
