TARGET = dinning-philosophers
OBJECT = dinning-philosophers.o
SOURCE = dinning-philosophers.cpp
DEPENDENCIES = $(INCLUDE_DIRECTORY)/semaphore.o $(INCLUDE_DIRECTORY)/shared_stream.o

$(OBJECT): $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIRECTORY) -c $(SOURCE)

$(TARGET): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(DEPENDENCIES) $< -o $@ $(LIBRARY)

all: $(TARGET)

clean:
	$(RM) $(OBJECT) $(TARGET)
