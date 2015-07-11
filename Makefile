default:
	g++ -std=c++11 *.cpp -o battleship

clean:
	rm -f battleship *~ *.o
