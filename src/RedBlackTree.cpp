// File: RedBlackTree.cpp
// Version: V1.1
// Date: 04/04/2012
// Name: Daniel Clarke - Computer Science
// ID: n0271538
// This program contains functions which manipulate the pointers used in the Red Black Tree, it also contains the implementation functions for tree balancing.
// Modification history:
// V1.1 4/4/2012

#include "RedBlackTree.h"
#include "Node.h"
#include "lib.h"
#include "Vessel.h"

#include <typeinfo>
#include <string>

using namespace std;

BinaryTree::BinaryTree()
{
	root = NULL;
	foundFlag = false;
}

void BinaryTree::Insert(int key, BaseVessel* vessel)
{
	if (root != NULL)
	{
		InsertNode(FindRoot(root), key, vessel);
		return;
	}
	root = new Node(key, vessel);
	element++;
}

void BinaryTree::InsertNode(Node* node, int key, BaseVessel* vessel)
{
	if (key == node->GetKey())
	{
		throw exception(DUPLICATE);
	}		

	if (node->GetKey() > key) //compare key in tree
	{
		if (node->GetNextLeft() != NULL)
		{
			InsertNode(node->GetNextLeft(), key, vessel);
		}
		else
		{
			node->SetNextLeft(new Node(key, vessel, node));
			element++;
		}
	}
	else
	{
		if (node->GetNextRight() != NULL)
		{
			InsertNode(node->GetNextRight(), key, vessel);
		}
		else
		{
			node->SetNextRight(new Node(key, vessel, node));
			element++;
		}
	}

	InsertCase1(node); // get the red black rolling on node Inserted to tree
}

void BinaryTree::EditNode(int key, BaseVessel* vesselPtr)
{
	Find(FindRoot(root), key)->SetVessel(vesselPtr);
}

int BinaryTree::Size()
{
	if (element != 0)
	{
		return element;
	}
	throw exception(ERRORMSG);
}

Node *BinaryTree::Find(Node *node, int idFind)
{
	if (node == NULL)
	{
		throw exception(UNFOUND);
	}
	
	if (node->GetKey() == idFind)
	{
		return node;
	}

	if (node->GetKey() < idFind)
	{
		return Find(node->GetNextRight(), idFind);
	}
	return Find(node->GetNextLeft(), idFind);
}

Node *BinaryTree::FindClosestMatch(Node *node, int idFind)
{
	if (node == NULL && closestNode != NULL)
	{
		//stream.Percent(closestNode, percentage);
		max = 0;
		closestNode = NULL;
		throw exception(CLOSEST);
	}

	if (node->GetKey() == idFind)
	{
		return node;
	}

	if (node->GetKey() < idFind)
	{
		percentageP1 = (double)node->GetKey() / (double)idFind;
		percentage = percentageP1 * 100;

		if (percentage > max)
		{
			max = percentage;
			closestNode = node;
		}

		return FindClosestMatch(node->GetNextLeft(), idFind);
	}

	percentageP1 = (double)idFind / (double)node->GetKey();
	percentage = percentageP1 * 100;

	if (percentage > max)
	{
		max = percentage;
		closestNode = node;
	}

	return FindClosestMatch(node->GetNextRight(), idFind);
}

Node *BinaryTree::FindByName(Node *node, std::string findName)
{
	if (root != NULL && node != NULL)
	{
		if (node->GetVessel()->GetName() == findName)
		{
			//stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
			foundFlag = true;
		}
		FindByName(node->GetNextLeft(), findName);
		FindByName(node->GetNextRight(), findName);
	}
	else
		throw exception(ERRORMSG);
}

void BinaryTree::InOrderPrint(Node *node)
{
	if (root != NULL && node != NULL)
	{
		InOrderPrint(node->GetNextLeft());
		//stream.streamOut(node->GetKey(), node->GetVesselName(), node->GetVesselPtr());
		InOrderPrint(node->GetNextRight());
	}
	else
		throw exception(ERRORMSG);
}

