COMPILER = g++
COMPILER_FLAGS = -Wall -c -I .

LINKER_FLAGS = -I .

HEADER_DIR = src/header
SOURCE_DIR = src/source

BUILD_DIR = bin
DATAS_DIR = data

DEPENDENCY_OBJECTS = chromosome.o population.o genetic_algorithm.o

EXECUTABLE = solver

#
# This is the default rule when the make command is invocated
# without any target
#
default: create build

#
# This rule create the environment for the building and linking phase
#
create:
	@echo "--------------------------------------------------"
	@echo "             BUILDING ENVIRONMENT                 "
	@echo "--------------------------------------------------"
	@mkdir -p $(BUILD_DIR)
	@echo "Build directory was succesfully created"
	@mkdir -p $(DATAS_DIR)
	@echo "Datas directory was succesfully created"
	@echo "--------------------------------------------------"
	@echo "             ENVIRONMENT CREATED                  "
	@echo "--------------------------------------------------"
	@echo ""

#
# This rule build the project and produces a runnable files
#
build: create $(DEPENDENCY_OBJECTS)
	@$(COMPILER) $(LINKER_FLAGS) $(BUILD_DIR)/*.o main.cpp -o $(EXECUTABLE)
	@echo "--------------------------------------------------"
	@echo "             PROJECT BUILDED                      "
	@echo "--------------------------------------------------"

chromosome.o: $(HEADER_DIR)/object/Chromosome.h $(SOURCE_DIR)/object/Chromosome.cpp
	@echo "--------------------------------------------------"
	@echo "             BUILDING PHASE                      "
	@echo "--------------------------------------------------"
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/object/Chromosome.cpp -o $(BUILD_DIR)/Chromosome.o
	@echo "Chromosome object was succesfully compiled"

population.o: $(HEADER_DIR)/object/Chromosome.h $(HEADER_DIR)/object/Population.h $(SOURCE_DIR)/object/Population.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/object/Population.cpp -o $(BUILD_DIR)/Population.o
	@echo "Population object was succesfully compiled"

genetic_algorithm.o: $(HEADER_DIR)/object/Chromosome.h $(HEADER_DIR)/object/Population.h $(HEADER_DIR)/solver/GeneticAlgorithm.h $(SOURCE_DIR)/solver/GeneticAlgorithm.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/solver/GeneticAlgorithm.cpp -o $(BUILD_DIR)/GeneticAlgorithm.o
	@echo "GeneticAlgorithm object was succesfully compiled"

#
# This rule clean the environment from the compiled and data file
#
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
	@echo "--------------------------------------------------"
	@echo "             ENVIRONMENT CLEANED                  "
	@echo "--------------------------------------------------"