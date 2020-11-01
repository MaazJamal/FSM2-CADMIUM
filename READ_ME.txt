
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
	instructions. 
	If Make cannot find the CADMIUM libraries. Please alter the makefile and change the values of 
	
	INCLUDECADMIUM=-I ~/CADMIUM/Cadmium-Simulation-Environment/cadmium/include
	INCLUDEDESTIMES=-I ~/CADMIUM/Cadmium-Simulation-Environment/DESTimes/include
	
	To the appropriate location in your computer.  