void BinaryTree::PostOrderPrint(Node *node)
{
	if (root != NULL && node != NULL)
	{
		PostOrderPrint(node->GetNextRight());
		//stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
		PostOrderPrint(node->GetNextLeft());
	}
	else
		throw exception(ERRORMSG);
}

void BinaryTree::NoOrderPrint(Node *node)
{
	if (root != NULL && node != NULL)
	{
		//stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
		NoOrderPrint(node->GetNextLeft());
		NoOrderPrint(node->GetNextRight());
	}
	else
		throw exception(ERRORMSG);
}

void BinaryTree::PublicPrint(int printSelect)
{
	auto rootNode = FindRoot(root);

	if (printSelect == 1)
	{
		InOrderPrint(rootNode);
	}
	else if (printSelect == 2)
	{
		PostOrderPrint(rootNode);
	}		
	else if (printSelect == 3)
	{
		NoOrderPrint(rootNode);
	}
}

void BinaryTree::FindVesselID(int idFind)
{
	auto _p = Find(FindRoot(root), idFind);
	//stream.streamOut(_p->getKey(), _p->getVesselName(), _p->getVesselPtr());
}

void BinaryTree::FindVesselName(std::string findName)
{
	Node *_p = FindByName(FindRoot(root), findName);

	if ((_p == NULL) && (foundFlag == false)) // _p will be returned as NULL because of recursion
		throw exception(UNFOUND);
	if ((_p == NULL) && (foundFlag == true))
		foundFlag = false;
}

void BinaryTree::Hydrophone(int idFind)
{
	Node* _p = FindClosestMatch(FindRoot(root), idFind);
	//stream.streamOut(_p->getKey(), _p->getVesselName(), _p->getVesselPtr()); //to catch if the hydrophone hits the nail on the head
}

Node *BinaryTree::Sucessor(Node *node)
{
	Node *temp, *temp2;
	temp = temp2 = node->GetNextRight();

	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->GetNextLeft();
	}

	return temp2;
}

