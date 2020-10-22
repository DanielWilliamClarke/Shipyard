#include <map>

#include "RedBlackTree.h"
#include "Node.h"
#include "Vessel.h"

#define ERRORMSG "No Elements"
#define UNFOUND "Not Found"
#define NAMEFIND "End Search"
#define DUPLICATE "Item already in table"
#define EMPTY "Table is now Empty"
#define CLOSEST "End Closest Match"

BinaryTree::BinaryTree()
	: root(nullptr), totalElements(0)
{
}

// Public

void BinaryTree::Insert(int key, Node* node)
{
	totalElements++;
	if (root != NULL)
	{
		InsertNode(FindRoot(root), node);
		return;
	}
	root = node;
}

void BinaryTree::Delete(int selectID)
{
	DeleteNode(selectID);
}

void BinaryTree::Traverse(BinaryTree::TRAVERSAL_ALGO algo, std::function<void(Node*)> callback)
{
	std::map<BinaryTree::TRAVERSAL_ALGO, std::function<void(Node*)>>{
		{ BinaryTree::TRAVERSAL_ALGO::INORDER, [&](Node* root) { this->InOrderTraversal(root, callback); } },
		{ BinaryTree::TRAVERSAL_ALGO::REVERSE, [&](Node* root) { this->PostOrderTraversal(root, callback); } },
		{ BinaryTree::TRAVERSAL_ALGO::TOPDOWN, [&](Node* root) { this->NoOrderTraversal(root, callback); } },
	} [algo] (FindRoot(root));
}

Node* BinaryTree::FindVessel(int idFind)
{
	return Find(FindRoot(root), idFind);
}

Node* BinaryTree::FindVessel(std::string findName)
{
	return FindByName(FindRoot(root), findName);
}

std::pair<Node*, float> BinaryTree::FindClosest(int key)
{
	return FindClosestMatch(FindRoot(root), std::make_pair(nullptr, 0.0f),  key);
}

int BinaryTree::Size()
{
	return totalElements;
}

// Private

void BinaryTree::InsertNode(Node* node, Node* newNode)
{
	if (newNode->GetKey() == node->GetKey())
	{
		throw std::exception(DUPLICATE);
	}		

	if (newNode->GetKey() < node->GetKey()) //compare key in tree
	{
		if (node->GetNextLeft() != NULL)
		{
			InsertNode(node->GetNextLeft(), newNode);
		}
		else
		{
			node->SetNextLeft(newNode);
			totalElements++;
		}
	}
	else
	{
		if (node->GetNextRight() != NULL)
		{
			InsertNode(node->GetNextRight(), newNode);
		}
		else
		{
			node->SetNextRight(newNode);
			totalElements++;
		}
	}

	newNode->SetParent(node);

	InsertCase1(node); // get the red black rolling on node Inserted to tree
}

Node *BinaryTree::Find(Node *node, int key)
{
	if (node == NULL)
	{
		throw std::exception(UNFOUND);
	}
	
	if (node->GetKey() == key)
	{
		return node;
	}

	if (key < node->GetKey())
	{
		return Find(node->GetNextLeft(), key);
	}
	return Find(node->GetNextRight(), key);
}

std::pair<Node*, float> BinaryTree::FindClosestMatch(Node *node, std::pair<Node*, float> closest, int key)
{
	if (node == NULL)
	{
		return closest;
	}

	if (node->GetKey() == key)
	{
		return std::make_pair(node, 1.0f);
	}

	if (key < node->GetKey())
	{
		auto percentage = (float)node->GetKey() / (float)key;
		if (percentage > closest.second)
		{
			closest.first = node;
			closest.second = percentage;
		}

		return FindClosestMatch(node->GetNextLeft(), closest, key);
	}

	auto percentage = (float)key / (float)node->GetKey();
	if (percentage > closest.second)
	{
		closest.first = node;
		closest.second = percentage;
	}

	return FindClosestMatch(node->GetNextRight(), closest, key);
}

Node *BinaryTree::FindByName(Node *node, std::string findName)
{
	if (node != NULL)
	{
		if (node->GetVessel()->GetName() == findName)
		{
			return node;
		}
		FindByName(node->GetNextLeft(), findName);
		FindByName(node->GetNextRight(), findName);
	}
	else
	{
		throw std::exception(ERRORMSG);
	}
	return nullptr;
}

void BinaryTree::InOrderTraversal(Node *node, std::function<void(Node*)> callback)
{
	if (node != NULL)
	{
		InOrderTraversal(node->GetNextLeft(), callback);
		callback(node);
		InOrderTraversal(node->GetNextRight(), callback);
	}
}

void BinaryTree::PostOrderTraversal(Node *node, std::function<void(Node*)> callback)
{
	if (node != NULL)
	{
		PostOrderTraversal(node->GetNextRight(), callback);
		callback(node);
		PostOrderTraversal(node->GetNextLeft(), callback);
	}
}

void BinaryTree::NoOrderTraversal(Node *node, std::function<void(Node*)> callback)
{
	if (node != NULL)
	{
		callback(node);
		NoOrderTraversal(node->GetNextLeft(), callback);
		NoOrderTraversal(node->GetNextRight(), callback);
	}
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

void BinaryTree::DeleteNode(int selectID)
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
				totalElements--;
				delete node;
				throw std::exception(EMPTY); // might aswell jump out now :P
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

		totalElements--;

		delete node;
	}
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

Node* BinaryTree::FindRoot(Node* node)
{
	if (node != nullptr && node->GetParent() != nullptr) {
		return FindRoot(node->GetParent());
	}
	return node;
}
