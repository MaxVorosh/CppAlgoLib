all: main


main: test.cpp
	g++ test.cpp -Wall -Werror -o main

clean:
	rm -rf main