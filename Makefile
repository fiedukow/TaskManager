# 3edc47e2e679f8673c5066264f902714
CC=clang
CXX=g++
CFLAGS=$(O) 
CXXFLAGS=$(CFLAGS) --std=c++0x -std=c++0x
O=-O2
LFLAGS=
OBJS=objs/ZarzadcaZadan.o objs/Population.o objs/EvolFunctions.o objs/EvolException.o objs/Subject.o objs/TaskManager.o objs/Zadanie.o objs/CzasRealizacji.o objs/Realizacja.o objs/PodgladPostepu.o


.PHONY: all
all: objs TaskManager

./TaskManager: $(OBJS)
	@ echo "    LINK ./TaskManager"
	@ $(CXX) $(OBJS) -o "./TaskManager" $(LFLAGS)

objs/ZarzadcaZadan.o: src/ZarzadcaZadan.cpp src/ZarzadcaZadan.hpp \
 src/EvolException.hpp
	@ echo "    CXX  src/ZarzadcaZadan.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/ZarzadcaZadan.cpp" -o $@
objs/Population.o: src/Population.cpp src/Population.hpp src/Subject.hpp \
 src/EvolException.hpp src/Chromosome.hpp src/debug.h src/Observer.hpp \
 src/EvolFunctions.hpp
	@ echo "    CXX  src/Population.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/Population.cpp" -o $@
objs/EvolFunctions.o: src/EvolFunctions.cpp src/EvolFunctions.hpp \
 src/Chromosome.hpp src/EvolException.hpp
	@ echo "    CXX  src/EvolFunctions.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/EvolFunctions.cpp" -o $@
objs/EvolException.o: src/EvolException.cpp src/EvolException.hpp
	@ echo "    CXX  src/EvolException.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/EvolException.cpp" -o $@
objs/Subject.o: src/Subject.cpp src/Subject.hpp src/EvolException.hpp \
 src/Chromosome.hpp src/debug.h
	@ echo "    CXX  src/Subject.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/Subject.cpp" -o $@
objs/TaskManager.o: src/TaskManager.cpp src/Realizacja.hpp src/Population.hpp \
 src/PodgladPostepu.hpp \
 src/Subject.hpp src/EvolException.hpp src/Chromosome.hpp src/debug.h \
 src/Observer.hpp src/EvolFunctions.hpp src/Zadanie.hpp \
 src/ZarzadcaZadan.hpp src/CzasRealizacji.hpp
	@ echo "    CXX  src/TaskManager.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/TaskManager.cpp" -o $@
objs/Zadanie.o: src/Zadanie.cpp src/Population.hpp src/Subject.hpp \
 src/EvolException.hpp src/Chromosome.hpp src/debug.h src/Observer.hpp \
 src/EvolFunctions.hpp
	@ echo "    CXX  src/Zadanie.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/Zadanie.cpp" -o $@
objs/CzasRealizacji.o: src/CzasRealizacji.cpp src/Population.hpp \
 src/Subject.hpp src/EvolException.hpp src/Chromosome.hpp src/debug.h \
 src/Observer.hpp src/CzasRealizacji.hpp src/Realizacja.hpp \
 src/EvolFunctions.hpp src/Zadanie.hpp src/ZarzadcaZadan.hpp
	@ echo "    CXX  src/CzasRealizacji.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/CzasRealizacji.cpp" -o $@
objs/Realizacja.o: src/Realizacja.cpp src/Realizacja.hpp src/Population.hpp \
 src/Subject.hpp src/EvolException.hpp src/Chromosome.hpp src/debug.h \
 src/Observer.hpp src/EvolFunctions.hpp src/Zadanie.hpp \
 src/ZarzadcaZadan.hpp
	@ echo "    CXX  src/Realizacja.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/Realizacja.cpp" -o $@
objs/PodgladPostepu.o: src/PodgladPostepu.cpp src/PodgladPostepu.hpp \
 src/TaskManager.cpp src/Realizacja.hpp src/Population.hpp \
 src/Subject.hpp src/EvolException.hpp src/Chromosome.hpp src/debug.h \
 src/Observer.hpp src/EvolFunctions.hpp src/Zadanie.hpp \
 src/ZarzadcaZadan.hpp src/CzasRealizacji.hpp
	@ echo "    CXX  src/PodgladPostepu.cpp"
	@ $(CXX) $(CXXFLAGS) -c "src/PodgladPostepu.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./TaskManager"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././TaskManager

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g -Wall -Wextra --std=c++0x
debug: O=-O0
debug: CC=gcc
debug: CXX=g++
debug: all

.PHONY: check-syntax
check-syntax:
	g++ $(CXXFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
