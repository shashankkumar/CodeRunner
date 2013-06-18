# Read http://blog.borngeek.com/2010/05/06/automatic-dependency-generation/

#SHELL is the program used as the shell
SHELL = /bin/bash

#CXX is the C++ compiler
CXX = g++

#CC is the C compiler
CC = g++

# CXXFLAGS are the flags to use when *compiling* c++ code
CXXFLAGS = -Wall -O3


# LFLAGS are the flags to use when *linking*
LDFLAGS = -Wall -O3

#varibales
VAR = headers.h Logs.h CROptions.h 
DEPDIR = dep
SRCDIR = src
OBJDIR = bin
CONFIG = config.h

# Build a list of the object files to create, based on the .cpps we find
# $(patsubst pattern,replacement,text)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

# Build a list of dependency files
DEPS = $(patsubst %.o,$(DEPDIR)/%.d,$(OTMP))

all: init config main Execution

init: $(DEPDIR) $(OBJDIR)
$(DEPDIR):
	mkdir -p $(DEPDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

config: $(SRCDIR)/$(CONFIG)
$(SRCDIR)/$(CONFIG): $(CONFIG)
	sh $(SRCDIR)/config.sh $(SRCDIR) $(CONFIG)

# Pull in dependency info for our objects

#stop reading the current makefile and read the other makefiles before proceeding 

-include $(DEPS)

main : $(filter-out $(OBJDIR)/Execution.o, $(OBJS))
	$(LINK.o) $^ -lcurl -o $@
	
Execution : $(OBJDIR)/Execution.o
	$(LINK.o) $^ -o $@

# Compile and generate dependency info
# 1. Compile the .cpp file
# 2. Generate dependency information, explicitly specifying the target name
# 3. The final three lines do a little bit of sed magic. The following
#    sub-items all correspond to the single sed command below:
#    a. sed: Strip the target (everything before the colon)
#    b. sed: Remove any continuation backslashes
#    c. fmt -1: List words one per line
#    d. sed: Strip leading spaces
#    e. sed: Add trailing colons
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(COMPILE.c) -o $@ -c $<
	$(COMPILE.c) -MM -MT $(OBJDIR)/$*.o $(SRCDIR)/$*.cpp > $(DEPDIR)/$*.d
	@cp $(DEPDIR)/$*.d $(DEPDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\\\$$//' < $(DEPDIR)/$*.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(DEPDIR)/$*.d
	rm -f $(DEPDIR)/$*.d.tmp
	
clean:
	rm -rf $(OBJDIR) $(DEPDIR) $(SRCDIR)/$(CONFIG) main Execution
