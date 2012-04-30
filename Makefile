CXX = g++
CXXFLAGS = -Wall
VAR= headers.h Logs.h CROptions.h 
complete: main Execution

main : main.o CodeRunner.o CROptions.o FileHandle.o CurlWrapper.o Logs.o ContentParser.o CROptions.o -lcurl
	$(CXX) $(CXXFLAGS) -o main main.o CodeRunner.o CROptions.o FileHandle.o CurlWrapper.o ContentParser.o Logs.o -lcurl
	
main.o : main.cpp CROptions.h CodeRunner.h $(VAR)
	$(CXX) $(CXXFLAGS) -c main.cpp

CodeRunner.o : CodeRunner.cpp CodeRunner.h $(VAR)
	$(CXX) $(CXXFLAGS) -c CodeRunner.cpp

CROptions.o : CROptions.cpp CROptions.h config.h $(VAR)
	$(CXX) $(CXXFLAGS) -c CROptions.cpp
	
FileHandle.o : FileHandle.cpp FileHandle.h CurlWrapper.h $(VAR)
	$(CXX) $(CXXFLAGS) -c FileHandle.cpp
	
CurlWrapper.o : CurlWrapper.cpp CurlWrapper.h $(VAR)
	$(CXX) $(CXXFLAGS) -c CurlWrapper.cpp
	
ContentParser.o : ContentParser.cpp ContentParser.h CurlWrapper.h $(VAR)
	$(CXX) $(CXXFLAGS) -c ContentParser.cpp

Logs.o : Logs.cpp $(VAR)
	$(CXX) $(CXXFLAGS) -c Logs.cpp

clean:
	rm *.o main Execution

Execution : Execution.cpp resources.h
	$(CXX) $(CXXFLAGS) Execution.cpp -o Execution
