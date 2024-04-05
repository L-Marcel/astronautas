BUILD=build/main.o build/entities.o build/list.o build/utils.o
FLAGS=-g -Wall -pedantic -Isrc/includes

run:
	./main
dev: ${BUILD}
	g++ -o main ${BUILD}
build/main.o: src/main.cpp
	g++ ${FLAGS} -c src/main.cpp -o build/main.o
build/entities.o: src/entities.cpp src/includes/entities.h
	g++ ${FLAGS} -c src/entities.cpp -o build/entities.o
build/list.o: src/list.cpp src/includes/list.h
	g++ ${FLAGS} -c src/list.cpp -o build/list.o
build/utils.o: src/utils.cpp src/includes/utils.h
	g++ ${FLAGS} -c src/utils.cpp -o build/utils.o