CXXFLAGS := -g -std=c++17
LDFLAGS := -g -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(wildcard *.cc)
EXECUTABLES := $(patsubst %.cc,%,$(SOURCES))

all: $(EXECUTABLES)

.PHONY: clean
clean:
	rm -f $(EXECUTABLES)

$(EXECUTABLES): %: %.cc 
	g++ $(CXXFLAGS) -o $@ $< $(LDFLAGS)