build:
	g++ -Wall ./src/*.cpp -lSDL2 -o renderer

run:
	./renderer

clean:
	rm renderer