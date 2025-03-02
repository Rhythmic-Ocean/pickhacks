CFLAG = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

main: main.c
	gcc -o main.exe main.c all_thingies.h maps.c screen3.c raycasted.c $(CFLAG)