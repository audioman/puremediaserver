#############################################################################
# Makefile for building: debug/PureMediaServer
# Generated by qmake (2.01a) (Qt 4.8.1) on: Thu Aug 9 20:40:30 2012
# Project:  PureMediaServer.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile PureMediaServer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_SCRIPT_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtScript -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -L./debug -lcitp -lQtScript -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		PureMediaServer.cpp \
		citp-lib.cpp \
		PacketCreator.cpp \
		PeerInformationSocket.cpp \
		MediaServer.cpp moc_PureMediaServer.cpp \
		moc_citp-lib.cpp \
		moc_PacketCreator.cpp \
		moc_PeerInformationSocket.cpp \
		moc_MediaServer.cpp
OBJECTS       = main.o \
		PureMediaServer.o \
		citp-lib.o \
		PacketCreator.o \
		PeerInformationSocket.o \
		MediaServer.o \
		moc_PureMediaServer.o \
		moc_citp-lib.o \
		moc_PacketCreator.o \
		moc_PeerInformationSocket.o \
		moc_MediaServer.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		PureMediaServer.pro
QMAKE_TARGET  = PureMediaServer
DESTDIR       = debug/
TARGET        = debug/PureMediaServer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_PureMediaServer.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) debug/ || $(MKDIR) debug/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: PureMediaServer.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtScript.prl \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtNetwork.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile PureMediaServer.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/declarative_debug.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtScript.prl:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtNetwork.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile PureMediaServer.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/PureMediaServer1.0.0 || $(MKDIR) .tmp/PureMediaServer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/PureMediaServer1.0.0/ && $(COPY_FILE) --parents PureMediaServer.h citp-lib.h PacketCreator.h PeerInformationSocket.h MediaServer.h CITPDefines.h MSEXDefines.h .tmp/PureMediaServer1.0.0/ && $(COPY_FILE) --parents main.cpp PureMediaServer.cpp citp-lib.cpp PacketCreator.cpp PeerInformationSocket.cpp MediaServer.cpp .tmp/PureMediaServer1.0.0/ && $(COPY_FILE) --parents PureMediaServer.ui .tmp/PureMediaServer1.0.0/ && (cd `dirname .tmp/PureMediaServer1.0.0` && $(TAR) PureMediaServer1.0.0.tar PureMediaServer1.0.0 && $(COMPRESS) PureMediaServer1.0.0.tar) && $(MOVE) `dirname .tmp/PureMediaServer1.0.0`/PureMediaServer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/PureMediaServer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_PureMediaServer.cpp moc_citp-lib.cpp moc_PacketCreator.cpp moc_PeerInformationSocket.cpp moc_MediaServer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_PureMediaServer.cpp moc_citp-lib.cpp moc_PacketCreator.cpp moc_PeerInformationSocket.cpp moc_MediaServer.cpp
moc_PureMediaServer.cpp: MediaServer.h \
		MSEXDefines.h \
		CITPDefines.h \
		ui_PureMediaServer.h \
		PureMediaServer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) PureMediaServer.h -o moc_PureMediaServer.cpp

moc_citp-lib.cpp: citp-lib.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) citp-lib.h -o moc_citp-lib.cpp

moc_PacketCreator.cpp: MSEXDefines.h \
		CITPDefines.h \
		PacketCreator.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) PacketCreator.h -o moc_PacketCreator.cpp

moc_PeerInformationSocket.cpp: PeerInformationSocket.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) PeerInformationSocket.h -o moc_PeerInformationSocket.cpp

moc_MediaServer.cpp: MSEXDefines.h \
		CITPDefines.h \
		MediaServer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MediaServer.h -o moc_MediaServer.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_PureMediaServer.h
compiler_uic_clean:
	-$(DEL_FILE) ui_PureMediaServer.h
ui_PureMediaServer.h: PureMediaServer.ui
	/usr/bin/uic-qt4 PureMediaServer.ui -o ui_PureMediaServer.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp PureMediaServer.h \
		MediaServer.h \
		MSEXDefines.h \
		CITPDefines.h \
		ui_PureMediaServer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

PureMediaServer.o: PureMediaServer.cpp PureMediaServer.h \
		MediaServer.h \
		MSEXDefines.h \
		CITPDefines.h \
		ui_PureMediaServer.h \
		citp-lib.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PureMediaServer.o PureMediaServer.cpp

citp-lib.o: citp-lib.cpp citp-lib.h \
		CITPDefines.h \
		PeerInformationSocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o citp-lib.o citp-lib.cpp

PacketCreator.o: PacketCreator.cpp PacketCreator.h \
		MSEXDefines.h \
		CITPDefines.h \
		PureMediaServer.h \
		MediaServer.h \
		ui_PureMediaServer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PacketCreator.o PacketCreator.cpp

PeerInformationSocket.o: PeerInformationSocket.cpp PeerInformationSocket.h \
		citp-lib.h \
		CITPDefines.h \
		PacketCreator.h \
		MSEXDefines.h \
		MediaServer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PeerInformationSocket.o PeerInformationSocket.cpp

MediaServer.o: MediaServer.cpp MediaServer.h \
		MSEXDefines.h \
		CITPDefines.h \
		PacketCreator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MediaServer.o MediaServer.cpp

moc_PureMediaServer.o: moc_PureMediaServer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_PureMediaServer.o moc_PureMediaServer.cpp

moc_citp-lib.o: moc_citp-lib.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_citp-lib.o moc_citp-lib.cpp

moc_PacketCreator.o: moc_PacketCreator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_PacketCreator.o moc_PacketCreator.cpp

moc_PeerInformationSocket.o: moc_PeerInformationSocket.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_PeerInformationSocket.o moc_PeerInformationSocket.cpp

moc_MediaServer.o: moc_MediaServer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MediaServer.o moc_MediaServer.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

