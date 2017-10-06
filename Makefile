shooter: main.c
	gcc main.c entryReader.c game.c gameEvents.c scenePlacement.c characters.c `sdl-config --cflags --libs` -o main

clean:
	rm main.c entryReader.c game.c gameEvents.c scenePlacement.c characters.c
