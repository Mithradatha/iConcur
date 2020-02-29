TARGET = cigarette-smokers
OBJECT = cigarette-smokers.o
SOURCE = cigarette-smokers.cpp
DEPENDENCIES = $(INCLUDE_DIRECTORY)/semaphore.o $(INCLUDE_DIRECTORY)/shared_stream.o

$(OBJECT): $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIRECTORY) -c $(SOURCE)

$(TARGET): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(DEPENDENCIES) $< -o $@ $(LIBRARY)

all: $(TARGET)

clean:
	$(RM) $(OBJECT) $(TARGET)
