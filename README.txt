# Byte Differentiator (written in C)

Jonah Kim

## Instructions

This program compares two input files byte by byte, and produces two output files. One of the output files contains the
differences found in the first input file compared to the second (step 1), and the other output file vice versa (step 2). For
instance, if the first input file contained "Hello" and the second input file contained "hello!", the first output file
contains "H" and the second output file contains "h!". A 'cat' system call is included within the Makefile to print the
output files. This program also calculates and prints the time spent for each step of the program.

A Linux/Unix environment was used to write and test this code, and a Makefile is provided to compile, run, and clean the program.
Two input files are provided, and users may edit them to test various cases.
