run: all
	./fan

all: fan.cpp
	g++ -o fan fan.cpp glad.c objLoader.cpp obj_parser.cpp list.cpp string_extra.cpp openglsys.c transf2d.c -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl


