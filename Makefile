all:	main clean
main:	obj_import.o	camera.o
	gcc obj_import.o camera.o main.c -o main.out -IGL -IGLU -IGLUT -lglut -lGL -lGLU -lm
obj_import.o:
	gcc sources/obj_import.c -c
camera.o:
	gcc sources/camera.c -c
clean:
	rm -rf *.o

