#  $Source: /home/xubuntu/berlios_backup/github/tmp-cvs/c--compiler/Repository/vps/Makefile,v $
#  $Revision: 1.1 $,  $Date: 2004/12/01 09:57:26 $
#  $Author: tobi1024 $,  $State: Exp $  
######################################################################
#
#  $Log: Makefile,v $
#  Revision 1.1  2004/12/01 09:57:26  tobi1024
#  Makefile
#
######################################################################

# Liste der Quelltexte:
# (Beim Hinzufuegen neuer Module erweitern!)
# Achtung!!!! Hinter dem backslash am Zeilenende darf *kein* Zeichen stehen!!
# Die letzte Zeile bekommt kein backslash!!!
#
# ACHTUNG!!! Die Reihenfolge ist entscheidend.


CC_SOURCES         =                                    \
                  src/X/XWindow.cc                     \
                  src/board/LocalBoard.cc              \
                  src/net/UDPNetwork.cc                \
		  src/net/TCPNetwork.cc \
		  src/client/LifeClient.cc             \
		  src/board/BoardServer.cc 

CLIENTOBJ        =                                 \
                  client.o
CLIENT = client

SERVEROBJ        =                                 \
                  server.o
SERVER = server

OBJDIR = bin
SRCDIR = src
APIDIR = doc/api
CC = g++
CXX = g++
LD = g++

INCLUDEDIR = -Iinclude      \
             -I/usr/include \
             -I/usr/X/include 

XLIBDIR   := /usr/X11R6/lib
LIBS      := -L$(XLIBDIR) \
             -L/usr/lib   \
             -lnsl        \
	     -lXt \
	-lX11       \
              -lm         \
              -lICE       \
              -lSM

CFLAGS = -Wall -g $(INCLUDEDIR)

CC_OBJECTS = $(notdir $(CC_SOURCES:.cc=.o))

OBJPRE = \
	$(addprefix $(OBJDIR)/, $(CC_OBJECTS))


# Ab hier folgt die Definition der targets,
# die stark vom gewaehlten Generierungssystem abhaengen.

.PHONY: clean doc

# erzeuge das Projekt komplett neu

all: client server

client: $(OBJDIR)/$(CLIENT)

server: $(OBJDIR)/$(SERVER)

# -------------------------------------------------
# Regel zur Erzeugung des Objektdateiverzeichnisses

$(OBJDIR) :
	mkdir $(OBJDIR)

# ----------------------------------------------------
# Regel zur Erzeugung des Dokumentationsverzeichnisses

$(APIDIR) : $(DOCDIR)
	mkdir $(APIDIR)

# -------------------------------------------------------------------------

# erzeuge Dokumentation mit Doxygen

doc: $(APIDIR)
	doxygen vps.cfg


# -include $(OBJ:%.o=%.d)

bin/cputicks.o : 
	$(CC) -c $(CFLAGS) -o bin/cputicks.o include/timer/readCpuTicks.s

$(OBJDIR)/%.o : 
	$(CC) -c $(CFLAGS) -o $@ $<


$(OBJDIR)/$(CLIENTOBJ): $(SRCDIR)/$(CLIENTOBJ:.o=.cc)
	@echo ''
	@echo '           --- Compiling '$(@:.o=.cc) to $@' ... '
#	$(CC) -M $(CFLAGS) $(INCLUDEDIR) -c $(@:.o=.cc) > $(@:.o=.d)
	$(CC) $(CFLAGS) -c -o $(@) $(SRCDIR)/$(notdir $(@:.o=.cc))

$(OBJDIR)/$(SERVEROBJ): $(SRCDIR)/$(SERVEROBJ:.o=.cc)
	@echo ''
	@echo '           --- Compiling '$(@:.o=.cc) to $@' ... '
#	$(CC) -M $(CFLAGS) $(INCLUDEDIR) -c $(@:.o=.cc) > $(@:.o=.d)
	$(CC) $(CFLAGS) -c -o $(@) $(SRCDIR)/$(notdir $(@:.o=.cc))


