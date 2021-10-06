INC = /Library/gurobi912/mac64/include/
CPP = g++
CARGS = -std=c++14 -m64 -g -arch x86_64
CPPLIB = -L/Library/gurobi912/mac64/lib -lgurobi_c++ -lgurobi91

all: c_test_c++ seq_c++ seq_relax_c++

clean: 
	rm *_c++

%_c++: %_c++.cpp
	$(CPP) $(CARGS) -o $@ $< -I$(INC) $(CPPLIB) -lm