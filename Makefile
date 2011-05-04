main : main.o FileHandle.o CurlWrapper.o
	g++ -o main main.o FileHandle.o CurlWrapper.o -lcurl

main.o : main.cpp includes.h CurlWrapper.h FileHandle.h
	g++ -c main.cpp

CurlWrapper.o : CurlWrapper.cpp CurlWrapper.h
	g++ -c CurlWrapper.cpp
	
FileHandle.o : FileHandle.cpp FileHandle.h
	g++ -c FileHandle.cpp
