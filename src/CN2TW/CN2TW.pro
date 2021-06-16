QT          += core
QT          -= gui

TARGET       = CN2TW
CONFIG      += console

TEMPLATE     = app

load(qt_tool)

SOURCES     += $${PWD}/CN2TW.cpp

win32 {
RC_FILE      = $${PWD}/CN2TW.rc
OTHER_FILES += $${PWD}/CN2TW.rc
include ($${PWD}/Documents/Qt/Qt.pri)
}
