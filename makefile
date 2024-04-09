BUILD=build/main.o build/system.o build/expedition.o build/astronaut.o build/list.o build/utils.o
FLAGS=-g -Wall -pedantic -Isrc/includes

ifeq ($(OS),Windows_NT)
	EXEC=./main.exe
	BUILD_FRAG=
else
	EXEC=./main
	BUILD_FRAG=-Wl,--copy-dt-needed-entries -lncurses
endif

run:
	${EXEC}
dev: compile
	${EXEC}
compile: ${BUILD}
	g++ -o main ${BUILD} ${BUILD_FRAG}
build/main.o: src/main.cpp
	g++ ${FLAGS} -c src/main.cpp -o build/main.o
build/system.o: src/system.cpp src/includes/system.h
	g++ ${FLAGS} -c src/system.cpp -o build/system.o
build/expedition.o: src/expedition.cpp src/includes/expedition.h
	g++ ${FLAGS} -c src/expedition.cpp -o build/expedition.o
build/astronaut.o: src/astronaut.cpp src/includes/astronaut.h
	g++ ${FLAGS} -c src/astronaut.cpp -o build/astronaut.o
build/list.o: src/list.cpp src/includes/list.h
	g++ ${FLAGS} -c src/list.cpp -o build/list.o
build/utils.o: src/utils.cpp src/includes/utils.h
	g++ ${FLAGS} -c src/utils.cpp -o build/utils.o