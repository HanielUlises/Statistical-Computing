CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -I/home/haniel/Libraries/ETL

TARGET = stats_app

OBJECTS = main.o CSVUtilities.o dynamic_statistics.o

CSVUtilities_SRC = /home/haniel/Libraries/ETL/CSVUtilities.cpp
DYNAMIC_STATISTICS_SRC = /home/haniel/Libraries/ETL/dynamic_statistics.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o main.o

CSVUtilities.o: $(CSVUtilities_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(CSVUtilities_SRC) -o CSVUtilities.o

dynamic_statistics.o: $(DYNAMIC_STATISTICS_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(DYNAMIC_STATISTICS_SRC) -o dynamic_statistics.o

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
