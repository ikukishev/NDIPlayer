QT    += core gui widgets

CONFIG += c++17

NDISDKPATH = "../NDISDK"

INCLUDEPATH += $${NDISDKPATH}/include

unix {
   contains(QT_ARCH, x86_64) {
      LIBS += -L"$${NDISDKPATH}/lib/x86_64-linux-gnu"
      message("LINUX x86_64");
   } else: contains(QT_ARCH, arm64) {
      message("LINUX arm64!");
      LIBS += -L"$${NDISDKPATH}/lib/arm-rpi3-linux-gnueabihf"
   }
   LIBS += -lndi
}
else: win32 {
    contains(QT_ARCH, x86_64) {
        message("WINDOWS 64-bit")
        LIBS += -L"$${NDISDKPATH}/Lib/x64"
        LIBS += -lProcessing.NDI.Lib.x64
    } else {
        message("WINDOWS  32-bit")
        LIBS += -L"$${NDISDKPATH}/Lib/x86"
        LIBS += -lProcessing.NDI.Lib.x86
    }
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

