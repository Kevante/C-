/***************************************************************************************************************************************
Name: Kevin Beltran                      Z#: 15234035
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date: 8/1/17                Due Time: 11:59
Total Points: 100
Assignment 11: call_stats8.cpp

Description: Read the contents of a datafile one record at a time into a dynamic array. Process the data that was read from the
datafile one record at a time, into a dynamic array. Print the records in a dynamic array to the screen and to a text file("stats7_output.txt").
It will separate the declaration and implementation for the class “call_class” into two separate files. It puts the class declaration in the 
file called “call_class.h”, and puts the class implementation in the file called “call_class.cpp.

Objectives:

1. Separate class code into a declaration (header) and implementation
components;
2. Implement a copy constructor;
3. Use the preprocessor directives #ifndef, #define and #endif.

***************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "call_class.h"	

using namespace std;


//driver to test the functionality of your class.
int main()
{
	call_class MyClass;


	call_class YourClass = MyClass;

	return 0;
}



