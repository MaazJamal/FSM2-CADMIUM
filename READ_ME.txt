
Author: Maaz Jamal

Folder Structure:

├── DEVSmodelsForm_FSM2-CADMIUM.doc
├── FSM2-CADMIUM-REPORT.doc
├── ModelDescription-FSM2-CADMIUM.xml
├── READ_ME.txt
├── atomics
│   └── moore.h
├── bin
├── build
├── data_structures
│   ├── message.cpp
│   └── message.hpp
├── input_data
│   ├── main_ATM.txt
│   ├── main_serial_adder.txt
│   ├── main_telephone.txt
│   ├── main_vendor.txt
│   ├── moore_input_test.txt
│   ├── moore_input_test_transition.txt
│   └── simplemoore_test.txt
├── makefile
├── simulation_results
│   ├── ATOMIC_TEST_MOORE_outputs.txt
│   ├── ATOMIC_TEST_MOORE_state.txt
│   ├── COUPLED_ATM_outputs.txt
│   ├── COUPLED_ATM_state.txt
│   ├── COUPLED_TELEPHONE_outputs.txt
│   ├── COUPLED_TELEPHONE_state.txt
│   ├── COUPLED_TEST_SIMPLEMOORE_outputs.txt
│   ├── COUPLED_TEST_SIMPLEMOORE_state.txt
│   ├── COUPLED_VENDOR_outputs.txt
│   ├── COUPLED_VENDOR_state.txt
│   ├── COUPLED_serial_adder_outputs.txt
│   └── COUPLED_serial_adder_state.txt
├── test
│   ├── main_test_moore.cpp
│   └── main_test_simplemoore.cpp
├── top_model
│   ├── main_ATM.cpp
│   ├── main_Telephone.cpp
│   ├── main_serial_adder.cpp
│   └── main_vendor.cpp
└── vendor
    ├── NDTime.hpp
    └── iestream.hpp

1) compiling the program

	- Open the root workspce folder and run the command make all
	- This will generate all the binaries in bin file

2) Running the programs:

	- There are 6 binaries in bin folder.
	- To run one of the binary open bin folder
	- Open terminal in bin folder
	- run the following command ./binary_name

3) Inputs and Outputs:
	
	- The program takes inputs from txt files in input_data folder
	- The program outputs result of simulation in the simulation_results folder.

Troubleshooting:

	While attempt has been made to make sure the program is able to compile using 
	out of the box, provided the CADMIUM libraries are installed following the provided 
	instructions for ubuntu. 
	If Make cannot find the CADMIUM libraries. Please alter the makefile and change the values of 
	
	INCLUDECADMIUM=-I ~/CADMIUM/Cadmium-Simulation-Environment/cadmium/include
	INCLUDEDESTIMES=-I ~/CADMIUM/Cadmium-Simulation-Environment/DESTimes/include
	
	To the appropriate location in your computer. 
	For Cygwin:
	The cygwin installation may not not contain the initial CADMIUM folder and the include path may be:

	INCLUDECADMIUM=-I ~/Cadmium-Simulation-Environment/cadmium/include
	INCLUDEDESTIMES=-I ~/Cadmium-Simulation-Environment/DESTimes/include

	The program has been tested on Cygwin and WSL Ubuntu20 and has succeslfully compiled,
	ran and tested on those platforms. 
	