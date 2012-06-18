CXX = g++
CC = g++
CXXFLAGS = -Wall
LDFLAGS = -Wall
VAR= headers.h Logs.h CROptions.h 
vpath %.o = bin

all: coderunner

# The .PHONY is needed to ensure that we recursively use the out/Makefile
# to check for changes.
.PHONY: coderunner

coderunner:
	cp config.h src/
	$(MAKE) --directory=bin
	ln -fs bin/main coderunner
	ln -fs bin/Execution Execution
	
clean:
	rm coderunner Execution
	$(MAKE) --directory=bin clean
