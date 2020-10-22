#include <iostream>
#include <time.h>
#include <map>
#include <functional>

#include "lib.h"
#include "RedBlackTree.h"

class ExitException : public std::exception
{
public:
	ExitException(std::string message)
		: message(message)
	{
	}
	virtual const char* what() const throw()
	{
		return message.c_str();
	}
private:
	std::string message;
};

int main()
{
	auto lib = std::make_unique<Library>(std::make_shared<BinaryTree>());
	std::map<int, std::pair<std::string, std::function<void(void)>>> options{
		{1, std::make_pair("Add Vessel to System", [&lib](void) -> void { lib->InsertVessel(); })},
		{2, std::make_pair("No. Vessels In System", [&lib](void) -> void { lib->Size(); })},
		{3, std::make_pair("Edit Vessel in System", [&lib](void) -> void { lib->SelectEditVessel(); })},
		{4, std::make_pair("Print System", [&lib](void) -> void { lib->PrintVessels(); })},
		{5, std::make_pair("Get Vessel from System", [&lib](void) -> void { lib->GetVessel(); })},
		{6, std::make_pair("Delete Vessel from System", [&lib](void) -> void { lib->DeleteVessel(); })},
		{7, std::make_pair("Simulate Hydrophone", [&lib](void) -> void { lib->Hydrophone(); })},
		{8, std::make_pair("Exit", [=](void) -> void { throw ExitException("Goodbye!"); })}
	};

	srand((unsigned)time(NULL));
	for(;;)
	{
		std::cout << "Welcome" << std::endl;
		lib->PrintOptions<int, std::string, std::function<void(void)>>("What would you like to do?", options);
		try
		{
			lib->MakeSelection<int, std::string, std::function<void(void)>>(options)();
		}
		catch (ExitException ex)
		{
			std::cout << "Exiting: " << ex.what() << std::endl;
			lib->EndGraceful();
			break;
		}
		catch (std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
			lib->EndGraceful();
		}
	}

	return 0;
}