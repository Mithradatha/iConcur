SUB_DIRECTORIES = utilities rendezvous readers_writers dinning_philosophers cigarette_smokers

CXXFLAGS = -g -Wall -std=c++11
INCLUDE_DIRECTORY = ../utilities
LIBRARY = -pthread

export

all clean: $(SUB_DIRECTORIES)

$(SUB_DIRECTORIES):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all clean $(SUB_DIRECTORIES)
