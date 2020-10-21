
//cin, cout stuff
#include <iostream>
#include <iomanip>
#include <limits>
#include <time.h>
#include <map>
#include <functional>
#include <algorithm>

#include "lib.h"
#include "RedBlackTree.h"

int main()
{

	auto lib = std::make_unique<Library>(std::make_shared<BinaryTree>());
	std::map<int, std::pair<std::string, std::function<void(void)>>> options{
		{1, std::make_pair("Add Vessel to System", [&lib](void) -> void { lib->InsertVessel(); })},
		{2, std::make_pair("No. Vessels In System", [&lib](void) -> void { lib->SizeOfList(); })},
		{3, std::make_pair("Edit Vessel in System", [&lib](void) -> void { lib->SelectEditVessel(); })},
		{4, std::make_pair("Print System", [&lib](void) -> void { lib->PrintVessels(); })},
		{5, std::make_pair("Get Vessel from System", [&lib](void) -> void { lib->GetVessel(); })},
		{6, std::make_pair("Delete Vessel from System", [&lib](void) -> void { lib->DeleteVessel(); })},
		{7, std::make_pair("Simulate Hydrophone", [&lib](void) -> void { lib->HydrophoneSim(); })}
	};

	srand((unsigned)time(NULL));
	int selection = 0;
	while (selection != 8)
	{
		std::cout << "Welcome" << std::endl
			<< std::endl << "What would you like to do?" << std::endl;
		std::for_each(options.begin(), options.end(), [&](std::pair<int, std::pair<std::string, std::function<void(void)>>> option) {
			std::cout << option.first << ". " << option.second.first << std::endl;
		});

		int selection = 0;
		for (;;) {
			std::cout << std::endl
				<< "Please Enter a Selection" << std::endl
				<< ">";
			std::cin >> selection;
			if (options.find(selection) == options.end())
			{
				std::cout << "INCORRECT INPUT" << std::endl;
				std::cin.clear();										 // clears cin
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores all items input
				continue;
			}
			break;
		}

		std::cout << std::endl 
			<< "You Selected: " << options[selection].first << std::endl
			<< std::endl;

		try
		{
			options[selection].second();
		}
		catch (std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
			lib->EndGraceful();
		}
	}

	return 0;
}