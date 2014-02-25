g++ -Wall -s pr.cpp load.cpp -o pr `sdl2-config --libs --cflags` -lSDL2_image -lSDL2_ttf -lGL -lGLU -Wl,-rpath -Wl,/usr/local/lib
