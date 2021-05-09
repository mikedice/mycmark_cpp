CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -I/Users/mikedice/code/c++/cmark/src -I/Users/mikedice/code/c++/cmark/build/src
LDFLAGS=-g -L./libraries
LDLIBS=-lcmark

SRCS=main.cpp metadata.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: mycmark

mycmark: $(OBJS)
	$(CXX) $(LDFLAGS) -o mycmarkapp $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) mycmarkapp

distclean: clean
	$(RM) *~ .depend

include .depend