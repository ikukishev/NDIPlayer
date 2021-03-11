QT    += core gui widgets

CONFIG += c++17

NDISDKPATH = "~/NDISDKForLinux"

INCLUDEPATH += $${NDISDKPATH}/include

unix {
   contains(QT_ARCH, x86_64) {
      LIBS += -L"$${NDISDKPATH}/lib/x86_64-linux-gnu"
      message("x86_64");
   }
   else: contains(QT_ARCH, arm64) {
      message("arm64!");
      LIBS += -L"$${NDISDKPATH}/lib/arm-rpi3-linux-gnueabihf"
   }
   LIBS += -lndi
}

SOURCES += \
    main.cpp \
    PlayerWindow/playerwindow.cpp

HEADERS += \
   PlayerWindow/playerwindow.h \
   AudioPlayer/AudioPlayer.hpp \
   common/IPersistence.hpp \
   NDIModule/IFrame.hpp


# Default rules for deployment.
unix: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target

