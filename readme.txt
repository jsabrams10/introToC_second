Asst0
John Abrams
2/17/2019
CS 214 - Systems Programming


----------------------------------------
Single-String CLI Parse-and-Sort in C
----------------------------------------


General Description:

This is a simple yet efficient C program that takes a single string as input and provides a sorted list of 
words it contains as output. Words are defined as solely alphabetic tokens from the input. Non-alphabetic 
characters are used as delimiters.


Efficiencies:

This program iterates once through the input string. During this scan, once a word is discovered it is 
copied out of the input, encapsulated into a node, and inserted into a linked list data structure. 
Insertions are designed to maintain a sorted property adhering to the assignment specification. As a 
result, the data is ready for output to the user immediately following the scanning process. As it is 
printed the data is simultaneously freed. The worst case run-time for this program would be O(n^2), in 
the scenario where each insertion occurs at the end of the list.
