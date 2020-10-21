#include "Node.h"
#include "Vessel.h"

Node::Node(int key, BaseVessel* vessel, Node* parent)
	: key(key), vessel(vessel), parent(parent), left(nullptr), right(nullptr), colour(false)
{
}

//getters and setters
int Node::GenerateKey()
{
	return rand() % 9999;
}

int Node::GetKey() const
{
	return key;
}

void Node::SetVessel(BaseVessel* v)
{
	vessel = v;
}

BaseVessel* Node::GetVessel() const
{
	return vessel;
}

void Node::SetParent(Node *p)
{
	parent = p;
}

Node* Node::GetParent() const
{
	return parent;
}

void Node::SetNextLeft(Node *l)
{
	left = l;
}

Node* Node::GetNextLeft() const
{
	return left;
}

void Node::SetNextRight(Node *ptr)
{
	right = ptr;
}

Node* Node::GetNextRight() const
{
	return right;
}

void Node::SetColour(bool c)
{
	colour = c;
}

bool Node::GetColour() const
{
	return colour;
}