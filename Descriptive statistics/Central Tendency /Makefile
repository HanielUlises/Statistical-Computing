CXX = g++
CXXFLAGS = -std=c++17 -I/home/haniel/Libraries/ETL

all: stats

stats: main.o /home/haniel/Libraries/ETL/CSVUtilities.o
	$(CXX) -o stats main.o /home/haniel/Libraries/ETL/CSVUtilities.o $(CXXFLAGS)

main.o: main.cpp /home/haniel/Libraries/ETL/CSVUtilities.h
	$(CXX) -c main.cpp $(CXXFLAGS)

clean:
	rm -f *.o stats