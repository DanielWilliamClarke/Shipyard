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

#include <typeinfo>
#include <string>

using namespace std;

library stream;

binaryTree::binaryTree()
{
	_root = NULL;
	_foundFlag = false;
}
void binaryTree::insert(int keyGen, std::string vesselName, BaseVessel *vesselPtr)
{
	if (_root != NULL)
		insertNode(findRoot(_root), keyGen, vesselName, vesselPtr);
	else
	{
		_root = new Node;
		_root->setKey(keyGen);			  //set node key
		_root->setVesselName(vesselName); //for searching by name
		_root->setVesselPtr(vesselPtr);	  //set node data
		_root->setNextLeft(NULL);
		_root->setNextRight(NULL);
		_root->setParent(NULL);
		_element++;
	}
}
void binaryTree::insertNode(Node *node, int keyGen, std::string vesselName, BaseVessel *vesselPtr)
{
	// to set parent so node can look back to its parent node
	Node *parent;

	parent = node;

	if ((keyGen == node->getKey()) || (vesselName == node->getVesselName()))
		throw exception(DUPLICATE);

	if (node->getKey() > keyGen) //compare key in tree
	{
		if (node->getNextLeft() != NULL)
			insertNode(node->getNextLeft(), keyGen, vesselName, vesselPtr);
		else
		{
			node->setNextLeft(new Node);
			node->getNextLeft()->setKey(keyGen);			//set node key
			node->getNextLeft()->setVesselName(vesselName); //for searching by name
			node->getNextLeft()->setVesselPtr(vesselPtr);	//set node data
			node->getNextLeft()->setNextLeft(NULL);
			node->getNextLeft()->setNextRight(NULL);
			node->getNextLeft()->setParent(parent);
			_element++;
		}
	}
	else if (keyGen > node->getKey())
	{
		if (node->getNextRight() != NULL)
			insertNode(node->getNextRight(), keyGen, vesselName, vesselPtr);
		else
		{
			node->setNextRight(new Node);
			node->getNextRight()->setKey(keyGen);			 //set node key
			node->getNextRight()->setVesselName(vesselName); //for searching by name
			node->getNextRight()->setVesselPtr(vesselPtr);	 //set node data
			node->getNextRight()->setNextLeft(NULL);
			node->getNextRight()->setNextRight(NULL);
			node->getNextRight()->setParent(parent);
			_element++;
		}
	}

	insertCase1(node); // get the red black rolling on node inserted to tree
}
void binaryTree::editNode(int key)
{
	Node *_vessel = find(findRoot(_root), key);
	_vessel->setVesselPtr(stream.fillVesselPtr());
}
void binaryTree::editNodeName(int key)
{
	Node *_vessel = find(findRoot(_root), key);
	_vessel->setVesselName(stream.setName());
}
int binaryTree::size()
{
	if (_element != 0)
		return _element;
	else
		throw exception(ERRORMSG);
}
Node *binaryTree::find(Node *node, int idFind)
{
	if (node == NULL)
		throw exception(UNFOUND);

	if (node->getKey() == idFind)
		return node;
	else
	{
		if (node->getKey() < idFind)
			return find(node->getNextRight(), idFind);
		else
			return find(node->getNextLeft(), idFind);
	}
}
Node *binaryTree::findClosestMatch(Node *node, int idFind)
{
	if (node == NULL)
	{
		if (_closestNode != NULL)
		{
			stream.Percent(_closestNode, _percentage);
			_max = 0;
			_closestNode = NULL;
		}
		throw exception(CLOSEST);
	}

	if (node->getKey() == idFind)
		return node;
	else
	{
		if (node->getKey() < idFind)
		{
			_percentageP1 = (double)node->getKey() / (double)idFind;
			_percentage = _percentageP1 * 100;

			if (_percentage > _max)
			{
				_max = _percentage;
				_closestNode = node;
			}

			return findClosestMatch(node->getNextLeft(), idFind);
		}
		else
		{
			_percentageP1 = (double)idFind / (double)node->getKey();
			_percentage = _percentageP1 * 100;

			if (_percentage > _max)
			{
				_max = _percentage;
				_closestNode = node;
			}

			return findClosestMatch(node->getNextRight(), idFind);
		}
	}
}
Node *binaryTree::findByName(Node *node, std::string findName)
{
	if (_root != NULL)
	{
		if (node != NULL)
		{
			if (node->getVesselName() == findName)
			{
				stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
				_foundFlag = true;
			}
			findByName(node->getNextLeft(), findName);
			findByName(node->getNextRight(), findName);
		}
	}
	else
		throw exception(ERRORMSG);
	//sort of an augmented noOrder traversal method
}
void binaryTree::inOrderPrint(Node *node)
{
	if (_root != NULL)
	{
		if (node != NULL)
		{
			inOrderPrint(node->getNextLeft());
			stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
			inOrderPrint(node->getNextRight());
		}
	}
	else
		throw exception(ERRORMSG);
}
void binaryTree::postOrderPrint(Node *node)
{
	if (_root != NULL)
	{
		if (node != NULL)
		{
			postOrderPrint(node->getNextRight());
			stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
			postOrderPrint(node->getNextLeft());
		}
	}
	else
		throw exception(ERRORMSG);
}
void binaryTree::noOrderPrint(Node *node)
{
	if (_root != NULL)
	{
		if (node != NULL)
		{
			stream.streamOut(node->getKey(), node->getVesselName(), node->getVesselPtr());
			noOrderPrint(node->getNextLeft());
			noOrderPrint(node->getNextRight());
		}
	}
	else
		throw exception(ERRORMSG);
}
void binaryTree::publicPrint(int printSelect)
{
	Node *rootNode = findRoot(_root);

	if (printSelect == 1)
		inOrderPrint(rootNode);
	else if (printSelect == 2)
		postOrderPrint(rootNode);
	else if (printSelect == 3)
		noOrderPrint(rootNode);
}
void binaryTree::FindVesselID(int idFind)
{
	Node *_p = find(findRoot(_root), idFind);
	stream.streamOut(_p->getKey(), _p->getVesselName(), _p->getVesselPtr());
}
void binaryTree::findVesselName(std::string findName)
{
	Node *_p = findByName(findRoot(_root), findName);

	if ((_p == NULL) && (_foundFlag == false)) // _p will be returned as NULL because of recursion
		throw exception(UNFOUND);
	if ((_p == NULL) && (_foundFlag == true))
		_foundFlag = false;
}
void binaryTree::hydrophone(int idFind)
{
	Node *_p = findClosestMatch(findRoot(_root), idFind);
	stream.streamOut(_p->getKey(), _p->getVesselName(), _p->getVesselPtr()); //to catch if the hydrophone hits the nail on the head
}
Node *binaryTree::sucessor(Node *node)
{
	Node *temp, *temp2;

	temp = temp2 = node->getNextRight();

	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->getNextLeft();
	}

	return temp2;
}
void binaryTree::deleteCurrent(int selectID)
{
	Node *node;
	Node *y;
	Node *sucessorTemp; //for both children

	//need to start with a search so
	node = find(findRoot(_root), selectID);
	Node *rootNode = findRoot(node);

	if (node->getKey() == selectID)
	{
		if ((node->getNextLeft() == NULL) && (node->getNextRight() == NULL)) //when node is a leaf only
		{
			y = node->getParent();

			if (node->getParent() == NULL)
			{
				rootNode = NULL;
				_element--;
				delete node;
				throw exception(EMPTY); // might aswell jump out now :P
			}
			if (node == (node->getParent()->getNextRight()))
				y->setNextRight(NULL);
			else
				y->setNextLeft(NULL);
		}
		else if ((node->getNextLeft() != NULL) && (node->getNextRight() == NULL)) //when a node has left only
		{
			if (node->getParent() == NULL)
			{

				node->getNextLeft()->setParent(node->getNextLeft());
				y = node->getNextLeft()->getParent();
				y->setNextLeft(y->getNextLeft());
				y->setParent(NULL);

				rootNode = y;
			}
			else if (node == (node->getParent()->getNextLeft()))
			{
				y = node->getParent();

				node->getNextLeft()->setParent(y);
				y->setNextLeft(node->getNextLeft());
			}
			else
			{
				y = node->getParent();

				node->getNextLeft()->setParent(y);
				y->setNextRight(node->getNextLeft());
			}

			//starting balancing
			if (node->getColour() == false)
			{
				if (node->getNextLeft()->getColour() == true)
					node->getNextLeft()->setColour(false);
				else
					deleteCase1(node->getNextLeft());
			}
		}
		else if ((node->getNextRight() != NULL) && (node->getNextLeft() == NULL)) //when a node has right only
		{
			if (node->getParent() == NULL)
			{

				node->getNextRight()->setParent(node->getNextRight());
				y = node->getNextRight()->getParent();
				y->setNextRight(y->getNextRight());
				y->setParent(NULL);

				rootNode = y;
			}
			else if (node == (node->getParent()->getNextLeft()))
			{
				y = node->getParent();
				node->getNextRight()->setParent(y);
				y->setNextLeft(node->getNextRight());
			}
			else
			{
				y = node->getParent();
				node->getNextRight()->setParent(y);
				y->setNextRight(node->getNextRight());
			}

			//starting balancing
			if (node->getColour() == false)
			{
				if (node->getNextRight()->getColour() == true)
					node->getNextRight()->setColour(false);
				else
					deleteCase1(node->getNextRight());
			}
		}
		else if ((node->getNextLeft() != NULL) && (node->getNextRight() != NULL)) //when node has both left and right
		{																		  //internal node//
			if (node->getParent() == NULL)										  // fixed
			{
				sucessorTemp = sucessor(node);

				if (sucessorTemp != node->getNextRight())
				{
					y = sucessorTemp->getParent();

					if (sucessorTemp->getNextRight() != NULL)
					{
						sucessorTemp->getNextRight()->setParent(y);
						y->setNextLeft(sucessorTemp->getNextRight());
					}
					else
						y->setNextLeft(NULL);

					sucessorTemp->setParent(NULL);
					node->getNextLeft()->setParent(sucessorTemp);
					node->getNextRight()->setParent(sucessorTemp);

					sucessorTemp->setNextRight(node->getNextRight());
					sucessorTemp->setNextLeft(node->getNextLeft());
				}
				else
				{
					y = sucessorTemp;

					sucessorTemp->setParent(NULL);
					node->getNextLeft()->setParent(sucessorTemp);
					sucessorTemp->setNextLeft(node->getNextLeft());
				}

				rootNode = sucessorTemp;
			}
			if (node == (node->getParent()->getNextLeft())) //left side first
			{
				sucessorTemp = sucessor(node);
				if (sucessorTemp != node->getNextRight())
				{
					y = sucessorTemp->getParent();

					if (sucessorTemp->getNextRight() != NULL)
					{
						sucessorTemp->getNextRight()->setParent(y);
						y->setNextLeft(sucessorTemp->getNextRight());
					}
					else
						y->setNextLeft(NULL);

					sucessorTemp->setParent(node->getParent());
					node->getNextRight()->setParent(sucessorTemp);
					node->getNextLeft()->setParent(sucessorTemp);

					sucessorTemp->setNextRight(node->getNextRight());
					sucessorTemp->setNextLeft(node->getNextLeft());

					node->getParent()->setNextLeft(sucessorTemp);
				}
				else
				{
					y = sucessorTemp;

					sucessorTemp->setParent(node->getParent());
					node->getNextLeft()->setParent(sucessorTemp);
					sucessorTemp->setNextLeft(node->getNextLeft());

					node->getParent()->setNextLeft(sucessorTemp);
				}
			}
			else if (node == (node->getParent()->getNextRight())) //now for the righthand side..
			{
				sucessorTemp = sucessor(node);

				if (sucessorTemp != node->getNextRight())
				{
					y = sucessorTemp->getParent();

					if (sucessorTemp->getNextRight() != NULL)
					{
						sucessorTemp->getNextRight()->setParent(y);
						y->setNextLeft(sucessorTemp->getNextRight());
					}
					else
						y->setNextLeft(NULL);

					sucessorTemp->setParent(node->getParent());
					node->getNextRight()->setParent(sucessorTemp);
					node->getNextLeft()->setParent(sucessorTemp);
					sucessorTemp->setNextRight(node->getNextRight());
					sucessorTemp->setNextLeft(node->getNextLeft());

					node->getParent()->setNextRight(sucessorTemp);
				}
				else
				{
					y = sucessorTemp;

					sucessorTemp->setParent(node->getParent());
					node->getNextLeft()->setParent(sucessorTemp);
					sucessorTemp->setNextLeft(node->getNextLeft());
					node->getParent()->setNextRight(sucessorTemp);
				}
			}
			//cannot balance internal nodes
		}

		_element--;

		delete node;
	}
}
void binaryTree::deletePublic(int selectID)
{
	deleteCurrent(selectID);
}
//red black Implementations
Node *binaryTree::grandParent(Node *node)
{
	if ((node != NULL) && (node->getParent() != NULL))
		return node->getParent()->getParent();
	else
		return node = NULL;
}
Node *binaryTree::uncleNode(Node *node)
{
	Node *gpNode = grandParent(node);

	if (gpNode == NULL)
		return NULL; // no grandParent therefore parent is root
	if (node->getParent() == gpNode->getNextLeft())
		return gpNode->getNextRight();
	else
		return gpNode->getNextLeft();
}
void binaryTree::insertCase1(Node *node)
{
	if (node->getParent() == NULL)
		node->setColour(false); //black
	else
		insertCase2(node);
}
void binaryTree::insertCase2(Node *node)
{
	if (node->getParent()->getColour() == false)
		return; /* tree's all cool yo */
	else
		insertCase3(node);
}
void binaryTree::insertCase3(Node *node)
{
	Node *uNode = uncleNode(node);
	Node *gpNode;

	if ((uNode != NULL) && (uNode->getColour() == true))
	{
		node->getParent()->setColour(false); //black
		uNode->setColour(false);			 // black
		gpNode = grandParent(node);
		gpNode->setColour(true); //red
		insertCase1(gpNode);
	}
	else
		insertCase4(node);
}
void binaryTree::insertCase4(Node *node)
{
	Node *gpNode = grandParent(node);

	if ((node == node->getParent()->getNextRight()) && (node->getParent() == gpNode->getNextLeft()))
	{
		rotateLeft(node->getParent());
		node = node->getNextLeft();
	}
	else if ((node == node->getParent()->getNextLeft()) && (node->getParent() == gpNode->getNextRight()))
	{
		rotateRight(node->getParent());
		node = node->getNextRight();
	}
	insertCase5(node);
}
void binaryTree::insertCase5(Node *node)
{
	Node *gpNode = grandParent(node);

	node->getParent()->setColour(false); //black
	gpNode->setColour(true);			 // red

	if (node == node->getParent()->getNextLeft())
		rotateRight(gpNode);
	else
		rotateLeft(gpNode);
}
//rotation algorithms
void binaryTree::rotateLeft(Node *node)
{
	Node *rotateRootNode;

	rotateRootNode = node->getNextRight();
	node->setNextRight(rotateRootNode->getNextLeft());

	if (rotateRootNode->getNextLeft() != NULL)
		rotateRootNode->getNextLeft()->setParent(node);

	if (node->getParent() != NULL)
		rotateRootNode->setParent(node->getParent());
	else
		rotateRootNode->setParent(NULL);

	if (node->getParent() == NULL)
		node->setParent(rotateRootNode); //check for root
	else if (node == node->getParent()->getNextLeft())
		node->getParent()->setNextLeft(rotateRootNode);
	else
		node->getParent()->setNextRight(rotateRootNode);

	rotateRootNode->setNextLeft(node);
	node->setParent(rotateRootNode);
}
void binaryTree::rotateRight(Node *rotateRootNode)
{
	Node *node;

	node = rotateRootNode->getNextLeft();
	rotateRootNode->setNextLeft(node->getNextRight());

	if (node->getNextRight() != NULL)
		node->getNextRight()->setParent(rotateRootNode);

	if (rotateRootNode->getParent() != NULL)
		node->setParent(rotateRootNode->getParent());
	else
		node->setParent(NULL);

	if (rotateRootNode->getParent() == NULL)
		rotateRootNode->setParent(node); //check for root
	if (rotateRootNode == rotateRootNode->getParent()->getNextLeft())
		rotateRootNode->getParent()->setNextLeft(node);
	else
		rotateRootNode->getParent()->setNextRight(node);

	node->setNextRight(rotateRootNode);
	rotateRootNode->setParent(node);
}
Node *binaryTree::siblingNode(Node *node)
{
	if (node == node->getParent()->getNextLeft())
		return node->getParent()->getNextRight();
	else
		return node->getParent()->getNextLeft();
}
void binaryTree::deleteCase1(Node *node)
{
	if (node->getParent() != NULL)
		deleteCase2(node);
}
void binaryTree::deleteCase2(Node *node)
{
	Node *sibNode = siblingNode(node);

	if (sibNode->getColour() == true) //if red
	{
		node->getParent()->setColour(true); //is now red
		sibNode->setColour(false);			//is not black

		if (node == node->getParent()->getNextLeft())
			rotateLeft(node->getParent());
		else
			rotateRight(node->getParent());
	}

	deleteCase3(node);
}
void binaryTree::deleteCase3(Node *node)
{
	Node *sibNode = siblingNode(node);

	if ((node->getParent()->getColour() == false) && (sibNode->getColour() == false) && (sibNode->getNextLeft()->getColour() == false) && (sibNode->getNextRight()->getColour() == false))
	{
		sibNode->setColour(true); // is now red
		deleteCase1(node->getParent());
	}
	else
		deleteCase4(node);
}
void binaryTree::deleteCase4(Node *node)
{
	Node *sibNode = siblingNode(node);

	if ((node->getParent()->getColour() == true) && (sibNode->getColour() == false) && (sibNode->getNextLeft()->getColour() == false) && (sibNode->getNextRight()->getColour() == false))
	{
		sibNode->setColour(true);
		node->getParent()->setColour(false);
	}
	else
		deleteCase5(node);
}
void binaryTree::deleteCase5(Node *node)
{
	Node *sibNode = siblingNode(node);

	if (sibNode->getColour() == false)
	{
		if ((node == node->getParent()->getNextLeft()) && (sibNode->getNextRight()->getColour() == false) && (sibNode->getNextLeft()->getColour() == true))
		{
			sibNode->setColour(true);
			sibNode->getNextLeft()->setColour(false);
			rotateRight(sibNode);
		}
		else if ((node == node->getParent()->getNextRight()) && (sibNode->getNextLeft()->getColour() == false) && (sibNode->getNextRight()->getColour() == true))
		{
			sibNode->setColour(true);
			sibNode->getNextRight()->setColour(false);
			rotateLeft(sibNode);
		}
	}
	deleteCase6(node);
}
void binaryTree::deleteCase6(Node *node)
{
	Node *sibNode = siblingNode(node);

	sibNode->setColour(node->getParent()->getColour());
	node->getParent()->setColour(false);

	if (node == node->getParent()->getNextLeft())
	{
		sibNode->getNextRight()->setColour(false);
		rotateLeft(node->getParent());
	}
	else
	{
		sibNode->getNextRight()->setColour(false);
		rotateRight(node->getParent());
	}
}
Node *binaryTree::findRoot(Node *node)
{
	while (true)
	{
		if (node->getParent() != NULL)
			node = node->getParent();
		else
			break;
	}

	return node;
}
