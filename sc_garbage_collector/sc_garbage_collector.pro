TEMPLATE = lib

SOURCES += \
    sc_garbage_collector.c \
    sc_garbage_collector_operations.c \
    sc_garbage_collector_functions.c

INCLUDEPATH += ../../sc-machine/sc-memory/src
INCLUDEPATH += ../../sc-machine/sc-memory/src/sc-store
DESTDIR = ../../sc-machine/bin/search

win32 {
    CONFIG += qt console
    LIBS += -L "../../bin" -lsc_memoryd

    INCLUDEPATH += "../../glib/include/glib-2.0"
    INCLUDEPATH += "../../glib/lib/glib-2.0/include"

    POST_TARGETDEPS += ../../glib/lib/glib-2.0.lib
    LIBS += ../../glib/lib/glib-2.0.lib
}


unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    PKGCONFIG += gmodule-2.0

    LIBS += -L "../../sc-machine/bin" -lsc_memory
}

HEADERS += \
    sc_garbage_collector.h \
    sc_garbage_collector_functions.h \
    sc_garbage_collector_operations.h
