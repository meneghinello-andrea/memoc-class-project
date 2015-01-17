COMPILER = g++
COMPILER_FLAGS = -Wall -c -I .

LINKER_FLAGS = -I .

HEADER_DIR = src/header
SOURCE_DIR = src/source

BUILD_DIR = bin

DATAS_DIR = data

DEPENDENCY_OBJECTS = hole.o plate.o random_plate_generator.o cluster_plate_generator.o problem_generator.o euclidean_problem_generator.o circle_plate_generator.o

EXECUTABLE = generator

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

hole.o: $(HEADER_DIR)/object/Hole.h $(SOURCE_DIR)/object/Hole.cpp
	@echo "--------------------------------------------------"
	@echo "             BUILDING PROJECT                       "
	@echo "--------------------------------------------------"
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/object/Hole.cpp -o $(BUILD_DIR)/Hole.o
	@echo "Hole object was succesfully compiled"

plate.o: $(HEADER_DIR)/object/Hole.h $(HEADER_DIR)/object/Plate.h $(SOURCE_DIR)/object/Plate.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/object/Plate.cpp -o $(BUILD_DIR)/Plate.o
	@echo "Plate object was succesfully compiled"

random_plate_generator.o: $(HEADER_DIR)/generator/PlateGenerator.h $(HEADER_DIR)/object/Hole.h $(HEADER_DIR)/object/Plate.h $(HEADER_DIR)/generator/RandomPlateGenerator.h $(SOURCE_DIR)/generator/RandomPlateGenerator.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/generator/RandomPlateGenerator.cpp -o $(BUILD_DIR)/RandomPlateGenerator.o
	@echo "RandomPlateGenerator object was succesfully compiled"

cluster_plate_generator.o: $(HEADER_DIR)/generator/PlateGenerator.h $(HEADER_DIR)/object/Hole.h $(HEADER_DIR)/object/Plate.h $(HEADER_DIR)/generator/ClusterPlateGenerator.h $(SOURCE_DIR)/generator/ClusterPlateGenerator.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/generator/ClusterPlateGenerator.cpp -o $(BUILD_DIR)/ClusterPlateGenerator.o
	@echo "ClusterPlateGenerator object was succesfully compiled"

problem_generator.o: $(HEADER_DIR)/generator/ProblemGenerator.h $(HEADER_DIR)/object/Hole.h $(HEADER_DIR)/object/Plate.h $(SOURCE_DIR)/generator/ProblemGenerator.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/generator/ProblemGenerator.cpp -o $(BUILD_DIR)/ProblemGenerator.o
	@echo "ProblemGenerator object was succesfully compiled"

euclidean_problem_generator.o: $(HEADER_DIR)/object/Hole.h $(HEADER_DIR)/generator/ProblemGenerator.h $(HEADER_DIR)/generator/EuclideanProblemGenerator.h $(SOURCE_DIR)/generator/EuclideanProblemGenerator.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/generator/EuclideanProblemGenerator.cpp -o $(BUILD_DIR)/EuclideanProblemGenerator.o
	@echo "EuclideanProblemGenerator object was succesfully compiled"

circle_plate_generator.o: $(HEADER_DIR)/generator/PlateGenerator.h $(HEADER_DIR)/object/Hole.h $(HEADER_DIR)/object/Plate.h $(HEADER_DIR)/generator/CirclePlateGenerator.h $(SOURCE_DIR)/generator/CirclePlateGenerator.cpp
	@$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_DIR)/generator/CirclePlateGenerator.cpp -o $(BUILD_DIR)/CirclePlateGenerator.o
	@echo "CirclePlateGenerator object was succesfully compiled"

#
# This rule execute the runnable file of the project
#
execute: build
	@./$(EXECUTABLE)

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
	@rm -rf $(DATAS_DIR)/*.dat
	@rm -rf $(DATAS_DIR)/*.crd
	@echo "data files was succesfully removed"
	@rmdir -p --ignore-fail-on-non-empty $(DATAS_DIR)/
	@echo "data files directory was succesfully removed"
	@echo "--------------------------------------------------"
	@echo "             ENVIRONMENT CLEANED                  "
	@echo "--------------------------------------------------"
