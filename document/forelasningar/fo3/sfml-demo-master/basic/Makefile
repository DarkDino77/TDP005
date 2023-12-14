CXXFLAGS := -g -std=c++17
LDFLAGS := -g -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(wildcard *.cpp)
EXECUTABLES := $(patsubst %.cpp,%,$(SOURCES))

all: $(EXECUTABLES)

.PHONY: clean
clean:
	rm -f $(EXECUTABLES)

$(EXECUTABLES): %: %.cpp
	g++ $(CXXFLAGS) -o $@ $< $(LDFLAGS)
