# executable
EXE=typewriter

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
typewriter.o: typewriter.cpp config.hpp
checkErrs.o: checkErrs.cpp config.hpp
fatal.o: fatal.cpp config.hpp
gprint.o: gprint.cpp config.hpp
project.o: project.cpp config.hpp
loadTexture.o: loadTexture.cpp config.hpp
twobjects.o: twobjects.cpp twobjects.hpp
selection.o: selection.cpp twobjects.hpp
getChar.o: getChar.cpp twobjects.hpp

# build archives
config.a: checkErrs.o fatal.o gprint.o project.o loadTexture.o
	ar -rcs $@ $^
twobjects.a: twobjects.o selection.o getChar.o
	ar -rcs $@ $^

# Compiling rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
typewriter: typewriter.o twobjects.a config.a
	g++ -O3 -o $@ $^   $(LIBS)
	$(info ) $(info ============== KEY BINDINGS ================)
	$(info q or ESC   exit program)
	$(info r          reset view)
	$(info w, s       lateral forward, backward)
	$(info a, d       lateral left, right)
	$(info z, x       increase, decrease elevation)
	$(info arrows     change angular view)
	$(info F, f       increase, decrease field of view)
	$(info ============================================) $(info )

#  Clean
clean:
	$(CLEAN)