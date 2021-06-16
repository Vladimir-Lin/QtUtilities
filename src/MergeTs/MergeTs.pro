QT          += core
QT          -= gui

TARGET       = MergeTs
CONFIG      += console

TEMPLATE     = app

load(qt_tool)

SOURCES     += $${PWD}/MergeTs.cpp

win32 {
RC_FILE      = $${PWD}/MergeTs.rc
OTHER_FILES += $${PWD}/MergeTs.rc
include ($${PWD}/Documents/Qt/Qt.pri)
}
