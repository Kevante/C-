#include <iostream>
#include <string>
#include <fstream>
#include "call_class.h"

using namespace std;

/************************************************************************************************************************************/
//Name: default constructor
//Precondition: call_class has not been initialized
//Postcondition: call_class has been initialized using callstats_data.txt
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;

	ifstream in;

	in.open("callstats_data.txt");

	call_DB = new call_record[size];
	call_record* temp = new call_record[size];

	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}

	if (is_empty())
	{
		double_size();
		double_size();
		temp = new call_record[size];
	}

	while (!in.eof())
	{
		if (is_full())
		{
			double_size();
			call_DB = temp;
			temp = new call_record[size];
			temp = call_DB;

		}
		in >> temp[count].firstname;
		in >> temp[count].lastname;
		in >> temp[count].cell_number;
		in >> temp[count].relays;
		in >> temp[count].call_length;
		count++;
	}

	in.close();

	call_DB = temp;
	process();

}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition: call_class Org has already been initialized and given a value
//Postcondition: call_class Org has been copied into call_DB
//Decription: performs a deep copy.
/************************************************************************************************************************************/
call_class::call_class(const call_class &Org)
{
	cout << "The Copy Constructor has been Called!\n";

	count = Org.count;
	size = Org.size;

	call_DB = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		call_DB[i] = Org.call_DB[i];
	}
}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: call_class has been initialized
//Postcondition: call_class has been initialized and has not been altered
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: call_class has been initialized
//Postcondition: call_class has been initialized and has not been altered
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: call_class has been initialized
//Postcondition: call_class has been initialized and has not been altered
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	for (int i = 0; i < count; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			return i;
		}
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: call_class has been initialized
//Postcondition: call_class has been initialized and has been altered
//Decription: adds a call_record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB. The user 
//            is prompted to enter the firstname, lastname, cell number, relays and call length. 
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full())
	{
		double_size();
	}

	call_record* temp = new call_record[size];
	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	cout << "Enter first name: " << endl;
	cin >> temp[count].firstname;
	cout << "Enter last name: " << endl;
	cin >> temp[count].lastname;
	cout << "Enter cell number: " << endl;
	cin >> temp[count].cell_number;
	cout << "Enter relays: " << endl;
	cin >> temp[count].relays;
	cout << "Enter call length: " << endl;
	cin >> temp[count].call_length;

	call_DB = temp;
	count++;
	process();



}


/******************************************************************************************************************************/
//Name: double_size
//Precondition: call_class has been initialized
//Postcondition: call_class has been initialized and has been altered
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];
	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: call_class has been initialized
//Postcondition: call_class has been initialized and has been altered
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int i = 0; i < count; i++)
	{
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		if (call_DB[i].relays >= 1 && call_DB[i].relays <= 5)
		{
			call_DB[i].call_tax = call_DB[i].net_cost * 1 / 100;	// CallRate = 1;
			call_DB[i].tax_rate = .01;
		}
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].call_tax = call_DB[i].net_cost * 3 / 100;	// CallRate = 3;
			call_DB[i].tax_rate = .03;
		}
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].call_tax = call_DB[i].net_cost * 5 / 100;	// CallRate = 5;
			call_DB[i].tax_rate = .05;
		}
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].call_tax = call_DB[i].net_cost * 8 / 100;	// CallRate = 8;
			call_DB[i].tax_rate = .08;
		}
		else if (call_DB[i].relays > 50)
		{
			call_DB[i].call_tax = call_DB[i].net_cost * 12 / 100;	// CallRate = 12;
			call_DB[i].tax_rate = .12;
		}
		else
		{
			call_DB[i].call_tax = call_DB[i].net_cost * 1 / 100;	// CallRate = 1. Was not given a tax_rate for 0 relays in the assignment description, but according to the outputs it is 1%
			call_DB[i].tax_rate = .01;
		}

		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}



/****************************************************************************************************************************/
//Name: destructor
//Precondition: call_class has been initialized
//Postcondition: memory has been deallocated from call_class
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[] call_DB;
}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: call_class has been initialized, key has been given a value
//Postcondition: call_class has been initialized and has not been altered
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	int loc = search(key);
	int i = 0;
	while (loc != -1)
	{
		count--;
		while (i < count)
		{
			if (i >= loc)
			{
				call_DB[i] = call_DB[i + 1];
			}
			i++;
		}
		loc = search(key);
		i = 0;
	}
	return *this;
}

/****************************************************************************************************************************/
//Name: operator<<
//Precondition: out and Org have been given values
//Postcondition: call_class has been initialized and has been altered
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen and a file called "stats7_output.txt".
/***************************************************************************************************************************/

ostream & operator<<(ostream & out, call_class & Org)
{
	for (int i = 0; i<Org.count; i++)
	{
		out << Org.call_DB[i].firstname << " " << Org.call_DB[i].lastname << "      \t" << Org.call_DB[i].cell_number << "\t" << Org.call_DB[i].relays << "\t" << Org.call_DB[i].call_length << "\t" << Org.call_DB[i].net_cost << "\t" << Org.call_DB[i].tax_rate << "\t" << Org.call_DB[i].call_tax << "\t" << Org.call_DB[i].total_cost << "\t" << endl;
	}

	//Put code to OPEN and CLOSE an ofstream and print to the file "stats7_output.txt".
	ofstream outfile;

	outfile.open("stats8_output.txt");

	if (outfile.fail())
	{
		cout << "Output file did not open correctly" << endl;
		exit(1);
	}

	outfile.setf(ios::showpoint);
	outfile.precision(2);
	outfile.setf(ios::fixed);

	// outputs every field of every call_record in call_DB to weekly5_call_info.txt file
	for (int i = 0; i < Org.count; i++)
	{
		outfile << Org.call_DB[i].firstname << " " << Org.call_DB[i].lastname << "      \t" << Org.call_DB[i].cell_number << "\t" << Org.call_DB[i].relays << "\t" << Org.call_DB[i].call_length << "\t" << Org.call_DB[i].net_cost << "\t" << Org.call_DB[i].tax_rate << "\t" << Org.call_DB[i].call_tax << "\t" << Org.call_DB[i].total_cost << "\t" << endl;
	}

	outfile.close();


	return out;  //must have this statement
}