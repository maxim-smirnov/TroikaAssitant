#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T16:52:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TroikaAssistant
TEMPLATE = app


SOURCES += main.cpp\
        troikaassistantwindow.cpp \
    readerstatus.cpp \
    cardstatus.cpp \
    carddatareader.cpp \
    troikacard.cpp

HEADERS  += troikaassistantwindow.hpp \
    readerstatus.hpp \
    cardstatus.hpp \
    carddatareader.hpp \
    troikacard.hpp

FORMS    += troikaassistantwindow.ui

DEFINES += UNIX

QMAKE_CXXFLAGS += -std=c++1z -Wall -Wextra -Werror -pedantic-errors -stdlib=libc++

unix|win32: LIBS += -llogicalaccess -lmifarecards
