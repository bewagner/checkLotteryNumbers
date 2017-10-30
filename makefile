# Universal makefile
#
#This makefile creates an executable called "checkLotterynumbers" from all the .cpp and .hh files in it's directory.
#To use this make file, please use the file endings .cpp/.hh for your source/header files.

#Specify all phony targets – that means they don't depend on a specific file
.PHONY := all clean run cleanAndRun

#Set the suffix list
.SUFFIX := .cpp .o .c .d

# ----- Variables -----
#Compiler
CXX := g++

#Compiler flags
CXXFLAGS := -c  -ggdb -g -Wall -Wextra -std=c++11 -O2

#Linker flags
LDFLAGS := -lm -ggdb -g

#Objects
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

#Dependencies
DEPS := $(OBJS:.o=.d)

#Name of executable
EXE := checkLotteryNumbers


# ----- Targets and rules -----
#Main target
all: $(EXE)
-include $(DEPS)

#Executable
$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

#Dependency files
%.d: %.cpp
	$(CXX) -MM -MT "$@ $(patsubst %.d, %.o, $@)" -MF $@ $<

#Object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

#Cleaning unwanted files
clean:
	rm -r -f $(OBJS) $(DEPS)

#Running your $(EXE)
run: $(EXE)
	./$(EXE) ./testCorrectNumbers.csv testMyNumbers.csv

#Clean and run afterwards
cleanAndRun: $(EXE)
	rm -rf $(OBJS) $(DEPS); ./$(EXE)
