QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hub.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    sklad.cpp \
    workers.cpp \

HEADERS += \
    hub.h \
    loginwindow.h \
    mainwindow.h \
    sklad.h \
    workers.h

FORMS += \
    hub.ui \
    loginwindow.ui \
    mainwindow.ui \
    sklad.ui \
    workers.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    ../imasdasd/ad-white.png \
    ../imasdasd/ad.png \
    ../imasdasd/bitmap1.bmp \
    ../imasdasd/book-white.png \
    ../imasdasd/book.png \
    ../imasdasd/catalog.png \
    ../imasdasd/client-white.png \
    ../imasdasd/closeEye.png \
    ../imasdasd/deal-white.png \
    ../imasdasd/dollar.png \
    ../imasdasd/downArrow.png \
    ../imasdasd/history-white.png \
    ../imasdasd/history.png \
    ../imasdasd/laptop.png \
    ../imasdasd/logout.png \
    ../imasdasd/main.png \
    ../imasdasd/openEye.png \
    ../imasdasd/settings.png \
    ../imasdasd/sklad-white.png \
    ../imasdasd/sklad.png \
    ../imasdasd/t-white.png \
    ../imasdasd/tp-white.png \
    ../imasdasd/upArrow.png \
    ../imasdasd/vendor-white.png \
    ../imasdasd/vendor.png \
    ../imasdasd/worker-white.png \
    ../imasdasd/worker.png
