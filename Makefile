VAR= headers.h Logs.h CROptions.h 
complete: main Execution

main : main.o CodeRunner.o CROptions.o FileHandle.o CurlWrapper.o Logs.o ContentParser.o CROptions.o -lcurl
	g++ -o main main.o CodeRunner.o CROptions.o FileHandle.o CurlWrapper.o ContentParser.o Logs.o -lcurl

main.o : main.cpp CROptions.h CodeRunner.h $(VAR)
	g++ -c main.cpp

CodeRunner.o : CodeRunner.cpp CodeRunner.h $(VAR)
	g++ -c CodeRunner.cpp

CROptions.o : CROptions.cpp CROptions.h config.h $(VAR)
	g++ -c CROptions.cpp
	
FileHandle.o : FileHandle.cpp FileHandle.h CurlWrapper.h $(VAR)
	g++ -c FileHandle.cpp
	
CurlWrapper.o : CurlWrapper.cpp CurlWrapper.h $(VAR)
	g++ -c CurlWrapper.cpp
	
ContentParser.o : ContentParser.cpp ContentParser.h CurlWrapper.h $(VAR)
	g++ -c ContentParser.cpp

Logs.o : Logs.cpp $(VAR)
	g++ -c Logs.cpp

.PHONY: clean
clean:
	rm *.o main Execution

Execution : Execution.cpp resources.h
	g++ Execution.cpp -o Execution
