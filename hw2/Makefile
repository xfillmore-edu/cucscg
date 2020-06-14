# executable
EXE=hw2

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
hw2.o: hw2.c objects.h config.h
checkErrs.o: checkErrs.c config.h
fatal.o: fatal.c config.h
gprint.o: gprint.c config.h
project.o: project.c config.h

# build archives
config.a: checkErrs.o fatal.o gprint.o project.o
	ar -rcs $@ $^
bmbObjects.a: things.o
	ar -rcs $@ $^

# Compiling rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
hw2: hw2.o bmbObjects.a config.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)