# executable
EXE=hw3

# main target
all: $(EXE)

# MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# state dependencies for each object file
hw3.o: hw3.c bmbObjects.h config.h
checkErrs.o: checkErrs.c config.h
fatal.o: fatal.c config.h
gprint.o: gprint.c config.h
project.o: project.c config.h
loadTexture.o: loadTexture.c config.h
cone.o: cone.c bmbObjects.h
cylinder.o: cylinder.c bmbObjects.h
leaf.o: leaf.c bmbObjects.h
cvertex.o: cvertex.c bmbObjects.h

# build archives
config.a: checkErrs.o fatal.o gprint.o project.o loadTexture.o
	ar -rcs $@ $^
bmbObjects.a: cone.o cylinder.o leaf.o cvertex.o
	ar -rcs $@ $^

# Compiling rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
hw3: hw3.o bmbObjects.a config.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)