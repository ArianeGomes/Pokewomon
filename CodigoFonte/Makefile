pokewomon:	main.o node.o lista.o pokemon.o game.o
	g++ main.o node.o lista.o pokemon.o game.o -o pokewomon -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o:
	g++ -c main.cpp

node.o:
	g++ -c node.cpp

lista.o:
	g++ -c lista.cpp

pokemon.o:
	g++ -c pokemon.cpp

game.o:
	g++ -c game.cpp

clean:
	rm *.o