void BinaryTree::DeleteCurrent(int selectID)
{
	Node *node;
	Node *y;
	Node *SucessorTemp; //for both children

	//need to start with a search so
	node = Find(FindRoot(root), selectID);
	auto rootNode = FindRoot(node);

	if (node->GetKey() == selectID)
	{
		if ((node->GetNextLeft() == NULL) && (node->GetNextRight() == NULL)) //when node is a leaf only
		{
			y = node->GetParent();

			if (node->GetParent() == NULL)
			{
				rootNode = NULL;
				element--;
				delete node;
				throw exception(EMPTY); // might aswell jump out now :P
			}
			if (node == (node->GetParent()->GetNextRight()))
				y->SetNextRight(NULL);
			else
				y->SetNextLeft(NULL);
		}
		else if ((node->GetNextLeft() != NULL) && (node->GetNextRight() == NULL)) //when a node has left only
		{
			if (node->GetParent() == NULL)
			{

				node->GetNextLeft()->SetParent(node->GetNextLeft());
				y = node->GetNextLeft()->GetParent();
				y->SetNextLeft(y->GetNextLeft());
				y->SetParent(NULL);

				rootNode = y;
			}
			else if (node == (node->GetParent()->GetNextLeft()))
			{
				y = node->GetParent();

				node->GetNextLeft()->SetParent(y);
				y->SetNextLeft(node->GetNextLeft());
			}
			else
			{
				y = node->GetParent();

				node->GetNextLeft()->SetParent(y);
				y->SetNextRight(node->GetNextLeft());
			}

			//starting balancing
			if (node->GetColour() == false)
			{
				if (node->GetNextLeft()->GetColour() == true)
					node->GetNextLeft()->SetColour(false);
				else
					DeleteCase1(node->GetNextLeft());
			}
		}
		else if ((node->GetNextRight() != NULL) && (node->GetNextLeft() == NULL)) //when a node has right only
		{
			if (node->GetParent() == NULL)
			{

				node->GetNextRight()->SetParent(node->GetNextRight());
				y = node->GetNextRight()->GetParent();
				y->SetNextRight(y->GetNextRight());
				y->SetParent(NULL);

				rootNode = y;
			}
			else if (node == (node->GetParent()->GetNextLeft()))
			{
				y = node->GetParent();
				node->GetNextRight()->SetParent(y);
				y->SetNextLeft(node->GetNextRight());
			}
			else
			{
				y = node->GetParent();
				node->GetNextRight()->SetParent(y);
				y->SetNextRight(node->GetNextRight());
			}

			//starting balancing
			if (node->GetColour() == false)
			{
				if (node->GetNextRight()->GetColour() == true)
					node->GetNextRight()->SetColour(false);
				else
					DeleteCase1(node->GetNextRight());
			}
		}
		else if ((node->GetNextLeft() != NULL) && (node->GetNextRight() != NULL)) //when node has both left and right
		{																		  //internal node//
			if (node->GetParent() == NULL)										  // fixed
			{
				SucessorTemp = Sucessor(node);

				if (SucessorTemp != node->GetNextRight())
				{
					y = SucessorTemp->GetParent();

					if (SucessorTemp->GetNextRight() != NULL)
					{
						SucessorTemp->GetNextRight()->SetParent(y);
						y->SetNextLeft(SucessorTemp->GetNextRight());
					}
					else
						y->SetNextLeft(NULL);

					SucessorTemp->SetParent(NULL);
					node->GetNextLeft()->SetParent(SucessorTemp);
					node->GetNextRight()->SetParent(SucessorTemp);

					SucessorTemp->SetNextRight(node->GetNextRight());
					SucessorTemp->SetNextLeft(node->GetNextLeft());
				}
				else
				{
					y = SucessorTemp;

					SucessorTemp->SetParent(NULL);
					node->GetNextLeft()->SetParent(SucessorTemp);
					SucessorTemp->SetNextLeft(node->GetNextLeft());
				}

				rootNode = SucessorTemp;
			}
			if (node == (node->GetParent()->GetNextLeft())) //left side first
			{
				SucessorTemp = Sucessor(node);
				if (SucessorTemp != node->GetNextRight())
				{
					y = SucessorTemp->GetParent();

					if (SucessorTemp->GetNextRight() != NULL)
					{
						SucessorTemp->GetNextRight()->SetParent(y);
						y->SetNextLeft(SucessorTemp->GetNextRight());
					}
					else
						y->SetNextLeft(NULL);

					SucessorTemp->SetParent(node->GetParent());
					node->GetNextRight()->SetParent(SucessorTemp);
					node->GetNextLeft()->SetParent(SucessorTemp);

					SucessorTemp->SetNextRight(node->GetNextRight());
					SucessorTemp->SetNextLeft(node->GetNextLeft());

					node->GetParent()->SetNextLeft(SucessorTemp);
				}
				else
				{
					y = SucessorTemp;

					SucessorTemp->SetParent(node->GetParent());
					node->GetNextLeft()->SetParent(SucessorTemp);
					SucessorTemp->SetNextLeft(node->GetNextLeft());

					node->GetParent()->SetNextLeft(SucessorTemp);
				}
			}
			else if (node == (node->GetParent()->GetNextRight())) //now for the righthand side..
			{
				SucessorTemp = Sucessor(node);

				if (SucessorTemp != node->GetNextRight())
				{
					y = SucessorTemp->GetParent();

					if (SucessorTemp->GetNextRight() != NULL)
					{
						SucessorTemp->GetNextRight()->SetParent(y);
						y->SetNextLeft(SucessorTemp->GetNextRight());
					}
					else
						y->SetNextLeft(NULL);

					SucessorTemp->SetParent(node->GetParent());
					node->GetNextRight()->SetParent(SucessorTemp);
					node->GetNextLeft()->SetParent(SucessorTemp);
					SucessorTemp->SetNextRight(node->GetNextRight());
					SucessorTemp->SetNextLeft(node->GetNextLeft());

					node->GetParent()->SetNextRight(SucessorTemp);
				}
				else
				{
					y = SucessorTemp;

					SucessorTemp->SetParent(node->GetParent());
					node->GetNextLeft()->SetParent(SucessorTemp);
					SucessorTemp->SetNextLeft(node->GetNextLeft());
					node->GetParent()->SetNextRight(SucessorTemp);
				}
			}
			//cannot balance internal nodes
		}

		element--;

		delete node;
	}
}

