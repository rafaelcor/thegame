SOURCES="main.cpp load.cpp common.cpp init.cpp draw.cpp cubes.cpp movimiento.cpp"
g++ -Wall -s $SOURCES -o pr `sdl2-config --libs --cflags` -lSDL2_image -lSDL2_ttf -lGL -lGLU
