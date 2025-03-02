CFLAG = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

main: main.c
	gcc -o main main.c $(CFLAG)