void BinaryTree::DeletePublic(int selectID)
{
	DeleteCurrent(selectID);
}

//red black Implementations
Node *BinaryTree::GrandParent(Node *node)
{
	if ((node != NULL) && (node->GetParent() != NULL))
		return node->GetParent()->GetParent();
	else
		return node = NULL;
}

Node *BinaryTree::Uncle(Node *node)
{
	Node *gpNode = GrandParent(node);

	if (gpNode == NULL)
		return NULL; // no GrandParent therefore parent is root
	if (node->GetParent() == gpNode->GetNextLeft())
		return gpNode->GetNextRight();
	else
		return gpNode->GetNextLeft();
}

void BinaryTree::InsertCase1(Node *node)
{
	if (node->GetParent() == NULL)
		node->SetColour(false); //black
	else
		InsertCase2(node);
}

void BinaryTree::InsertCase2(Node *node)
{
	if (node->GetParent()->GetColour() == false)
		return; /* tree's all cool yo */
	else
		InsertCase3(node);
}

void BinaryTree::InsertCase3(Node *node)
{
	Node *uNode = Uncle(node);
	Node *gpNode;

	if ((uNode != NULL) && (uNode->GetColour() == true))
	{
		node->GetParent()->SetColour(false); //black
		uNode->SetColour(false);			 // black
		gpNode = GrandParent(node);
		gpNode->SetColour(true); //red
		InsertCase1(gpNode);
	}
	else
		InsertCase4(node);
}

void BinaryTree::InsertCase4(Node *node)
{
	Node *gpNode = GrandParent(node);

	if ((node == node->GetParent()->GetNextRight()) && (node->GetParent() == gpNode->GetNextLeft()))
	{
		RotateLeft(node->GetParent());
		node = node->GetNextLeft();
	}
	else if ((node == node->GetParent()->GetNextLeft()) && (node->GetParent() == gpNode->GetNextRight()))
	{
		RotateRight(node->GetParent());
		node = node->GetNextRight();
	}
	InsertCase5(node);
}

void BinaryTree::InsertCase5(Node *node)
{
	Node *gpNode = GrandParent(node);

	node->GetParent()->SetColour(false); //black
	gpNode->SetColour(true);			 // red

	if (node == node->GetParent()->GetNextLeft())
		RotateRight(gpNode);
	else
		RotateLeft(gpNode);
}

//rotation algorithms
void BinaryTree::RotateLeft(Node *node)
{
	Node *rotateRootNode;

	rotateRootNode = node->GetNextRight();
	node->SetNextRight(rotateRootNode->GetNextLeft());

	if (rotateRootNode->GetNextLeft() != NULL)
		rotateRootNode->GetNextLeft()->SetParent(node);

	if (node->GetParent() != NULL)
		rotateRootNode->SetParent(node->GetParent());
	else
		rotateRootNode->SetParent(NULL);

	if (node->GetParent() == NULL)
		node->SetParent(rotateRootNode); //check for root
	else if (node == node->GetParent()->GetNextLeft())
		node->GetParent()->SetNextLeft(rotateRootNode);
	else
		node->GetParent()->SetNextRight(rotateRootNode);

	rotateRootNode->SetNextLeft(node);
	node->SetParent(rotateRootNode);
}

