# define your sources here
SRC =	src/tacolife.cc \
	src/board/Board.cc \
	src/life/LifeObj.cc

# define here the include directory of taco
TACO		= 	~/taco/include

# define here the include directory of your compiler
CPLUSPLUS_INC   =       .


# define your platform for taco
PLATFORM	= TACO_MTTL
#PLATFORM	= TACO_MPI
#PLATFORM	= TACO_TCP
#PLATFORM	= TACO_BIP
#PLATFORM	= TACO_PM

# define your C++ compiler
# use mpi++ (or mpiCC) for MPI and mpc++ otherwise
# mpc++ uses g++ by default.
# for g++ enable the following flags

LIB=-L/usr/X11R6/lib -lX11
INC=-I/usr/include/X11 -Iinclude

CXX	= mpc++ -compiler=gnu3
CXXFLAGS := -O -Wall -felide-constructors -ftemplate-depth-25
#CXXFLAGS := -g -Wall -felide-constructors -ftemplate-depth-25

CPPFLAGS =  -DTACO_EXCEPTION -D$(PLATFORM)  -I. -I$(ETC_INC) -I$(TACO) $(INC) -I$(CPLUSPLUS_INC)

MAKEDEPEND = makedepend

OBJ = $(subst .cc,.o,$(SRC))
EXE = bin/tacolife

tacolife:	$(OBJ)
		$(CXX) -static $(OBJ) $(LIB) -o $(EXE)

depend: $(SRC)
	$(MAKEDEPEND) $(CPPFLAGS) $(SRC)

clean:
	/bin/rm -f $(OBJ) $(EXE)

# DO NOT DELETE

src/tacolife.o: include/defines.h include/life/LifeObj.h
src/tacolife.o: include/board/Board.h /usr/include/stdlib.h
src/tacolife.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/tacolife.o: /usr/include/gnu/stubs.h
src/tacolife.o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
src/board/Board.o: include/board/Board.h /usr/include/stdlib.h
src/board/Board.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/board/Board.o: /usr/include/gnu/stubs.h
src/board/Board.o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
src/board/Board.o: include/defines.h
src/life/LifeObj.o: /usr/include/stdlib.h /usr/include/features.h
src/life/LifeObj.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
src/life/LifeObj.o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
src/life/LifeObj.o: include/life/LifeObj.h include/defines.h
src/life/LifeObj.o: include/board/Board.h
