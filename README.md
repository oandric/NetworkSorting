# Sorting on the Maxeler dataflow machine




*Network sorting on Maxeler dataflow machine is implemented for the MaxIDE version 2011.*

We give an example of a Bitonic network sorting algorithm for arrays of 64 values to be sorted.

The implementation in the APP directory is streaming array from the PC over the PCIe bus to the FPGA on MAX2 maxeler card inside PC and compares results to the sequential sorting algorithm running on the CPU inside the same PC.

The original implementation of the network sorting on a PC using the conventional control flow machine is found in folder ORIG.
 
![LPLogo](DOCS/Bitonic8.png)