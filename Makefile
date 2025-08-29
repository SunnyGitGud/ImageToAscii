maincppp: main.cpp
	g++ main.cpp -o ascii `pkg-config --cflags --libs opencv4`
