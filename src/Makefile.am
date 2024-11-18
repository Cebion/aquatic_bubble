SUBDIRS = ima sonidos

DEFS= -DLOCALEDIR=\"${localedir}\" -DPACKAGE=\"${PACKAGE}\" \
-DDATA_DIR=\"${datadir}/${PACKAGE}\" -DVER=\"${VERSION}\" -I../intl

LIBS= -lSDL -lSDL_image -lSDL_mixer

bin_PROGRAMS = aqbubble

aqbubble_SOURCES = actor.cpp audio.cpp barra.cpp burbuja.cpp cadena.cpp \
creditos.cpp dialogo.cpp enemigos.cpp escena.cpp grafico.cpp \
items.cpp juego.cpp libgrafico.cpp main.cpp marcas.cpp menu.cpp mundo.cpp \
nivel.cpp paco.cpp perifericos.cpp pez.cpp procesos.cpp protagonistas.cpp \
records.cpp silvio.cpp simple.cpp texto.cpp transicion.cpp

EXTRA_DIST = actor.h audio.h barra.h burbuja.h cadena.h creditos.h dialogo.h \
enemigos.h enum.h escena.h grafico.h items.h juego.h libgrafico.h \
main.h marcas.h menu.h mundo.h nivel.h paco.h perifericos.h pez.h procesos.h \
protagonistas.h records.h silvio.h simple.h texto.h transicion.h int_gettext.h
