
CXX=g++ 
INCDIR=-Iinclude
CXXFLAGS=--std=c++11 $(INCDIR)
LDFLAGS= #-g
FLAGS= -Wall -Wextra
CFLAGS= -m64 -fPIC -pedantic -pg -O3 -march=native


SRCS=analysis.cc histo.cc lhe_read.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: analysis

analysis: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o analysis  $(OBJS)

clean:
	rm -f *.o analysis