void BinaryTree::RotateRight(Node *rotateRootNode)
{
	Node *node;

	node = rotateRootNode->GetNextLeft();
	rotateRootNode->SetNextLeft(node->GetNextRight());

	if (node->GetNextRight() != NULL)
		node->GetNextRight()->SetParent(rotateRootNode);

	if (rotateRootNode->GetParent() != NULL)
		node->SetParent(rotateRootNode->GetParent());
	else
		node->SetParent(NULL);

	if (rotateRootNode->GetParent() == NULL)
		rotateRootNode->SetParent(node); //check for root
	if (rotateRootNode == rotateRootNode->GetParent()->GetNextLeft())
		rotateRootNode->GetParent()->SetNextLeft(node);
	else
		rotateRootNode->GetParent()->SetNextRight(node);

	node->SetNextRight(rotateRootNode);
	rotateRootNode->SetParent(node);
}

Node *BinaryTree::Sibling(Node *node)
{
	if (node == node->GetParent()->GetNextLeft())
		return node->GetParent()->GetNextRight();
	else
		return node->GetParent()->GetNextLeft();
}

void BinaryTree::DeleteCase1(Node *node)
{
	if (node->GetParent() != NULL)
		DeleteCase2(node);
}

void BinaryTree::DeleteCase2(Node *node)
{
	Node *sibNode = Sibling(node);

	if (sibNode->GetColour() == true) //if red
	{
		node->GetParent()->SetColour(true); //is now red
		sibNode->SetColour(false);			//is not black

		if (node == node->GetParent()->GetNextLeft())
			RotateLeft(node->GetParent());
		else
			RotateRight(node->GetParent());
	}

	DeleteCase3(node);
}

void BinaryTree::DeleteCase3(Node *node)
{
	Node *sibNode = Sibling(node);

	if ((node->GetParent()->GetColour() == false) && (sibNode->GetColour() == false) && (sibNode->GetNextLeft()->GetColour() == false) && (sibNode->GetNextRight()->GetColour() == false))
	{
		sibNode->SetColour(true); // is now red
		DeleteCase1(node->GetParent());
	}
	else
		DeleteCase4(node);
}

void BinaryTree::DeleteCase4(Node *node)
{
	Node *sibNode = Sibling(node);

	if ((node->GetParent()->GetColour() == true) && (sibNode->GetColour() == false) && (sibNode->GetNextLeft()->GetColour() == false) && (sibNode->GetNextRight()->GetColour() == false))
	{
		sibNode->SetColour(true);
		node->GetParent()->SetColour(false);
	}
	else
		DeleteCase5(node);
}

void BinaryTree::DeleteCase5(Node *node)
{
	Node *sibNode = Sibling(node);

	if (sibNode->GetColour() == false)
	{
		if ((node == node->GetParent()->GetNextLeft()) && (sibNode->GetNextRight()->GetColour() == false) && (sibNode->GetNextLeft()->GetColour() == true))
		{
			sibNode->SetColour(true);
			sibNode->GetNextLeft()->SetColour(false);
			RotateRight(sibNode);
		}
		else if ((node == node->GetParent()->GetNextRight()) && (sibNode->GetNextLeft()->GetColour() == false) && (sibNode->GetNextRight()->GetColour() == true))
		{
			sibNode->SetColour(true);
			sibNode->GetNextRight()->SetColour(false);
			RotateLeft(sibNode);
		}
	}
	DeleteCase6(node);
}

void BinaryTree::DeleteCase6(Node *node)
{
	Node *sibNode = Sibling(node);

	sibNode->SetColour(node->GetParent()->GetColour());
	node->GetParent()->SetColour(false);

	if (node == node->GetParent()->GetNextLeft())
	{
		sibNode->GetNextRight()->SetColour(false);
		RotateLeft(node->GetParent());
	}
	else
	{
		sibNode->GetNextRight()->SetColour(false);
		RotateRight(node->GetParent());
	}
}

Node *BinaryTree::FindRoot(Node *node)
{
	while (true)
	{
		if (node->GetParent() != NULL)
			node = node->GetParent();
		else
			break;
	}

	return node;
}
