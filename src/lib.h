#pragma once

#include <string>

class Node;
class BaseVessel;

class library
{
public:

	//hydrophone function set up and finish
	void hydrophoneSim();
	void Percent(Node* node, double percentage);

	//insert and edit functions
	void insertVessel();
	void selectEditVessel();
	BaseVessel* fillVesselPtr();
	
	std::string setName();

	void sizeOfList();

	//printing functions
	void printVessels();
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