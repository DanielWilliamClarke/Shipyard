#include <iostream>
#include <iomanip>
#include <limits>
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
		<< std::endl << "Vessel's Acoustic Signature: " << signature << std::endl;

	this->tree->Insert(signature, FillVessel());
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
	this->tree->Delete(select);
	EndGraceful();
}

void Library::Size() const
{
	std::cout << this->tree->Size() << " Vessels(s) in the System" << std::endl;
	EndGraceful();
}

void Library::PrintVessels() const
{
	std::map<int, std::pair<std::string, BinaryTree::PRINTMODE>> options {
		{ 1, std::make_pair("In Order", BinaryTree::PRINTMODE::ASC) },
		{ 2, std::make_pair("Post Order", BinaryTree::PRINTMODE::DESC) },
		{ 3, std::make_pair("No Order", BinaryTree::PRINTMODE::NON) },
	};

	PrintOptions<int, std::string, BinaryTree::PRINTMODE>("-Print Vessels-", options);

	this->tree->Print(
		MakeSelection<int, std::string, BinaryTree::PRINTMODE>(options),
		[=](Node* node) {
			StreamOut(node->GetKey(), node->GetVessel());
		});

	EndGraceful();
}

void Library::SelectEditVessel() const
{
	system("CLS");
	std::cout << "Enter an ID to edit" << std::endl << ">";
	auto keyToFind = ValidateCin();

	std::map<int, std::pair<std::string, std::function<void(void)>>> options{
		{1, std::make_pair("Vessel Data", [&](void) -> void { 
			this->tree->EditNode(keyToFind, nullptr);
		})},
	};

	try
	{
		PrintOptions<int, std::string, std::function<void(void)>>("-Edit Vessels-", options);
		MakeSelection<int, std::string, std::function<void(void)>>(options)();
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}

	EndGraceful();
}

void Library::Hydrophone() const
{
	auto signature = Node::GenerateKey();

	system("CLS");
	std::cout << "-Listening on Hydrophone-" << std::endl
		<< std::endl << "Acoustic Signature detected! : " << signature << std::endl
		<< "Checking System for Possible Match..." << std::endl << std::endl;

	StreamPercent(this->tree->FindClosest(signature));

	EndGraceful();
}

void Library::GetVessel() const
{
	system("CLS");

	std::cout << "-System Search-" << std::endl
		 << std::endl;

	std::map<int, std::pair<std::string, std::function<void(void)>>> options {
		{1, std::make_pair("By Signature", [&]() {
			std::cout << "Please Enter an ID:" << std::endl << ">";
			auto node = this->tree->FindVessel(ValidateCin());
			StreamOut(node->GetKey(), node->GetVessel());
		})},
		{2, std::make_pair("By Name", [&]() {
			std::cout << "Please Enter a Name:" << std::endl << ">";
			auto searchName = std::string("");
			std::cin >> searchName;
			auto node = this->tree->FindVessel(searchName);
			StreamOut(node->GetKey(), node->GetVessel());
		})}
	};

	try
	{
		PrintOptions<int, std::string, std::function<void(void)>>("How would you like to search", options);
		MakeSelection<int, std::string, std::function<void(void)>>(options)();
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}

	EndGraceful();
}

BaseVessel* Library::FillVessel() const
{
	std::map<int, std::pair<std::string, std::function<BaseVessel*(void)>>> options{
		{1, std::make_pair("AirCraft Carrier", [&]() { return new AircraftCarrier(std::cin); })},
		{2, std::make_pair("Destroyer", [&]() { return new Destroyer(std::cin); })},
		{3, std::make_pair("Tanker", [&]() { return new Tanker(std::cin); })},
		{4, std::make_pair("Landing Platform Dock", [&]() { return new LandingPlat(std::cin); })},
		{5, std::make_pair("Ballistic Submarine", [&]() { return new BallisticSub(std::cin); })},
		{6, std::make_pair("Attack Submarine", [&]() { return new AttackSub(std::cin); })}
	};

	try
	{
		PrintOptions<int, std::string, std::function<BaseVessel* (void)>>("What type of Vessel would you like to insert", options);
		return MakeSelection<int, std::string, std::function<BaseVessel*(void)>>(options)();
	}
	catch (std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		return nullptr;
	}
}

template<class KEY, class OPTION, class DATA>
void Library::PrintOptions(std::string title, std::map<KEY, std::pair<OPTION, DATA>> options) const
{
	system("CLS");
	std::cout << title << std::endl;
	std::for_each(options.begin(), options.end(), [&](std::pair<KEY, std::pair<OPTION, DATA>> option) {
		std::cout << option.first << ". " << option.second.first << std::endl;
	});
}

template<class KEY, class OPTION, class DATA>
DATA Library::MakeSelection(std::map<KEY, std::pair<OPTION, DATA>> options) const
{
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

	return options[selection].second;
}

void Library::StreamOut(int signature, BaseVessel* vessel) const
{
	std::cout << std::endl
		<< "-Vessel Data-" << std::endl
		<< std::endl;

	std::cout << "Acoustic Signature: " << signature << std::endl;

	vessel->Display(std::cout);

	std::cout << std::endl;
}

void Library::StreamPercent(std::pair<Node*, float> closest) const
{
	if (closest.first != nullptr && closest.second > 65)
	{
		std::cout << "Closest Match to: " << closest.first->GetKey() << " with " << std::setprecision(4) << closest.second << "%"
			<< std::endl << std::endl;
		StreamOut(closest.first->GetKey(), closest.first->GetVessel());
		return;
	}

	std::cout << "Signature is Unidentified" << std::endl
		<< std::setprecision(4) << closest.second << "% Match to a Vessel in the System" << std::endl
		<< "Could Not Make Comparison" << std::endl
		<< std::endl;
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