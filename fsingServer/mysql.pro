TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    database.cpp \
    fsingservice.cpp
LIBS += -lmysqlclient

HEADERS += \
    database.h \
    fsingservice.h \
    macro.h
LIBS += -lpthread -lboost_system -lboost_thread -ljsoncpp
