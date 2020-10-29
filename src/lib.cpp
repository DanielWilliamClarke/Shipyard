#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <functional>
#include <algorithm>
#include <random>

#include "lib.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "Vessel.h"
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

	this->tree->Insert(new Node(FillVessel(), nullptr));

	auto node = this->tree->FindVessel(signature);
	StreamOut(node->GetVessel());

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
	std::map<int, std::pair<std::string, BinaryTree::TRAVERSAL_ALGO>> options {
		{ 1, std::make_pair("In Order", BinaryTree::TRAVERSAL_ALGO::INORDER) },
		{ 2, std::make_pair("Reverse", BinaryTree::TRAVERSAL_ALGO::REVERSE) },
		{ 3, std::make_pair("No Order", BinaryTree::TRAVERSAL_ALGO::TOPDOWN) },
	};

	PrintOptions<int, std::string, BinaryTree::TRAVERSAL_ALGO>("-Print Vessels-", options);

	this->tree->Traverse(
		MakeSelection<int, std::string, BinaryTree::TRAVERSAL_ALGO>(options),
		[=](Node* node) {
			StreamOut(node->GetVessel());
		});

	EndGraceful();
}

void Library::SelectEditVessel() const
{
	system("CLS");
	std::map<int, std::pair<std::string, std::function<void(void)>>> options{
		{1, std::make_pair("Vessel Data", [&](void) -> void { 
			std::cout << "Enter an ID to edit" << std::endl << ">";
			auto node = this->tree->FindVessel(ValidateCin());
			node->SetVessel(FillVessel());
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

void Library::GenerateRandomTree() const
{
	std::cout << "Please Enter Total Number of Vessels" << std::endl;
	std::cout << ">";
	auto totalVessels = ValidateCin();

	std::random_device device;
	std::mt19937 source(device());

	const int min = 0, max = 1000000;

	std::uniform_int_distribution<unsigned int> dist(min, max);

	// This is gross will refactor
	std::vector<std::function<BaseVessel* (unsigned int signature)>> vesselTypes {
		{ [&](unsigned int signature) { return new AircraftCarrier(signature, "Aircraft Carrier-" + std::to_string(signature), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source)); } },

		{ [&](unsigned int signature) { return new Destroyer(signature, "Destroyer-" + std::to_string(signature), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), "Bombs"); } },

		{ [&](unsigned int signature) { return new Tanker(signature, "Tanker-" + std::to_string(signature), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source)); } },

		{ [&](unsigned int signature) { return new LandingPlat(signature, "LandingPlat-" + std::to_string(signature), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source)); } },

		{ [&](unsigned int signature) { return new BallisticSub(signature, "BallisticSub-" + std::to_string(signature), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source)); } },

		{ [&](unsigned int signature) { return new AttackSub(signature, "AttackSub-" + std::to_string(signature), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source), dist(source)); } }
	};

	std::uniform_int_distribution<size_t> vesselDist(0, vesselTypes.size() - 1);
	for (int index = 0; index < totalVessels; index++) 
	{
		this->tree->Insert(
			new Node(
				vesselTypes.at(vesselDist(source))(dist(source))));
	}
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
			StreamOut(node->GetVessel());
		})},
		{2, std::make_pair("By Name", [&]() {
			std::cout << "Please Enter a Name:" << std::endl << ">";
			auto searchName = std::string("");
			std::cin >> searchName;
			auto node = this->tree->FindVessel(searchName);
			StreamOut(node->GetVessel());
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
	auto signature = Node::GenerateKey();

	std::map<int, std::pair<std::string, std::function<BaseVessel*(void)>>> options{
		{1, std::make_pair("AirCraft Carrier", [&]() { return new AircraftCarrier(signature, std::cin); })},
		{2, std::make_pair("Destroyer", [&]() { return new Destroyer(signature, std::cin); })},
		{3, std::make_pair("Tanker", [&]() { return new Tanker(signature, std::cin); })},
		{4, std::make_pair("Landing Platform Dock", [&]() { return new LandingPlat(signature, std::cin); })},
		{5, std::make_pair("Ballistic Submarine", [&]() { return new BallisticSub(signature, std::cin); })},
		{6, std::make_pair("Attack Submarine", [&]() { return new AttackSub(signature, std::cin); })}
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
		std::cout << std::endl << ">";
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

void Library::StreamOut(BaseVessel* vessel) const
{
	std::cout << std::endl
		<< "-Vessel Data-" << std::endl
		<< std::endl;
	vessel->Display(std::cout);
}

void Library::StreamPercent(std::pair<Node*, float> closest) const
{
	if (closest.first != nullptr && closest.second > 65)
	{
		std::cout << "Closest Match to: " << closest.first->GetVessel()->GetSignature() << " with " << std::setprecision(4) << closest.second << "%"
			<< std::endl << std::endl;
		StreamOut(closest.first->GetVessel());
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