SHELL := bash
all: compile execute 

compile:
	@echo "Compiling the source code src.c"
	mpicc src.c -o halo -lm
	@echo "Create hostfile dynamically"
	./create_hostfile.sh 8 8
	
execute:
	@echo "---------------------------------------------"
	@echo "Running all the halo program with all the configurations"
	./execute_config.sh


