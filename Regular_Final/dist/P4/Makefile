CC      := g++
CCFLAGS := -g -std=c++11
LDFLAGS :=

TARGETS:= prog
MAINS  := $(addsuffix .o, $(TARGETS) )
OBJ    := graphic.o $(MAINS)
DEPS   := graphic.hpp

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

$(OBJ): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $(LIBS) $^ $(CCFLAGS) $(LDFLAGS)
