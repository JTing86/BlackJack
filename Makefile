
# compiler flags:
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CXXFLAGS = -g -Wall -Werror -std=c++11
CXX = g++

# the build target executable:
TARGET1 = cards
TARGET2 = dice


all: $(TARGET1) $(TARGET2)
<\t>$ (TARGET1) : $ (TARGET1).cpp
		$CXX $CXXFLAGS -o $(TARGET1) $(TARGET1).cpp
<\t>$ (TARGET2) : $(TARGET2).cpp
		$CXX $CXXFLAGS -o $(TARGET2) $(TARGET2).cpp



clean:
