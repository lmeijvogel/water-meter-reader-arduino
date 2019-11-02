CXX = g++
CXXFLAGS = -std=c++0x -g -Wall -pedantic

APP_FILES_O = obj/Filter.o

TEST_FILES_O = obj/FilterTests.o

test: bin bin/run_tests
	bin/run_tests

obj:
	mkdir -p obj
bin: obj
	mkdir -p bin

obj/Filter.o: Filter.cpp
	$(CXX) Filter.cpp -c -o $@ $(CXXFLAGS)

obj/FilterTests.o: __tests__/FilterTests.cpp obj/Filter.o
	$(CXX) __tests__/FilterTests.cpp obj/Filter.o -c -o $@ $(CXXFLAGS)

obj/catch.o:  __tests__/suite.cpp
	$(CXX) __tests__/suite.cpp -c -o $@ $(CXXFLAGS)

bin/run_tests: obj/catch.o ${TEST_FILES_O}
	$(CXX) ${TEST_FILES_O} obj/catch.o -o $@ ${CXXFLAGS}

.PHONY: clean

clean:
	rm -rf obj bin
