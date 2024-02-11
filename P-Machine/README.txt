// Tristan B Grogan
// UCFID: 5175492
// Montague COP 3402 P-Machine
// 2/1/2024

Contributor(s): Tristan Grogan

PM/0 VIRTUAL MACHINE README:

This document provides instructions on how to compile and run the PM/0 Virtual Machine (VM) as per the assignment guidelines. 
The VM is written in C and is designed to run on Eustis3. 
It executes a series of instructions from an input file, manipulating a stack according to the principles of a stack-based VM.

Compilation Instructions:
To compile the VM on Eustis3, navigate to the directory containing your vm.c file and execute the following command:

gcc -o vm vm.c

This compiles the source code into an executable named vm.

Running the VM:
The VM expects the name of an input file containing instructions as a command-line argument. To run the VM with your input file, use the following command:

./vm input.txt

Replace input.txt with the actual name of your input file. Ensure the input file is in the same directory as the executable or provide a relative or absolute path to the file