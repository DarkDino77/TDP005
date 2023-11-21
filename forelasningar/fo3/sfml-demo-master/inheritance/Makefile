CXXFLAGS := -g -std=c++17 -Wall -Wextra
LDFLAGS := -g -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))

# Dependencies:
DEPS := $(patsubst %.o,%.d,$(OBJECTS))
DEPFLAGS := -MMD -MP

all: game

pdf: uml.pdf

.PHONY: clean
clean:
	rm -f game $(OBJECTS) $(DEPS)
	find . -name "uml.*" | grep -Ev "(pdf|tex)$$" | xargs rm -f

uml.pdf: uml.tex
	latexmk -xelatex -pvc- uml.tex

game: $(OBJECTS)
	g++ $(CXXFLAGS) -o game $(OBJECTS) $(LDFLAGS)

$(OBJECTS): %.o: %.cpp
	g++ $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<

# Include dependencies
-include $(DEPS)
