CXX      := -g++
CXXFLAGS := -O2 -Wall -Wno-missing-braces
LDFLAGS  := -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
BUILD    := build
TARGET   := DictionaryCS163.exe
INCLUDES  := -I ../include/ 
SRC      :=                      \
   $(wildcard ../src/*.cpp)         \
   $(wildcard ../src/pages/*.cpp)   \
   $(wildcard ../src/utility/*.cpp) \

default:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(OBJ) $(INCLUDES) $(LDFLAGS)