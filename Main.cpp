// File: Main.cpp
// Version: V1.1 
// Date: 04/04/2012
// Name: Daniel Clarke - Computer Science 
// ID: n0271538
// This program contains main(), and is the top layer where the user interacts with the system
// Modification history: 
// V1.1 4/4/2012

#include "stdafx.h"

#include "Main.h"
#include "RedBlackTree.h"
#include "lib.h"

//cin, cout stuff
#include <iostream>
#include <iomanip>
#include <limits>
#include <time.h>

using namespace std;

	library lib;

int main()
{
	srand((unsigned)time(NULL));
	int selection = 0;
	int selectID = 0;
	
	lib.filltree();

	while(selection != 8)
	{
		cout << endl
			 << "Welcome" << endl
			 << endl
			 << "1. Add Vessel to System" << endl
			 << "2. No. Vessels In System" << endl
			 << "3. Edit Vessel in System" << endl
			 << "4. Print System" << endl
			 << "5. Get Vessel from System" << endl
			 << "6. Delete Vessel from System" << endl
			 << "7. Simulate Hydrophone" << endl
			 << endl
			 << "8. Exit" << endl
			 << endl
			 << "Please Enter a Selection" << endl  
			 << ">";

		while(!(cin >> selection)) // validation for user input
		{
			cout << "INCORRECT INPUT" << endl;
			cin.clear(); // clears cin 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores all items input
			cout << endl <<  "Please Enter a Selection" << endl
			<< ">"; //redisplays the message
		}
		
		cout << endl;

		cout <<"You entered: " << selection << endl << endl;

		switch(selection)
		{
		case 1:

			try
			{
				lib.insertVessel();
			}
			catch(exception& ex)
			{
				cout << "Error: " << ex.what() << endl;
				lib.endGraceful();
			}
			break;

		case 2:

			try
			{	
				lib.sizeOfList();
			}
			catch(exception& ex)
			{
				cout << "Error: " << ex.what() << endl;
				lib.endGraceful();
			}
			break;

		case 3:

			try
			{
				lib.selectEditVessel();
			}
			catch(exception& ex)
			{
				cout << "Error: " << ex.what() << endl;
				lib.endGraceful();
			}
			break;

		case 4:
			
			try
			{
				lib.printVessels();
			}
			catch(exception& ex)
			{
				cout<< "Error: "<< ex.what() << endl;
				lib.endGraceful();
			}
			break;

		case 5:

			try
			{
				lib.getVessel();
			}
			catch(exception& ex)
			{
				cout << "Error: " << ex.what() << endl;
				lib.endGraceful();
			}
			break;

		case 6:

			try
			{
				lib.deleteVessel();
			}
			catch(exception& ex)
			{
				cout<< "Error: " << ex.what() << endl;
				lib.endGraceful();
			}
			break;

		case 7:

			try
			{
				lib.hydrophoneSim();
			}
			catch(exception& ex)
			{
				cout << ex.what() << endl;
				lib.endGraceful();
			}
			break;
			
		}
	}

return 0;

}

int _tmain(int argc, _TCHAR* argv[])
{
	main();
	return 0;
}

	

