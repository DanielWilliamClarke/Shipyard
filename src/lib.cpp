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

void library::filltree()
{
	AircraftCarrier *AC = new AircraftCarrier("AC", 45, 700, 10000, 20000, 400, 4, 20);
	MyList.insert(rand() % 9999, "a", AC);
	AC = new AircraftCarrier("AC", 30, 650, 7000, 15000, 200, 5, 15);
	MyList.insert(rand() % 9999, "b", AC);
	AC = new AircraftCarrier("AC", 20, 800, 8000, 12000, 125, 3, 10);
	MyList.insert(rand() % 9999, "c", AC);
	AC = new AircraftCarrier("AC", 24, 400, 9000, 10000, 225, 5, 12);
	MyList.insert(rand() % 9999, "d", AC);
	AC = new AircraftCarrier("AC", 30, 400, 7500, 12050, 150, 2, 7);
	MyList.insert(rand() % 9999, "e", AC);
	AC = new AircraftCarrier("AC", 35, 500, 6500, 9000, 300, 5, 20);
	MyList.insert(rand() % 9999, "f", AC);
	AC = new AircraftCarrier("AC", 60, 550, 9500, 10000, 325, 7, 2);
	MyList.insert(rand() % 9999, "g", AC);
	AC = new AircraftCarrier("AC", 15, 1000, 15000, 20000, 400, 4, 10);
	MyList.insert(rand() % 9999, "h", AC);
	AC = new AircraftCarrier("AC", 50, 1200, 20000, 15000, 200, 8, 12);
	MyList.insert(rand() % 9999, "i", AC);
}
void library::hydrophoneSim()
{
	system("CLS");

	cout << "-Listening on Hydrophone-" << endl
		 << endl;

	_signature = MyNode.generateKey();

	cout << "Acoustic Signature detected! : " << _signature << endl
		 << "Checking System for Possible Match..." << endl
		 << endl;

	MyList.hydrophone(_signature);
}
void library::Percent(Node *node, double percentage)
{
	if (percentage > 65)
	{
		cout << "Closest Match to: " << node->getKey() << " with " << setprecision(4) << percentage << "%" << endl
			 << endl;
		streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
	}
	else
		cout << "Signature is Unidentified" << endl
			 << "Only a " << setprecision(4) << percentage << "% Match to a Vessel in the System" << endl
			 << "Could Not Make Comparison" << endl
			 << endl;
}
void library::insertVessel()
{
	system("CLS");

	//these Data Members can never be changed once entered
	cout << "-Insert Vessel-" << endl
		 << endl;
	_signature = MyNode.generateKey();
	cout << "Vessel's Acoustic Signature: " << _signature << endl
		 << endl;
	_newName = setName();
	cout << endl;

	MyList.insert(_signature, _newName, fillVesselPtr());

	endGraceful();
}
void library::selectEditVessel()
{
	system("CLS");

	cout << "-Edit Vessel-" << endl
		 << endl;

	cout << "What would you like to Edit?" << endl
		 << endl;

	cout << "1. VesselName" << endl
		 << "2. Vessel Data" << endl
		 << ">";

	while (true)
	{
		_select = validateCin();
		if ((_select < 1) || (_select > 2))
			cout << "INCORRECT INPUT" << endl
				 << endl;
		else
			break;
	}

	cout << "Enter an ID to edit" << endl;
	cout << ">";
	_keyToFind = validateCin();
	cout << endl;

	if (_select == 1)
	{
		MyList.editNodeName(_keyToFind);
		cout << "Vessel Name Edited" << endl;
	}
	else
		MyList.editNode(_keyToFind);

	endGraceful();
}
BaseVessel *library::fillVesselPtr()
{
	BaseVessel *returnPtr;

	cout << "What type of Vessel would you like to insert" << endl
		 << endl
		 << "Surface Vessels" << endl
		 << "1. AirCraft Carrier" << endl
		 << "2. Destroyer" << endl
		 << "Fleet Auxiliaries" << endl
		 << "3. Tanker" << endl
		 << "4. Landing Platform Dock" << endl
		 << "Submarines" << endl
		 << "5. Ballistic Sub" << endl
		 << "6. Attack Sub" << endl
		 << ">";

	while (true)
	{
		_select = validateCin();
		if ((_select < 1) || (_select > 6))
			cout << "INCORRECT INPUT" << endl
				 << endl;
		else
			break;
	}

	cout << endl;

	switch (_select)
	{
	case 1:
	{
		cout << "You Chose 'Aircraft Carrier'" << endl
			 << endl;
		setBV();
		setSF();
		setAC();
		AircraftCarrier *AC = new AircraftCarrier("AC", _newSpeed, _newLength, _newRange, _newDisp, _newCrew, _newHeli, _newAircraft);
		//pass object to tree insert function
		returnPtr = AC;
		break;
	}
	case 2:
	{
		cout << "You Chose 'Destroyer'" << endl
			 << endl;
		setBV();
		setSF();
		setDestroyer();
		//create new instance of vessel and call constructor
		Destroyer *Destroy = new Destroyer("D", _newSpeed, _newLength, _newRange, _newDisp, _newCrew, _newHeli, _newWep);
		//pass object to tree insert function
		returnPtr = Destroy;
		break;
	}
	case 3:
	{
		cout << "You Chose 'Tanker'" << endl
			 << endl;
		setBV();
		setSF();
		setFleetAux();
		setTanker();
		//create new instance of vessel and call constructor
		Tanker *Tank = new Tanker("T", _newSpeed, _newLength, _newRange, _newDisp, _newCrew, _newHeli, _newDeck, _newCapL);
		//pass object to tree insert function7
		returnPtr = Tank;
		break;
	}
	case 4:
	{
		cout << "You Chose 'Landing Platform Dock'" << endl
			 << endl;
		setBV();
		setSF();
		setFleetAux();
		setLandPlat();
		//create new instance of vessel and call constructor
		LandingPlat *LP = new LandingPlat("LP", _newSpeed, _newLength, _newRange, _newDisp, _newCrew, _newHeli, _newDeck, _newCapM3);
		//pass object to tree insert function
		returnPtr = LP;
		break;
	}
	case 5:
	{
		cout << "You Chose 'Ballistic Submarine'" << endl
			 << endl;
		setBV();
		setSub();
		setBSub();
		//create new instance of vessel and call constructor
		BallisticSub *BS = new BallisticSub("BS", _newSpeed, _newLength, _newRange, _newDisp, _newCrew, _newDiveDepth, _newSubSpeed, _newSubDisp, _newSLBM);
		//pass object to tree insert function
		returnPtr = BS;
		break;
	}
	case 6:
	{
		cout << "You Chose 'Attack Submarine'" << endl
			 << endl;
		setBV();
		setSub();
		setASub();
		//create new instance of vessel and call constructor
		AttackSub *AS = new AttackSub("AS", _newSpeed, _newLength, _newRange, _newDisp, _newCrew, _newDiveDepth, _newSubSpeed, _newSubDisp, _newTorpedos);
		//pass object to tree insert function
		returnPtr = AS;
		break;
	}
	}

	cout << endl
		 << "Vessel Written" << endl;

	return returnPtr;
}
std::string library::setName()
{
	cout << "Enter Name: " << endl;
	cout << "> ";
	cin >> _newName;

	return _newName; //to make each vessel HMS "something"
}
void library::setBV()
{
	cout << "Enter Speed (Knots): " << endl;
	cout << ">";
	_newSpeed = validateCin();
	cout << "Enter Length (Metres): " << endl;
	cout << ">";
	_newLength = validateCin();
	cout << "Enter Range (Nautical Miles): " << endl;
	cout << ">";
	_newRange = validateCin();
	cout << "Enter Displacement (Tons): " << endl;
	cout << ">";
	_newDisp = validateCin();
	cout << "Enter Crew Size: " << endl;
	cout << ">";
	_newCrew = validateCin();
}
void library::setSF()
{
	cout << "Enter No. Helicopters: " << endl;
	cout << ">";
	_newHeli = validateCin();
}
void library::setSub()
{
	cout << "Enter Dive Depth (Metres): " << endl;
	cout << ">";
	_newDiveDepth = validateCin();
	cout << "Enter Submerged Speed (Knots): " << endl;
	cout << ">";
	_newSubSpeed = validateCin();
	cout << "Enter Submerged Displacement (Tons): " << endl;
	cout << ">";
	_newSubDisp = validateCin();
}
void library::setFleetAux()
{
	cout << "Enter Deck Size (Metres): " << endl;
	cout << ">";
	_newDeck = validateCin();
}
void library::setAC()
{
	cout << "Enter No. Aircraft: " << endl;
	cout << ">";
	_newAircraft = validateCin();
}
void library::setDestroyer()
{
	cout << "Please Select Weapon System: " << endl;
	cout << "1. Gun System" << endl;
	cout << "2. Guided Missle System" << endl;
	cout << ">";

	while (true)
	{
		_select = validateCin();
		if (_select == 1)
		{
			_newWep = "Gun System";
			break;
		}
		if (_select == 2)
		{
			_newWep = "Guilded Missle System";
			break;
		}
	}
	cout << endl
		 << "You Chose: " << _newWep << endl;
}
void library::setTanker()
{
	cout << "Enter Capacity (Litres): " << endl;
	cout << ">";
	_newCapL = validateCin();
}
void library::setLandPlat()
{
	cout << "Enter Capacity (Cubic Metres): " << endl;
	cout << ">";
	_newCapM3 = validateCin();
}
void library::setBSub()
{
	cout << "Enter No. SLBM: " << endl;
	cout << ">";
	_newSLBM = validateCin();
}
void library::setASub()
{
	cout << "Enter No. Torpedos: " << endl;
	cout << ">";
	_newTorpedos = validateCin();
}
void library::sizeOfList()
{
	cout << "There is/are " << MyList.size() << " Vessels(s) on the System" << endl;
	endGraceful();
}
void library::printVessels()
{
	system("CLS");
	cout << "-Vessel Print-" << endl
		 << endl;
	cout << "In which order would you like to print" << endl
		 << "1. In Order" << endl
		 << "2. Post Order" << endl
		 << "3. No Order" << endl
		 << ">";

	while (true)
	{
		_select = validateCin();
		if ((_select < 1) || (_select > 3))
			cout << "INCORRECT INPUT" << endl
				 << endl;
		else
		{
			MyList.publicPrint(_select);
			break;
		}
	}

	cout << endl;

	endGraceful();
}
void library::getVessel()
{
	system("CLS");

	cout << "-System Search-" << endl
		 << endl;

	cout << "How would you like to search" << endl
		 << "1. By Signature" << endl
		 << "2. By Name" << endl
		 << ">";

	while (true)
	{
		_select = validateCin();
		if ((_select < 1) || (_select > 2))
			cout << "INCORRECT INPUT" << endl
				 << endl;
		else
			break;
	}

	if (_select == 1)
	{
		cout << "Please Enter an ID:" << endl;
		cout << ">";

		_select = validateCin();

		MyList.FindVesselID(_select);

		cout << endl;
	}
	else
	{
		cout << "Please Enter a Name:" << endl;
		cout << ">";

		cin >> _searchName;

		MyList.findVesselName(_searchName);

		cout << endl;
	}

	endGraceful();
}

