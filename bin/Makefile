CXX = g++
CC = g++
CXXFLAGS = -Wall
LDFLAGS = -Wall
VAR = headers.h Logs.h CROptions.h 
SOURCE_DIR = ../src
vpath %.cpp = $(SOURCE_DIR)
vpath %.h = $(SOURCE_DIR)
OBJECT = main.o CodeRunner.o CROptions.o FileHandle.o CurlWrapper.o Logs.o ContentParser.o CROptions.o -lcurl

all: main Execution
main : $(OBJECT)
main.o : main.cpp CROptions.h CodeRunner.h $(VAR)
CodeRunner.o : CodeRunner.cpp CodeRunner.h $(VAR)
CROptions.o : CROptions.cpp CROptions.h config.h $(VAR)
FileHandle.o : FileHandle.cpp FileHandle.h CurlWrapper.h $(VAR)
CurlWrapper.o : CurlWrapper.cpp CurlWrapper.h $(VAR)
ContentParser.o : ContentParser.cpp ContentParser.h CurlWrapper.h $(VAR)
Logs.o : Logs.cpp $(VAR)
Execution : Execution.o
Execution.o : Execution.cpp resources.h

clean:
	rm *.o main Execution
