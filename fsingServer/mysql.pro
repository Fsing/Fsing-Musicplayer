TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    database.cpp \
    fsingservice.cpp \
    songlistbroker.cpp \
    songlist.cpp \
    songbroker.cpp \
    song.cpp \
    fsingservice.cpp \
    fanbroker.cpp \
    fan.cpp
LIBS += -lmysqlclient

HEADERS += \
    database.h \
    fsingservice.h \
    macro.h \
    songlistbroker.h \
    songlist.h \
    songbroker.h \
    song.h \
    relationbroker.h \
    fsingservice.h \
    fanbroker.h \
    fan.h
LIBS += -lpthread -lboost_system -lboost_thread -ljsoncpp
