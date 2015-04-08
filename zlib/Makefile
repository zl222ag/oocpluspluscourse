zlib:
	mkdir -p obj
	g++ -Wall -fPIC -I../include/ -std=c++11 -c ../source/*.cpp
	ar -cvq zlib.a *.o
clean:
	rm -rfv obj/
