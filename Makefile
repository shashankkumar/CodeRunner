VAR=includeh.h includes.h config.h Logs.h
main : main.o FileHandle.o CurlWrapper.o Logs.o ContentParser.o *_execution -lcurl
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

*_execution : cpp_execution.cpp java_execution.cpp
	g++ cpp_execution.cpp -o cpp_execution
	g++ java_execution.cpp -o java_execution
