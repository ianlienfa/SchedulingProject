INC = -I/Library/gurobi950/macos_universal2/include/ -I./headers/
CPP = g++
CARGS = -std=c++14 -m64 -g 
CPPLIB = -L/Library/gurobi950/macos_universal2/lib -lgurobi_c++ -lgurobi95
BIN_PATH = bin
INPUT = input/30_v1.in
ALGO = CBFSLag
# CPPLIB = 
# INC = 

# all: seq_relax_c++ permSet_outtree seq_lagRelax_c++ seq_c++
all: $(BIN_PATH)/permSet_outtree $(BIN_PATH)/TESTrelax_oneparam_c++

# %_c++: test/%_c++.cpp
# 	$(CPP) $(CARGS) -o $@ $< $(INC) $(CPPLIB) -lm

$(BIN_PATH)/TESTrelax_oneparam_c++: test/TESTrelax_oneparam_c++.cpp
	$(CPP) $(CARGS) -o $@ $< $(INC) $(CPPLIB) -lm

$(BIN_PATH)/permSet_outtree: permSet_outtree.cpp
	$(CPP) $(CARGS) -o $@ $< $(INC) $(CPPLIB) -lm

$(BIN_PATH)/seq_c++: gurobi/seq_c++.cpp
	$(CPP) $(CARGS) -o $@ $< $(INC) $(CPPLIB) -lm

.PHONY: clean
clean: 
	rm -rf $(BIN_PATH)/*


# to run the program with specific input: make run INPUT=input/input_file
.PHONY: run
run:
	@echo "[Makefile] Running: permSet_outtree"
	@echo "----------------------------------------"
	./$(BIN_PATH)/permSet_outtree $(ALGO) < $(INPUT)
	@echo

.PHONY: run_debug
run_debug:
	@echo "[Makefile] Running: permSet_outtree"
	@echo "----------------------------------------"
	./$(BIN_PATH)/permSet_outtree $(ALGO) debug=true < $(INPUT)
	@echo
