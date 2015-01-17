COMPILER = g++
COMPILER_FLAGS = -Wall -c -I. -I/opt/CPLEX_Studio/cplex/include -std=c++0x

LINKER_FLAGS = -I. -I/opt/CPLEX_Studio/cplex/include -std=c++0x

HEADER_DIR = src/header
SOURCE_DIR = src/source

BUILD_DIR = bin

DATAS_DIR = data
RESULT_DIR = result

DEPENDENCY_OBJECTS = tsp_solver.o

EXECUTABLE = solver

CPX_LIBDIR  = /opt/CPLEX_Studio/cplex/lib/x86-64_linux/static_pic
CPX_LDFLAGS = -lcplex -lm -pthread

#
# This is the default rule when make command is invocated
# without any target
#
default: create build

#
# This rule create the environment for the building phase
#
create:
	@echo "--------------------------------------------------"
	@echo "             BUILDING ENVIRONMENT                 "
	@echo "--------------------------------------------------"
	@mkdir -p $(BUILD_DIR)
	@echo "Build directory was succesfully created"
	@mkdir -p $(DATAS_DIR)
	@echo "Datas directory was succesfully created"
	@mkdir -p $(RESULT_DIR)
	@echo "Result directory was succesfully created"
	@echo "--------------------------------------------------"
	@echo "             ENVIRONMENT CREATED                  "
	@echo "--------------------------------------------------"
	@echo ""

build: create $(DEPENDENCY_OBJECTS)
	@$(COMPILER) $(LINKER_FLAGS) $(BUILD_DIR)/*.o main.cpp -o $(EXECUTABLE) -L$(CPX_LIBDIR) $(CPX_LDFLAGS)
	@echo "--------------------------------------------------"
	@echo "             PROJECT BUILDED                      "
	@echo "--------------------------------------------------"

tsp_solver.o: $(HEADER_DIR)/macro/cpxmacro.h $(HEADER_DIR)/solver/TSPSolver.h $(SOURCE_DIR)/solver/TSPSolver.cpp
	@echo "--------------------------------------------------"
	@echo "             BUILDING project                 "
	@echo "--------------------------------------------------"
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/solver/TSPSolver.cpp -o $(BUILD_DIR)/TSPSolver.o
	@echo "TSPSolver object was succesfully compiled"

clean:
	@echo "--------------------------------------------------"
	@echo "             CLEANING PHASE                       "
	@echo "--------------------------------------------------"
	@rm -rf $(EXECUTABLE)
	@echo "executable file was succesfully removed"
	@rm -rf $(BUILD_DIR)/*.o
	@echo "object files was succesfully removed"
	@rmdir -p --ignore-fail-on-non-empty $(BUILD_DIR)/
	@echo "object files directory was succesfully removed"
	@rm -rf $(RESULT_DIR)/*.lp
	@rm -rf $(RESULT_DIR)/*.sol
	@echo "CPlex result files are succesfully removed"
	@rmdir -p --ignore-fail-on-non-empty $(RESULT_DIR)/
	@echo "Result directory was succesfully removed"
	@rm -rf $(DATAS_DIR)/*.dat
	@echo "Problem data files was succesfully removed"
	@rmdir -p --ignore-fail-on-non-empty $(DATAS_DIR)/
	@echo "Datas directory was succesfully removed"
	@echo "--------------------------------------------------"
	@echo "             ENVIRONMENT CLEANED                  "
	@echo "--------------------------------------------------"