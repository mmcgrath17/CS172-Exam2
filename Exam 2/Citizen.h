//I affirm that all code given below was written solely by me, Matt McGrath, and that any help I received 
//adhered to the rules stated for this exam
#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <string>
#include <iostream>

using namespace std;

class Citizen
{
private:
	int identity;
	string first;
	string last;
	string color;

public:
	Citizen(int id, string firstName, string lastName, string col) //constructor for citizen
	{
		identity = id;
		first = firstName;
		last = lastName;
		color = col;
	}

	Citizen(Citizen* citizen) //creates copy of citizen by accessing all of the input pointer's member variables
	{
		last = citizen->getLastName();
		first = citizen->getFirstName();
		color = citizen->getFavoriteColor();
		identity = citizen->getId();
	}

	~Citizen() {}

	string getLastName() //gets last name of this citizen
	{
		return last;
	}
	string getFirstName() //gets first name of this citizen
	{
		return first;
	}
	int getId() //gets id for this citizen
	{
		return identity;
	}
	string getFavoriteColor() //gets favorite color for this citizen
	{
		return color;
	}
	void setFavoriteColor(string col) //sets favorite color for this citizen
	{
		color = col;
	}
};
#endif