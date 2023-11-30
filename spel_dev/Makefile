CCC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic -Weffc++ -g -fno-elide-constructors
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC := src#Source directory
BIN := bin#Output directory

#All test related files need to have the name test in them
IN_TEST_FILES := $(notdir $(wildcard $(SRC)/*test*))

#Gives the files the correct format
SRC_TEST := $(addprefix $(SRC)/,$(IN_TEST_FILES))
BIN_TEST := $(addprefix $(BIN)/,$(IN_TEST_FILES:.cc=.o))

#The files that are necessary for the game
NECESSARY_IN_FILES := $(filter-out $(IN_TEST_FILES), $(notdir $(wildcard $(SRC)/*.cc)))

#Gives the files the correct format
SRC_NECESSARY := $(addprefix $(SRC)/,$(NECESSARY_IN_FILES))
BIN_NECESSARY := $(addprefix $(BIN)/,$(NECESSARY_IN_FILES:.cc=.o))

all: game

game: $(BIN_NECESSARY)
	$(CCC) $(CFLAGS) $(BIN_NECESSARY) $(SFMLFLAGS) -o the_grand_arena

#Create the compiled binary files and put them in bin/
$(BIN)/%.o: $(SRC)/%.cc
	$(CCC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_NECESSARY) $(BIN)/test_gameobj.o the_grand_arena

.PHONY:
clearscreen:
	clear

.PHONY:
run:
	./the_grand_arena

.PHONY:
leak_run:
	valgrind --tool=memcheck --leak-check=yes ./the_grand_arena