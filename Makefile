.PHONY: all clean

CPPFLAGS := -g -I. $(shell root-config --cflags)
CXXFLAGS= -g -Wall `root-config --cflags`
LDFLAGS=`root-config --glibs`

SUFFIXES := .o .C .cpp
EXES := analyzeTree

SRCS := $(wildcard *.C)
OBJS := $(SRCS:.C=.o)

all: $(EXES)

analyzeTree: $(OBJS)

clean:
	- $(RM) $(OBJS) Dependencies.make $(EXES)


Dependencies.make: $(wildcard *.C)
	$(CPP) -g  $(CPPFLAGS) -MM $^ >$@
-include Dependencies.make