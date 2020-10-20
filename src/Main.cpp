
//cin, cout stuff
#include <iostream>
#include <iomanip>
#include <limits>
#include <time.h>
#include <map>
#include <functional>

#include "lib.h"
#include "RedBlackTree.h"

int main()
{
	auto lib = std::make_shared<library>();
	std::map<int, std::function<void(void)>> options{
		{1, [&lib](void) -> void { lib->insertVessel(); }},
		{2, [&lib](void) -> void { lib->sizeOfList(); }},
		{3, [&lib](void) -> void { lib->selectEditVessel(); }},
		{4, [&lib](void) -> void { lib->printVessels(); }},
		{5, [&lib](void) -> void { lib->getVessel(); }},
		{6, [&lib](void) -> void { lib->deleteVessel(); }},
		{6, [&lib](void) -> void { lib->hydrophoneSim(); }},
	};

	srand((unsigned)time(NULL));
	int selection = 0;
	int selectID = 0;

	while (selection != 8)
	{
		std::cout << std::endl
			 << "Welcome" << std::endl
			 << std::endl
			 << "1. Add Vessel to System" << std::endl
			 << "2. No. Vessels In System" << std::endl
			 << "3. Edit Vessel in System" << std::endl
			 << "4. Print System" << std::endl
			 << "5. Get Vessel from System" << std::endl
			 << "6. Delete Vessel from System" << std::endl
			 << "7. Simulate Hydrophone" << std::endl
			 << std::endl
			 << "8. Exit" << std::endl
			 << std::endl
			 << "Please Enter a Selection" << std::endl
			 << ">";

		while (!(std::cin >> selection)) // validation for user input
		{
			std::cout << "INCORRECT INPUT" << std::endl;
			std::cin.clear();										 // clears cin
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores all items input
			std::cout << std::endl
				 << "Please Enter a Selection" << std::endl
				 << ">"; //redisplays the message
		}

		std::cout << std::endl 
			<< "You entered: " << selection << std::endl
			<< std::endl;

		try
		{
			options[selection]();
		}
		catch (std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
			lib->endGraceful();
		}
	}

	return 0;
}