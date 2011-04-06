main : main.cpp FileWrapper.h FileHandle.h CurlWrapper.h includes.h config.h
	g++ main.cpp -lcurl -o main
