CC_SOURCES = \
	main.cc \
	Stack.cc \
	NameList.cc \
	FunctionList.cc \
	IL.cc \
	Context.cc \
	ConstList.cc

BISONGEN = prak.cc
BISON = prak.y++

FLEXGEN = lex.yy.cc
FLEX = prak.l


CFLAGS = -Wall -d
CXX = g++


CC_OBJECTS = $(CC_SOURCES:.cc=.o)
BISON_OBJECT = prak.o
FLEX_OBJECT = lex.yy.o 

OBJECTS = $(CC_OBJECTS) $(BISON_OBJECT) $(FLEX_OBJECT)

all : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS)

%.o : %.cc
	$(CXX) -c $(CFLAGS) -o $@ $< 


$(FLEXGEN) : $(FLEX)
	flex -o$(FLEXGEN) $(FLEX) 

$(BISONGEN) : $(BISON)
	C:\Programme\GnuWin32\bin\bison -d -y -o $(BISONGEN) $(BISON)

depend:
	sed -e "/^# DO NOT DELETE/,$$$$d" Makefile > Makefile.cut
	echo "# DO NOT DELETE" >> Makefile.cut
	$(CXX) -MM $(CFLAGS) $(CC_SOURCES) | sed -e "s/.*:/\/&/" >> Makefile.cut
	rm Makefile
	mv Makefile.cut Makefile 

.PHONY: all
# DO NOT DELETE
/main.o: main.cc Context.h OTypes.h Stack.h FunctionList.h NameList.h IL.h
/Stack.o: Stack.cc Stack.h
/NameList.o: NameList.cc NameList.h
/FunctionList.o: FunctionList.cc FunctionList.h
/IL.o: IL.cc IL.h OTypes.h NameList.h
/Context.o: Context.cc Context.h OTypes.h Stack.h FunctionList.h \
  NameList.h
