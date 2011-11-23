VAR=includeh.h includes.h config.h Logs.h
complete: main Execution

main : main.o FileHandle.o CurlWrapper.o Logs.o ContentParser.o -lcurl
	g++ -o main main.o FileHandle.o CurlWrapper.o ContentParser.o Logs.o -lcurl

main.o : main.cpp ContentParser.h FileHandle.h $(VAR)
	g++ -c main.cpp

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
	rm *.o main *_execution

Execution : Execution.cpp
	g++ Execution.cpp -o Execution
