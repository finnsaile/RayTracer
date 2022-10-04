CXX       := /usr/bin/g++
CXX_FLAGS := -std=c++17 -fdiagnostics-color=always -Wall
RELEASE_FLAGS := -Ofast
LIBRARIES := -lstatusbar 
OPENCV := -lopencv_core -lopencv_highgui -lopencv_imgcodecs


SRC     := src
INCLUDE := include

all: clean release

release: main.cpp $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $(RELEASE_FLAGS) -I$(INCLUDE) $^ -o main.exe $(LIBRARIES) $(OPENCV) 

main.exe: main.cpp $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES) $(OPENCV)

run: all
	./main.exe

clean:
	rm -f *.exe

test.exe: test.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES) $(OPENCV)
