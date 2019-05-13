CC := g++ -std=c++11
CXXFLAGS += -O0 -Wall

KNAPSACK := DP_0_1_knapsack

ASTYLE := astyle --style=kr --indent=spaces=4 --suffix=none
ASTYLEFLAGS := --style=kr --indent=spaces=4 --suffix=none
CPPCHECK := cppcheck -I. --error-exitcode=1 .

$(PRE):
	$(CPPCHECK)
	astyle $(ASTYLEFLAGS) $(KNAPSACK).cpp

all: 
	$(PRE)
	$(CC) -o $(KNAPSACK) $(CXXFLAGS) $(KNAPSACK).cpp

debug:
	$(PRE)
	$(CC) -o $(SEKNAPSACKLECT) $(CXXFLAGS) -g $(KNAPSACK).cpp

debugEXE:
	$(PRE)
	$(CC) -o $(KNAPSACK).exe $(CXXFLAGS) -g $(KNAPSACK).cpp

style: $(SOURCES:.cpp=.astyle-check-stamp)
	$(PRE)

.PHONY: clean

clean:
	rm -rf $(KNAPSACK) $(KNAPSACK).exe