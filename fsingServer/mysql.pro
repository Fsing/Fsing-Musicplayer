TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    database.cpp \
    fsingservice.cpp \
    fan.cpp \
    songlist.cpp \
    song.cpp \
    fanbroker.cpp \
    songlistbroker.cpp \
    songbroker.cpp
LIBS += -lmysqlclient

HEADERS += \
    database.h \
    fsingservice.h \
    macro.h \
    song.h \
    songlist.h \
    user.h \
    ralationbroker.h \
    fan.h \
    fanbroker.h \
    songbroker.h \
    songlistbroker.h
LIBS += -lpthread -lboost_system -lboost_thread -ljsoncpp
