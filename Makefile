
CXX = g++
REPOS = ~/Repos

SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)

LDFLAGS = -lEternal -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lGLEW -L $(REPOS)/libEternal/

CXXFLAGS = -I $(REPOS)/libEternal/include/

out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJS) out
