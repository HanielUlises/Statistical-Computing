CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -I/home/haniel/Libraries/ETL

TARGET = stats_app

OBJECTS = main.o csv_utilities.o dynamic_statistics.o

CSV_UTILITIES_SRC = /home/haniel/Libraries/ETL/csv_utilities.cpp
DYNAMIC_STATISTICS_SRC = /home/haniel/Libraries/ETL/dynamic_statistics.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o main.o

csv_utilities.o: $(CSV_UTILITIES_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(CSV_UTILITIES_SRC) -o csv_utilities.o

dynamic_statistics.o: $(DYNAMIC_STATISTICS_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(DYNAMIC_STATISTICS_SRC) -o dynamic_statistics.o

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
