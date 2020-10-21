#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <time.h>
#include <map>
#include <functional>
#include <algorithm>

#include "lib.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "Vessel.h"

Library::Library(std::shared_ptr<BinaryTree> tree) 
	: tree(tree)
{}

void Library::InsertVessel() const
{
	auto signature = Node::GenerateKey();
	system("CLS");

	std::cout << "-Insert Vessel-" << std::endl
		<< std::endl << "Vessel's Acoustic Signature: " << signature << std::endl
		<< std::endl;

	this->tree->Insert(signature, FillVesselPtr());
	EndGraceful();
}

void Library::DeleteVessel() const
{
	system("CLS");

	std::cout << "-Delete Vessel-" << std::endl
		<< std::endl;

	std::cout << "Please Enter ID to Delete Vessel" << std::endl;
	std::cout << ">";
	auto select = ValidateCin();

	std::cout << "Vessel With ID " << select << " Deleted." << std::endl;
	this->tree->DeletePublic(select);
	EndGraceful();
}

std::string Library::SetName() const
{
	std::cout << "Enter Name: " << std::endl;
	std::cout << "> ";
	auto newName = std::string("");
	std::cin >> newName;
	return newName; //to make each vessel HMS "something"
}

void Library::SizeOfList() const
{
	std::cout << "There is/are " << this->tree->Size() << " Vessels(s) on the System" << std::endl;
	EndGraceful();
}

void Library::PrintVessels() const
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
		select = ValidateCin();
		if ((select < 1) || (select > 3))
		{
			std::cout << "INCORRECT INPUT" << std::endl
				<< std::endl;
			continue;
		}
		break;
	}

	this->tree->PublicPrint(select);
	EndGraceful();
}

void Library::SelectEditVessel() const
{
	system("CLS");

	std::cout << "Enter an ID to edit" << std::endl;
	std::cout << ">";
	auto keyToFind = ValidateCin();
	std::cout << std::endl;

	std::map<int, std::pair<std::string, std::function<void(void)>>> options{
		{1, std::make_pair("Vessel Data", [&](void) -> void { 
			this->tree->EditNode(keyToFind, nullptr);
		})},
	};

	std::cout << "-Edit Vessel-" << std::endl
		<< std::endl << "What would you like to Edit?" << std::endl;
	std::for_each(options.begin(), options.end(), [&](std::pair<int, std::pair<std::string, std::function<void(void)>>> option) {
		std::cout << option.first << ". " << option.second.first << std::endl;
	});
	
	int selection = 0;
	for (;;) {
		std::cout << std::endl
			<< "Please Enter a Selection" << std::endl
			<< ">"; 
		selection = ValidateCin();
		if (options.find(selection) == options.end())
		{
			std::cout << "INCORRECT INPUT" << std::endl;
			std::cin.clear();										 // clears cin
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores all items input
			continue;
		}
		break;
	}

	try
	{
		options[selection].second();
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}

	EndGraceful();
}

void Library::HydrophoneSim() const
{
	auto signature = Node::GenerateKey();

	system("CLS");
	std::cout << "-Listening on Hydrophone-" << std::endl
		<< std::endl << "Acoustic Signature detected! : " << signature << std::endl
		<< "Checking System for Possible Match..." << std::endl
		<< std::endl;

	this->tree->Hydrophone(signature);
}

void Library::GetVessel() const
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
		select = ValidateCin();
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

		select = ValidateCin();

		this->tree->FindVesselID(select);

		std::cout << std::endl;
	}
	else
	{
		std::cout << "Please Enter a Name:" << std::endl;
		std::cout << ">";

		auto searchName = std::string("");
		std::cin >> searchName;

		this->tree->FindVesselName(searchName);
		std::cout << std::endl;
	}

	EndGraceful();
}

void Library::Percent(Node* node, double percentage) const
{
	if (percentage > 65)
	{
		std::cout << "Closest Match to: " << node->GetKey() << " with " << std::setprecision(4) << percentage << "%" << std::endl
			<< std::endl;
		StreamOut(node->GetKey(), "fail", node->GetVessel());
		return;
	}
	std::cout << "Signature is Unidentified" << std::endl
		<< "Only a " << std::setprecision(4) << percentage << "% Match to a Vessel in the System" << std::endl
		<< "Could Not Make Comparison" << std::endl
		<< std::endl;
}


void Library::StreamOut(int _signature, std::string _vesselName, BaseVessel *vesselPtr) const
{
	std::cout << std::endl
		 << "-Vessel Data-" << std::endl
		 << std::endl;

	std::cout << "Acoustic Signature: " << _signature << std::endl;

	vesselPtr->Display(std::cout);

	std::cout << std::endl;
}

void Library::EndGraceful() const
{
	std::cout << std::endl
		 << "Press any 'y' to return" << std::endl;

	auto confirm = 'a'; //something that isnt y

	while (confirm != 'y')
	{
		std::cin >> confirm;
	}

	system("CLS");
}

int Library::ValidateCin() const
{
	int checkVar;
	while (!(std::cin >> checkVar))
	{
		std::cout << "INCORRECT INPUT" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ">" << std::endl;
	}
	return checkVar;
}

BaseVessel* Library::FillVesselPtr() const
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
		select = ValidateCin();
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