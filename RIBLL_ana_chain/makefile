OBJS = ana_chain.o main.o
EXE  = ana_chain
                                                                                
ROOTCFLAGS    = $(shell root-config --cflags) -lSpectrum
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)
                                                                                
INCFLAGS = -I$(ROOTCFLAGS)
LDFLAGS = -L$(ROOTLIBS)
                                                                                
#CXX = g++
CPP = g++
FLAGS = -Wall -g $(INCFLAGS) $(LDFLAGS) 
                                                                                
#COMPILE = $(CXX) $(FLAGS) -c
COMPILE = $(CPP) $(FLAGS) -c                                                                                
all: $(EXE)
                                                                                
$(EXE): $(OBJS)
	$(CPP) -o $(EXE) $(OBJS) $(ROOTCFLAGS) $(ROOTLIBS)                                                                                 
#%.o: %.cxx
%.o: %.cpp
	$(COMPILE)  $<
clean:
	rm -f  *.o $(EXE)
