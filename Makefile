EXENAME = finalproj
OBJS = graph.o parser.o main.o search_algos.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

graph.o:
	$(CXX) $(CXXFLAGS) libraries/graph.cpp

parser.o:
	$(CXX) $(CXXFLAGS) libraries/parser.cpp	

main.o:
	$(CXX) $(CXXFLAGS) main.cpp

search_algos.o: graph.o
	$(CXX) $(CXXFLAGS) libraries/search_algos.cpp

test: search_algos.o parser.o graph.o
	$(LD) tests/tests.cpp search_algos.o Parser.o Graph.o $(LDFLAGS) -o test

clean:
	-rm -f *.o test $(EXENAME)

remake: clean all