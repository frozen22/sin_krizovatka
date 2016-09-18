# Projekt: VUT Brno FIT - Inteligentni systemy (SIN)
#          Dopravni telematika - adaptivni rizeni krizovatky (Fuzzy)
# Autor:   Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
#          Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
# Datum:   2015-12-05

CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -O2 -lm
PFLAGS=./simlib/src/simlib.a -lsimlib
SOURCES=main.cpp Crossroad.cpp CrossroadPhase.cpp CrossroadSemaphore.cpp FuzzyControl.cpp Lane.cpp Parameters.cpp RuleDecision.cpp RuleGreenPhase.cpp RuleNextPhase.cpp Rules.cpp Vehicle.cpp VehicleGenerator.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sincrossroad

all: $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(PFLAGS)

clean:
	rm -f $(OBJECTS) xnemec61_xopalk01.zip $(EXECUTABLE)

install:
	wget http://www.fit.vutbr.cz/~peringer/SIMLIB/source/simlib-3.02-20111030.tar.gz && \
	tar -zxvf simlib-3.02-20111030.tar.gz && \
	make -C ./simlib

run:
	./sincrossroad
