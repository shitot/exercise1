
# Guy Golpur
# Bar Azouri
# Hadar Ivan
# Shachar Levkovich


ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = checkList.o main.o Checkbox.o

all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe -static