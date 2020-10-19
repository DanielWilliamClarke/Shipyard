#pragma once
#include "Main.h"
#include "RedBlackTree.h"
#include <String>

using namespace std;

class library
{
private:
		
	int _select; //menu selection variable
	char _confirm; //endGraceful() termination char

	//insertion variables
	int _signature;
	std::string _newName;
	//base
	unsigned int _newSpeed;
	unsigned int _newLength;
	unsigned int _newRange;
	unsigned int _newDisp;
	unsigned int _newCrew;
	//surface vessel
	unsigned int _newHeli;
	//aircraft carrier 
	unsigned int _newAircraft;
	//destroyer
	std::string _newWep;
	//FleetAux
	unsigned int _newDeck;
	//tanker 
	unsigned int _newCapL;
	//laning play
	unsigned int _newCapM3;
	//submarine
	unsigned int _newDiveDepth;
	unsigned int _newSubSpeed;
	unsigned int _newSubDisp;
	//ballistic sub
	unsigned int _newSLBM;
	//attack sub
	unsigned int _newTorpedos;

	int _keyToFind;
	double _percentage;
	double _max;
	std::string _searchName;

public:

	void filltree();

	//hydrophone function set up and finish
	void hydrophoneSim();
	void Percent(Node* node, double percentage);

	//insert and edit functions
	void insertVessel();
	void selectEditVessel();
	BaseVessel* fillVesselPtr();
	
	std::string setName();
	//base class data members
	void setBV(); 
	//1nd level derived members
	void setSF(); 
	void setSub(); 
	//2nd level derived members
	void setFleetAux();
	void setAC(); 
	void setDestroyer();
	void setBSub();
	void setASub();
	//3rd level derived members	
	void setTanker();
	void setLandPlat();

	void sizeOfList();

	//printing functions
	void printVessels();
	void printDerivedData(BaseVessel* vesselPtr);
	void streamOut(int key, std::string vesselName, BaseVessel* vesselPtr);

	//get by name or signature
	void getVessel();
	
	//delete vessel by signature
	void deleteVessel();

	//formatting and input validation functions
	void endGraceful();
	int validateCin();

	//TO DO 
	//XML SAVING
	//GUI

};