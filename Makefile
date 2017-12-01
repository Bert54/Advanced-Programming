shooter: main.c
	gcc main.c entryReader.c game.c gameEvents.c scenePlacement.c characters.c projectiles.c menus.c -lSDL -lSDL_ttf `sdl-config --cflags --libs` -o game

clean:
	rm main.c entryReader.c game.c gameEvents.c scenePlacement.c characters.c projectiles.c menus.c
