SHELL = /bin/bash
CXX = g++
CC = g++
CXXFLAGS = -Wall -O3
LDFLAGS = -Wall -O3
VAR = headers.h Logs.h CROptions.h 
DEPDIR = dep
SRCDIR = src
OBJDIR = bin
CONFIG = config.h

# Build a list of the object files to create, based on the .cpps we find
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
-include $(DEPS)

main : $(filter-out $(OBJDIR)/Execution.o, $(OBJS))
	$(LINK.o) $^ -lcurl -o $@
	
Execution : $(OBJDIR)/Execution.o
	$(LINK.o) $^ -o $@

# Compile and generate dependency info
# From website http://blog.borngeek.com/2010/05/06/automatic-dependency-generation/
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
