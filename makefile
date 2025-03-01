CFLAG = -lSDL2 -lSDL2_image

main: main.c
	gcc -o main main.c $(CFLAG)