void library::deleteVessel()
{
	system("CLS");

	cout << "-Delete Vessel-" << endl
		 << endl;

	cout << "Please Enter ID to Delete Vessel" << endl;
	cout << ">";

	_select = validateCin();

	MyList.deletePublic(_select);

	cout << "Vessel With ID " << _select << " Deleted." << endl;

	endGraceful();
}
void library::streamOut(int _signature, std::string _vesselName, BaseVessel *vesselPtr)
{
	cout << endl
		 << "-Vessel Data-" << endl
		 << endl;

	cout << "Acoustic Signature: " << _signature << endl
		 << "Vessel Name: " << _vesselName << endl
		 << endl
		 << "Max Speed: " << vesselPtr->getSpeed() << endl
		 << "Lenght: " << vesselPtr->getLength() << endl
		 << "Max Range: " << vesselPtr->getRange() << endl
		 << "Displacement: " << vesselPtr->getDisp() << endl
		 << "Crew Size: " << vesselPtr->getCrew() << endl
		 << endl;

	printDerivedData(vesselPtr);

	cout << endl;
}
void library::printDerivedData(BaseVessel *vesselPtr)
{
	if (vesselPtr->getVesselType() == "AC")
	{
		AircraftCarrier *AC = static_cast<AircraftCarrier *>(vesselPtr);
		cout << "No. Helicopters: " << AC->getHeli() << endl
			 << "No. Aircraft: " << AC->getCraft() << endl;
	}
	if (vesselPtr->getVesselType() == "D")
	{
		Destroyer *D = static_cast<Destroyer *>(vesselPtr);
		cout << "No. Helicopters: " << D->getHeli() << endl
			 << "Weapon System: " << D->getWep() << endl;
	}
	if (vesselPtr->getVesselType() == "T")
	{
		Tanker *T = static_cast<Tanker *>(vesselPtr);
		cout << "No. Helicopters: " << T->getHeli() << endl
			 << "Desk Size: " << T->getDeck() << endl
			 << "Capacity in Litres: " << T->getCapL() << endl;
	}
	if (vesselPtr->getVesselType() == "LP")
	{
		LandingPlat *LP = static_cast<LandingPlat *>(vesselPtr);
		cout << "No. Helicopters: " << LP->getHeli() << endl
			 << "Desk Size: " << LP->getDeck() << endl
			 << "Capcity in Cubic Metres: " << LP->getCapM3() << endl;
	}
	if (vesselPtr->getVesselType() == "BS")
	{
		BallisticSub *BS = static_cast<BallisticSub *>(vesselPtr);
		cout << "Maximum Dive Depth: " << BS->getDiveDepth() << endl
			 << "Maximum Submerged Speed: " << BS->getSubSpeed() << endl
			 << "Submerged Displacement: " << BS->getSubDisp() << endl
			 << "No. SLBM: " << BS->getSLBM() << endl;
	}
	if (vesselPtr->getVesselType() == "AS")
	{
		AttackSub *AS = static_cast<AttackSub *>(vesselPtr);
		cout << "Maximum Dive Depth: " << AS->getDiveDepth() << endl
			 << "Maximum Submerged Speed: " << AS->getSubSpeed() << endl
			 << "Submerged Displacement: " << AS->getSubDisp() << endl
			 << "No. Torpedos: " << AS->getTorpedos() << endl;
	}
}
void library::endGraceful()
{
	cout << endl
		 << "Press any 'y' to return" << endl;

	_confirm = 'a'; //something that isnt y

	while (_confirm != 'y')
	{
		cin >> _confirm;
	}

	system("CLS");
}
int library::validateCin()
{
	int checkVar;
	while (!(cin >> checkVar))
	{
		cout << "INCORRECT INPUT" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << ">" << endl;
	}
	return checkVar;
}
