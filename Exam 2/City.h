//I affirm that all code given below was written solely by me, Matt McGrath, and that any help I received 
//adhered to the rules stated for this exam
#ifndef CITY_H_
#define CITY_H_


#include "Citizen.h"
#include <fstream>
#include <vector>

using namespace std;

class City
{
private:
	vector<Citizen*> population; //vector storing all people in this city
	string nameOfCity; //name of the city

public:
	City(string cityName)
	{
		ifstream fin; //make variable for reading from file
		cityName.append(".txt", ios::in); //add ".txt" so it fin can open the city
		fin.open(cityName); //opens the city text file corresponding to the city name passe in
		if (!fin.fail()) //does all the things below if it opens the file
		{
			string line; //takes out a line from the city.txt file
			string tempFirst; //temporary fisrtName variable
			string tempLast; //temporary lastName variable
			string tempColor; //temporary color variable
			int space1Index, space2Index; //tracks index of spaces
			int spaceNumber; //keeps track of how many spaces have been found
			int idIncrementor = 0; //variable to set the id to the line number

			while (getline(fin, line)) //takes each line out of the file, putting the content in the line variable
			{
				idIncrementor++; //increments the ID number each line
				spaceNumber = 0; //resets the space finder variable
				
				for (int i = 0; i < line.size(); i++) //runs through the line the number of times equal to the length
				{

					if (line.substr(i, 1).compare(" ") == 0) //checks if the current index is a space or not
					{
						if (spaceNumber == 0) //if no spaces have been found, sets the first space index to i
						{
							space1Index = i;
							spaceNumber++;
						}
						else if (spaceNumber == 1) //if one space has been found, sets the second splace index to i
						{
							space2Index = i;
						}

						tempFirst = line.substr(0, space1Index); //sets the temporary first name variable to the substring between 0 index and first space
						tempLast = line.substr(space1Index + 1, space2Index - space1Index - 1); //sets the temporary last name variable to the substring between the space1Index and space2Index
						tempColor = line.substr(space2Index + 1, line.size() - space2Index - 1); //sets the color to the last portion of this line after space 2

						Citizen * c = new Citizen(idIncrementor, tempFirst, tempLast, tempColor);
						population.push_back(c); //add new citizen with the gathered information to the population vector
					}
				}
			}
		}
	}

	~City()
	{
		ofstream fout; //make variable to write into city text file
		nameOfCity.append(".txt"); //adds the .txt so the file can be read
		fout.open(nameOfCity, ios::trunc); //overwrites existing or creates new text file with the name of the city
		if (!fout.fail())
		{
			while(!population.empty()) //inputs every citizen
			{
				int id = population.at(0)->getId(); //sets the temporary id variable to the id of the first citizen
				int index; //tracks which citizen in the population vector has the smallest id

				for (int i = 0; i < population.size() - 1; i++) //finds the lowest id
				{
					if (id > population.at(i + 1)->getId()) //tests if the next citizen in the population vector has a smaller id
					{
						id = population.at(i + 1)->getId(); //sets the new found lowest id number
						index = i + 1; //keeps track of which element has the smallest id
					}
				}

				fout << population.at(index)->getFirstName() << " " << population.at(index)->getLastName() << " " << population.at(index)->getFavoriteColor() << endl; //inputs the first and last name of the citizen at index i from population vector into the text file
				population.erase(population.begin() + index - 1); //erases the citizen at the lowest id number
			}
		}
	}

	string getCityName() //returns name of city
	{
		return nameOfCity;
	}

	int populationSize() //returns population size
	{
		return population.size();
	}

	Citizen * getCitizenAtIndex(int index) //returns pointer to citizen at index passed in
	{
		Citizen * tempCit = population.at(index); //make pointer to the citizen at this index
		return tempCit;
	}

	void addCitizen(Citizen * citizen)
	{
		population.push_back(citizen); //add citizen to end of population vector
	}

	Citizen * getCitizenWithId(int id)
	{
		bool found = false; //flag for finding this citizen
		int incrementor = 0; //incrementor variable
		while (!found) //goes through population vector as until the right citizen is found
		{
			if (population.at(incrementor)->getId() == id) //checks each citizen's id
			{
				found = true;
				cout << "\nCitizen found.\n";
				Citizen * c = population.at(incrementor);
				return c; //outputs the pointer to the citizen with the id passed in
			}

			if (incrementor == population.size()) //ends the loop when no one with this id is found
			{
				found = true;
				cout << "\nCitizen not found.\n";
			}
		}

		return &Citizen(id, "", "", ""); //if no citizen is found, retruns pointer to citizen with nothing in it but the id
	}

	vector<Citizen*> getCitizensForFavoriteColor(string color) //returns vector of all citizens with the favorite color passed in
	{
		vector<Citizen*> citizensWithColor;

		for (int i = 0; i < population.size(); i++) //test every citizen for their favorite color
		{
			if (population.at(i)->getFavoriteColor().compare(color) == 0) //chack if the current citizen at index i likes this color
			{
				citizensWithColor.push_back(population.at(i)); //adds this citizen if they do like this color
			}
		}
		return citizensWithColor;
	}
};
#endif