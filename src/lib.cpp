// File: lib.cpp
// Version: V1.1
// Date: 04/04/2012
// Name: Daniel Clarke - Computer Science
// ID: n0271538
// This program contains a library of functions which interact with the data layer (Red Black Tree), functions include, insert, edit, print, search, delete
// Modification history:
// V1.1 4/4/2012

#include "lib.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "Vessel.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <time.h>

using namespace std;

//this thing..
binaryTree MyList;
Node MyNode;

void library::hydrophoneSim()
{
	system("CLS");

	std::cout << "-Listening on Hydrophone-" << std::endl
		 << std::endl;

	auto signature = MyNode.generateKey();

	std::cout << "Acoustic Signature detected! : " << signature << std::endl
		 << "Checking System for Possible Match..." << std::endl
		 << std::endl;

	MyList.hydrophone(signature);
}

void library::Percent(Node *node, double percentage)
{
	if (percentage > 65)
	{
		std::cout << "Closest Match to: " << node->getKey() << " with " << setprecision(4) << percentage << "%" << std::endl
			 << std::endl;
		streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
	}
	else
	{
		std::cout << "Signature is Unidentified" << std::endl
			<< "Only a " << setprecision(4) << percentage << "% Match to a Vessel in the System" << std::endl
			<< "Could Not Make Comparison" << std::endl
			<< std::endl;
	}
}

void library::insertVessel()
{
	system("CLS");

	//these Data Members can never be changed once entered
	std::cout << "-Insert Vessel-" << std::endl
		 << std::endl;
	auto signature = MyNode.generateKey();
	std::cout << "Vessel's Acoustic Signature: " << signature << std::endl
		 << std::endl;
	auto newName = setName();
	std::cout << std::endl;

	MyList.insert(signature, newName, fillVesselPtr());

	endGraceful();
}

void library::selectEditVessel()
{
	system("CLS");

	std::cout << "-Edit Vessel-" << std::endl
		 << std::endl;

	std::cout << "What would you like to Edit?" << std::endl
		 << std::endl;

	std::cout << "1. VesselName" << std::endl
		 << "2. Vessel Data" << std::endl
		 << ">";

	auto select = 0;
	for (;;)
	{
		select = validateCin();
		if ((select < 1) || (select > 2))
		{
			std::cout << "INCORRECT INPUT" << std::endl
				<< std::endl;
			continue;
		}
		break;	
	}

	std::cout << "Enter an ID to edit" << std::endl;
	std::cout << ">";
	auto keyToFind = validateCin();
	std::cout << std::endl;

	if (select == 1)
	{
		MyList.editNodeName(keyToFind);
		std::cout << "Vessel Name Edited" << std::endl;
	}
	else
	{
		MyList.editNode(keyToFind);
	}

	endGraceful();
}

BaseVessel *library::fillVesselPtr()
{
	std::cout << "What type of Vessel would you like to insert" << std::endl
		 << std::endl
		 << "Surface Vessels" << std::endl
		 << "1. AirCraft Carrier" << std::endl
		 << "2. Destroyer" << std::endl
		 << "Fleet Auxiliaries" << std::endl
		 << "3. Tanker" << std::endl
		 << "4. Landing Platform Dock" << std::endl
		 << "Submarines" << std::endl
		 << "5. Ballistic Sub" << std::endl
		 << "6. Attack Sub" << std::endl
		 << ">";

	auto select = 0;
	for (;;)
	{
		select = validateCin();
		if ((select < 1) || (select > 6))
		{
			std::cout << "INCORRECT INPUT" << std::endl
				<< std::endl;
			continue;
		}
		break;
	}

	std::cout << std::endl;

	switch (select)
	{
	case 1:
		std::cout << "You Chose 'Aircraft Carrier'" << std::endl
			 << std::endl;
		return new AircraftCarrier(std::cin);
	case 2:
		std::cout << "You Chose 'Destroyer'" << std::endl
			 << std::endl;
		//create new instance of vessel and call constructor
		return new Destroyer(std::cin);
	case 3:
		std::cout << "You Chose 'Tanker'" << std::endl
			 << std::endl;
		return new Tanker(std::cin);
	case 4:
		std::cout << "You Chose 'Landing Platform Dock'" << std::endl
			 << std::endl;
		return new LandingPlat(std::cin);
	case 5:
		std::cout << "You Chose 'Ballistic Submarine'" << std::endl
			 << std::endl;
		return  new BallisticSub(std::cin);
	case 6:
		std::cout << "You Chose 'Attack Submarine'" << std::endl
			 << std::endl;
		return new AttackSub(std::cin);
	}

	return nullptr;
}

