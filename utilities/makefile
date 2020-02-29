%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<

light_switch.o: semaphore.o

all: semaphore.o light_switch.o shared_stream.o

clean:
	$(RM) *.o

