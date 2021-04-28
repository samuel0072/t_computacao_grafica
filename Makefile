all:	main clean
main:	obj_import.o	camera.o
	gcc obj_import.o camera.o main.c -o main -IGL -IGLU -IGLUT -lglut -lGL -lGLU -lm
obj_import.o:
	gcc obj_import.c -c
camera.o:
	gcc camera.c -c
clean:
	rm -rf *.o