std::string library::setName()
{
	std::cout << "Enter Name: " << std::endl;
	std::cout << "> ";
	auto newName = std::string("");
	cin >> newName;

	return newName; //to make each vessel HMS "something"
}

void library::sizeOfList()
{
	std::cout << "There is/are " << MyList.size() << " Vessels(s) on the System" << std::endl;
	endGraceful();
}

void library::printVessels()
{
	system("CLS");
	std::cout << "-Vessel Print-" << std::endl
		 << std::endl;
	std::cout << "In which order would you like to print" << std::endl
		 << "1. In Order" << std::endl
		 << "2. Post Order" << std::endl
		 << "3. No Order" << std::endl
		 << ">";

	auto select = 0;
	for (;;)
	{
		select = validateCin();
		if ((select < 1) || (select > 3))
		{
			std::cout << "INCORRECT INPUT" << std::endl
				<< std::endl;
			continue;
		}
		break;
	}

	MyList.publicPrint(select);
	endGraceful();
}

void library::getVessel()
{
	system("CLS");

	std::cout << "-System Search-" << std::endl
		 << std::endl;

	std::cout << "How would you like to search" << std::endl
		 << "1. By Signature" << std::endl
		 << "2. By Name" << std::endl
		 << ">";

	auto select = 0;
	for (;;)
	{
		select = validateCin();
		if ((select < 1) || (select > 2))
		{
			std::cout << "INCORRECT INPUT" << std::endl
				<< std::endl;
			continue;
		}
		break;
	}

	if (select == 1)
	{
		std::cout << "Please Enter an ID:" << std::endl;
		std::cout << ">";

		select = validateCin();

		MyList.FindVesselID(select);

		std::cout << std::endl;
	}
	else
	{
		std::cout << "Please Enter a Name:" << std::endl;
		std::cout << ">";

		auto searchName = std::string("");
		cin >> searchName;

		MyList.findVesselName(searchName);
		std::cout << std::endl;
	}

	endGraceful();
}

void library::deleteVessel()
{
	system("CLS");

	std::cout << "-Delete Vessel-" << std::endl
		 << std::endl;

	std::cout << "Please Enter ID to Delete Vessel" << std::endl;
	std::cout << ">";

	auto select = validateCin();

	MyList.deletePublic(select);

	std::cout << "Vessel With ID " << select << " Deleted." << std::endl;

	endGraceful();
}

void library::streamOut(int _signature, std::string _vesselName, BaseVessel *vesselPtr)
{
	std::cout << std::endl
		 << "-Vessel Data-" << std::endl
		 << std::endl;

	std::cout << "Acoustic Signature: " << _signature << std::endl;

	vesselPtr->Display(std::cout);

	std::cout << std::endl;
}

void library::endGraceful()
{
	std::cout << std::endl
		 << "Press any 'y' to return" << std::endl;

	auto confirm = 'a'; //something that isnt y

	while (confirm != 'y')
	{
		cin >> confirm;
	}

	system("CLS");
}

int library::validateCin()
{
	int checkVar;
	while (!(cin >> checkVar))
	{
		std::cout << "INCORRECT INPUT" << std::endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout << ">" << std::endl;
	}
	return checkVar;
}
