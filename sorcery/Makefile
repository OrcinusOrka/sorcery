CXX = g++
CXXFLAGS = -g -std=c++14 -Wall
OBJECTS = main.o ascii_graphics.o board.o card.o cardscollection.o deck.o effect.o enchantment.o minion.o player.o ritual.o spell.o textdisplay.o
EXEC = sorcery
${EXEC} : ${OBJECTS}
		${CXX} ${OBJECTS} -o ${EXEC}
.PHONY:clean
clean:
	rm ${OBJECTS} ${EXEC}
