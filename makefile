BUILD=build/main.o build/system.o build/expedition.o build/astronaut.o build/utils.o
FLAGS=-g -Wall -pedantic -Isrc/includes
ARGS=
CLEAR=clear

ifeq (seeded, $(filter seeded,$(MAKECMDGOALS)))
	ARGS=seeded
endif

ifeq ($(OS),Windows_NT)
	EXEC=./main.exe ${ARGS}
	BUILD_FRAG=
	CLEAR=cls
else
	EXEC=./main ${ARGS}
	BUILD_FRAG=-Wl,--copy-dt-needed-entries -lncurses
endif

valgrind: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ${EXEC} && ${CLEAR}
run:
	${EXEC} && ${CLEAR}
dev: compile
	${EXEC} && ${CLEAR}
compile: ${BUILD}
	g++ -o main ${BUILD} ${BUILD_FRAG}
build/main.o: src/main.cpp src/includes/list.hpp
	g++ ${FLAGS} -c src/main.cpp -o build/main.o
build/system.o: src/system.cpp src/includes/system.hpp
	g++ ${FLAGS} -c src/system.cpp -o build/system.o
build/expedition.o: src/expedition.cpp src/includes/expedition.hpp
	g++ ${FLAGS} -c src/expedition.cpp -o build/expedition.o
build/astronaut.o: src/astronaut.cpp src/includes/astronaut.hpp
	g++ ${FLAGS} -c src/astronaut.cpp -o build/astronaut.o
build/utils.o: src/utils.cpp src/includes/utils.hpp
	g++ ${FLAGS} -c src/utils.cpp -o build/utils.o
seeded:
	${CLEAR}