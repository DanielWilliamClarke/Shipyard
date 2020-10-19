#pragma once
#include "Vessel.h"
#include <string>

class Node
{
public:
	//constructor and deconstructor
	Node();
	
	//node key will act as ships signature
	int generateKey(void);
	void setKey(int newKey);
	int getKey(void);
	//name of ship -> will be easier for searching
	void setVesselName(std::string newName);
	std::string getVesselName(void);

	//instance of the vessels are attached via void pointer
	void setVesselPtr(BaseVessel* newVesselPtr);
	BaseVessel* getVesselPtr(void);

	//set and get parents
	void setParent(Node *parent);
	Node* getParent(void);

	//to set and get the next left node in the tree
	void setNextLeft(Node *nextLeft);
	Node* getNextLeft(void);

	//set and get the next right node in the tree
	void setNextRight(Node *nextRight);
	Node* getNextRight(void);

	//colour types for redblack implementation
	void setColour(bool Colour);
	bool getColour(void);

private:

	int _key; //ship signature
	std::string _vesselName;
	BaseVessel *_vesselPtr; //allows data to be put in tree regardless of type
	Node *_parent; //pointer to node parent
	Node *_nextLeft; //pointer to the next left node
	Node *_nextRight;// pointer to next right node
	bool _Colour; // red is true, black is false
	
};