CC = gcc
CFLAGS = -I/usr/local/include
LDLIBS = -L/usr/local/lib -lglut -lGLU -lGL -lm -lpthread
#
.c.o:
	$(CC) $(CFLAGS) -c $<

all: exG

exG: main.o coord.o glsl.o
	$(CC) $(CFLAGS) $< coord.o glsl.o -o $@ $(LDLIBS)

clean:
	rm *.o exG

coord.o:	common.h coord.h coord.c
glsl.o:		glsl.h glsl.c
main.o:		common.h glsl.h main.c
