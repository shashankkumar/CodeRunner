main : main.o FileHandle.o CurlWrapper.o Logger.o includes.h config.h
	g++ -o main main.o FileHandle.o CurlWrapper.o Logs.o -lcurl

main.o : main.cpp includes.h CurlWrapper.h FileHandle.h Logs.h includes.h config.h
	g++ -c main.cpp

FileHandle.o : FileHandle.cpp FileHandle.h CurlWrapper.h Logs.h includes.h config.h
	g++ -c FileHandle.cpp
	
CurlWrapper.o : CurlWrapper.cpp CurlWrapper.h Logs.h includes.h config.h
	g++ -c CurlWrapper.cpp
	
Logger.o : Logs.cpp Logs.h includes.h config.h
	g++ -c Logs.cpp
