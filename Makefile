CC=g++
CFLAGS=-Werror -I.
DEPS = include/*.h
OBJ = vector3f.o  color.o ray.o source.o object.o light.o sphere.o plane.o triangle.o bmp.o camera.o raytracer.o exceptions.o obj.o main.o

all: ray

%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: src/main.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

ray: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

PHONY: clean

clean:
	rm -rf *.o