sdltest:	main.c
	gcc -Wall main.c entryReader.c game.c gameEvents.c `sdl-config --cflags --libs` -o main

clean:
	rm main.c entryReader.c game.c gameEvents.c
