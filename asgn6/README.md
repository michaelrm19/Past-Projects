# Assignment 6
## Michael Nguyen
## Description

This program reads in a list of badspeak words and another list of oldspeak and newspeak pairs of words. It will then create a "dictionary" with the use of hashtables
that are an array of linked lists and a Bloom Filter (which is an array of bits/bit vector). The program will read user input from stdin, compare the input to words hashed
and stored in the hashtable. If the user is deemed to be guilty of thoughtcrime or requires counseling (or both), the program will print out a corresponding message detailing
which words they used that was considered badspeak as well as any oldspeak words used along with their respective newspeak translations.

## Build

$ make all

## Run

$./banhammer -commandline options

## Command Line Options
-h size specifies the size of the hashtable, -f size specifies the size of the bloom filter, -m enables move-to-front rule

## Clean

$ make clean

## Other Notes
scan-build did not report any warnings or bugs. Please do note that Credit for code goes to TA Eugene and TA Sahiti for their pseudocode and explanations
on how to approach the linked list ADT in ll.c during their lab sections. Furthermore, much of the code for the Bit Vector ADT was taken from my BitMatrix ADT code in Assignment 4. In Assignment 4, TA Eugene was specifically helpful in explaining how masks and bitwise operations work for setting bits, getting bits, and clearing bits. Thus, credit goes to him. In the main() function, TA Sahiti was specifically useful in explaining the overall structure of the main() function, and I would like to specifically credit her on how to open, scan words from files, and close files in my main() function in banhammer.c. Also do note that when run, my program ended in a seg fault (which I wasn't able to pinpoint where my program failed). I would also like to credit Eugene once again for his operations on how to insert a node into a linked list, manipulating the nodes' previous and next pointers for a node in ll.c.

