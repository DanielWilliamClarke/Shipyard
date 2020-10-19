// File: Node.cpp
// Version: V1.1 
// Date: 04/04/2012
// Name: Daniel Clarke - Computer Science 
// ID: n0271538
// This program hold the setter and getter functions for the private data members held with in the class Node
// Modification history: 
// V1.1 4/4/2012

#include "Node.h"
#include <time.h>

Node::Node()
{
	//initialise the left and right node pointers
	_nextLeft = NULL;
	_nextRight = NULL;
	_parent = NULL;
}
//getters and setters
int Node::generateKey()
{
	return rand() % 9999;
}
void Node::setKey(int newKey)
{
	_key = newKey;
}
int Node::getKey()
{
	return _key;
}
void Node::setVesselName(std::string newName)
{
	_vesselName = newName;
}
std::string Node::getVesselName()
{
	return _vesselName;
}
void Node::setVesselPtr(BaseVessel *newVesselPtr)
{
	_vesselPtr = newVesselPtr;
}
BaseVessel* Node::getVesselPtr()
{
	return _vesselPtr;
}
void Node::setParent(Node *ptr)
{
	_parent = ptr;
}
Node* Node::getParent()
{
	return _parent;
}
void Node::setNextLeft(Node *ptr)
{
	_nextLeft = ptr;
}
Node* Node::getNextLeft(void)
{
	return _nextLeft;
}
void Node::setNextRight(Node *ptr)
{
	_nextRight = ptr;
}
Node* Node::getNextRight(void)
{
	return _nextRight;
}
void Node::setColour(bool newColour)
{
	_Colour = newColour;
}
bool Node::getColour(void)
{
	return _Colour;
}