$(OBJDIR)/$(CLIENT):  $(OBJDIR)/$(CLIENTOBJ) $(OBJPRE) bin/cputicks.o
	@echo '           --- Linking '$< into $@' ... '
	$(CC) $(OBJDIR)/$(CLIENTOBJ) $(OBJPRE) -o $@ bin/cputicks.o $(CFLAGS) $(INCLUDEDIR) $(LIBS)

$(OBJDIR)/$(SERVER):  $(OBJDIR)/$(SERVEROBJ) $(OBJPRE) bin/cputicks.o
	@echo '           --- Linking '$< into $@' ... '
	$(CC) $(OBJDIR)/$(SERVEROBJ) $(OBJPRE) -o $@ bin/cputicks.o $(CFLAGS) $(INCLUDEDIR) $(LIBS)

clean:
	$(RM) $(OBJDIR)/$(CLIENTOBJ)
	$(RM) $(OBJDIR)/$(SERVEROBJ)
	$(RM) $(OBJPRE)
	$(RM) $(CLIENTOBJ:%.o=%.d)
	$(RM) $(SERVEROBJ:%.o=%.d)
	$(RM) $(CC_OBJECTS:%.o=%.d)
	$(RM) $(OBJDIR)/$(SERVER)
	$(RM) $(OBJDIR)/$(CLIENT)

depend:
	sed -e "/^# DO NOT DELETE/,$$$$d" Makefile > Makefile.cut
	echo "# DO NOT DELETE" >> Makefile.cut	
	echo $(OBJDIR)/$(SERVER): $(OBJDIR)/$(SERVEROBJ)>> Makefile.cut
	echo $(OBJDIR)/$(CLIENT): $(OBJDIR)/$(CLIENTOBJ)>> Makefile.cut	
	$(CC) -MM $(CFLAGS) $(SRCDIR)/$(SERVEROBJ:.o=.cc) $(SRCDIR)/$(CLIENTOBJ:.o=.cc) $(CC_SOURCES) $(INCLUDEDIR) | sed -e "s/.*:/$(OBJDIR)\/&/" >> Makefile.cut
	
	rm Makefile
	mv Makefile.cut Makefile

# DO NOT DELETE
bin/server: bin/server.o
bin/client: bin/client.o
bin/server.o: src/server.cc include/net/IPAddress.h include/net/IPNetwork.h \
  include/net/UDPNetwork.h include/board/Board.h \
  include/board/LocalBoard.h include/board/BoardServer.h \
  include/X/XWindow.h include/X/Coord2D.h
bin/client.o: src/client.cc include/X/XWindow.h include/X/Coord2D.h \
  include/net/IPAddress.h include/net/IPNetwork.h \
  include/net/UDPNetwork.h include/client/LifeClient.h \
  include/board/LocalBoard.h include/board/Board.h
bin/XWindow.o: src/X/XWindow.cc include/X/XWindow.h include/X/Coord2D.h \
  include/icon_bitmap
bin/LocalBoard.o: src/board/LocalBoard.cc include/board/LocalBoard.h \
  include/board/Board.h
bin/UDPNetwork.o: src/net/UDPNetwork.cc include/net/UDPNetwork.h \
  include/net/IPNetwork.h include/net/IPAddress.h
bin/TCPNetwork.o: src/net/TCPNetwork.cc include/net/TCPNetwork.h \
  include/net/IPNetwork.h include/net/IPAddress.h
bin/LifeClient.o: src/client/LifeClient.cc include/client/LifeClient.h \
  include/net/IPAddress.h include/net/IPNetwork.h \
  include/board/LocalBoard.h include/board/Board.h
bin/BoardServer.o: src/board/BoardServer.cc include/board/BoardServer.h \
  include/X/XWindow.h include/X/Coord2D.h include/board/Board.h \
  include/net/IPAddress.h include/net/IPNetwork.h \
  include/board/LocalBoard.h
