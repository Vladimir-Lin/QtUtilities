QT          += core
QT          -= gui

TARGET       = NoComment
CONFIG      += console
CONFIG      -= app_bundle
CONFIG      += c++11

TEMPLATE     = app

load(qt_tool)

SOURCES     += $${PWD}/NoComment.cpp

win32 {
RC_FILE      = $${PWD}/NoComment.rc
OTHER_FILES += $${PWD}/NoComment.rc
}
