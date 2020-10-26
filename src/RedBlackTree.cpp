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

BinaryTree::BinaryTree(std::shared_ptr<ITreeAlgorithm> balancer)
	: balancer(balancer), root(nullptr), totalElements(0)
{
}

// Public
void BinaryTree::Insert(Node* node)
{
	totalElements++;
	root != nullptr ?
		InsertNode(FindRoot(root), node) :
		root = node;
}

void BinaryTree::Delete(unsigned int selectID)
{
	DeleteNode(selectID);
}

void BinaryTree::Traverse(BinaryTree::TRAVERSAL_ALGO algo, std::function<void(Node*)> callback) const
{
	std::map<BinaryTree::TRAVERSAL_ALGO, std::function<void(Node*)>>{
		{ BinaryTree::TRAVERSAL_ALGO::INORDER, [&](Node* root) { this->InOrderTraversal(root, callback); } },
		{ BinaryTree::TRAVERSAL_ALGO::REVERSE, [&](Node* root) { this->PostOrderTraversal(root, callback); } },
		{ BinaryTree::TRAVERSAL_ALGO::TOPDOWN, [&](Node* root) { this->NoOrderTraversal(root, callback); } },
	} [algo] (FindRoot(root));
}

Node* BinaryTree::FindVessel(unsigned int idFind) const
{
	return Find(FindRoot(root), idFind);
}

Node* BinaryTree::FindVessel(std::string findName) const
{
	return FindByName(FindRoot(root), findName);
}

std::pair<Node*, float> BinaryTree::FindClosest(int key) const
{
	return FindClosestMatch(FindRoot(root), std::make_pair(nullptr, 0.0f),  key);
}

int BinaryTree::Size() const
{
	return totalElements;
}

Node* BinaryTree::GetRoot() const
{
	return root;
}

// Private

void BinaryTree::InsertNode(Node* node, Node* newNode)
{
	if (newNode->GetVessel()->GetSignature() == node->GetVessel()->GetSignature())
	{
		throw std::exception(DUPLICATE);
	}		

	if (newNode->GetVessel()->GetSignature() < node->GetVessel()->GetSignature()) //compare key in tree
	{
		if (node->GetNextLeft() != nullptr)
		{
			InsertNode(node->GetNextLeft(), newNode);
		}
		else
		{
			node->SetNextLeft(newNode);
		}
	}
	else
	{
		if (node->GetNextRight() != nullptr)
		{
			InsertNode(node->GetNextRight(), newNode);
		}
		else
		{
			node->SetNextRight(newNode);
		}
	}

	newNode->SetParent(node);

	this->balancer->BalanceOnInsert(node); // get the red black rolling on node Inserted to tree
}

Node* BinaryTree::FindRoot(Node* node) const
{
	if (node != nullptr && node->GetParent() != nullptr) {
		return FindRoot(node->GetParent());
	}
	return node;
}

Node *BinaryTree::Find(Node *node, unsigned int key) const
{
	if (node == nullptr)
	{
		throw std::exception(UNFOUND);
	}
	
	if (node->GetVessel()->GetSignature() == key)
	{
		return node;
	}

	if (key < node->GetVessel()->GetSignature())
	{
		return Find(node->GetNextLeft(), key);
	}
	return Find(node->GetNextRight(), key);
}

std::pair<Node*, float> BinaryTree::FindClosestMatch(Node *node, std::pair<Node*, float> closest, unsigned int key) const
{
	if (node == nullptr)
	{
		return closest;
	}

	if (node->GetVessel()->GetSignature() == key)
	{
		return std::make_pair(node, 1.0f);
	}

	if (key < node->GetVessel()->GetSignature())
	{
		auto percentage = (float)node->GetVessel()->GetSignature() / (float)key;
		if (percentage > closest.second)
		{
			closest.first = node;
			closest.second = percentage;
		}

		return FindClosestMatch(node->GetNextLeft(), closest, key);
	}

	auto percentage = (float)key / (float)node->GetVessel()->GetSignature();
	if (percentage > closest.second)
	{
		closest.first = node;
		closest.second = percentage;
	}

	return FindClosestMatch(node->GetNextRight(), closest, key);
}

Node *BinaryTree::FindByName(Node *node, std::string findName) const
{
	if (node != nullptr)
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

void BinaryTree::InOrderTraversal(Node *node, std::function<void(Node*)> callback) const
{
	if (node != nullptr)
	{
		InOrderTraversal(node->GetNextLeft(), callback);
		callback(node);
		InOrderTraversal(node->GetNextRight(), callback);
	}
}

void BinaryTree::PostOrderTraversal(Node *node, std::function<void(Node*)> callback) const
{
	if (node != nullptr)
	{
		PostOrderTraversal(node->GetNextRight(), callback);
		callback(node);
		PostOrderTraversal(node->GetNextLeft(), callback);
	}
}

void BinaryTree::NoOrderTraversal(Node *node, std::function<void(Node*)> callback) const
{
	if (node != nullptr)
	{
		callback(node);
		NoOrderTraversal(node->GetNextLeft(), callback);
		NoOrderTraversal(node->GetNextRight(), callback);
	}
}

void BinaryTree::DeleteNode(int key)
{
	//need to start with a search so
	auto node = Find(FindRoot(root), key);

	if (node->GetVessel()->GetSignature() == key)
	{
		// when node is a leaf only
		if ((node->GetNextLeft() == nullptr) && (node->GetNextRight() == nullptr))
		{
			if (node == root)
			{
				delete node;
				node = nullptr;
				totalElements = 0;
				throw std::exception(EMPTY); // might aswell jump out now :P
			}

			node == node->GetParent()->GetNextRight() ?
				node->GetParent()->SetNextRight(nullptr) :
				node->GetParent()->SetNextLeft(nullptr);
		}
		// when a node has left child only
		else if (node->GetNextLeft() != nullptr && node->GetNextRight() == nullptr) 
		{
			if (node == root)
			{
				root = node->GetNextLeft();
				root->SetParent(nullptr);				
			}
			else if (node == node->GetParent()->GetNextLeft())
			{
				node->GetNextLeft()->SetParent(node->GetParent());
				node->GetParent()->SetNextLeft(node->GetNextLeft());
			}
			else
			{
				node->GetNextLeft()->SetParent(node->GetParent());
				node->GetParent()->SetNextRight(node->GetNextLeft());
			}

			//starting balancing
			if (node->GetColour() == false)
			{
				node->GetNextLeft()->GetColour() ?
					node->GetNextLeft()->SetColour(false) :
					this->balancer->BalanceOnDelete(node->GetNextLeft());
			}
		}
		// when a node has right child only
		else if ((node->GetNextRight() != nullptr) && (node->GetNextLeft() == nullptr)) //when a node has right only
		{
			if (node == root)
			{
				root = node->GetNextRight();
				root->SetParent(nullptr);
			}
			else if (node == node->GetParent()->GetNextLeft())
			{
				node->GetNextRight()->SetParent(node->GetParent());
				node->GetParent()->SetNextLeft(node->GetNextRight());
			}
			else
			{
				node->GetNextRight()->SetParent(node->GetParent());
				node->GetParent()->SetNextRight(node->GetNextRight());
			}

			//starting balancing
			if (node->GetColour() == false)
			{
				node->GetNextRight()->GetColour() ?
					node->GetNextRight()->SetColour(false) :
					this->balancer->BalanceOnDelete(node->GetNextRight());
			}
		}
		// when node has both left and right children
		else if ((node->GetNextLeft() != nullptr) && (node->GetNextRight() != nullptr))
		{																		 
			if (node == root)
			{
				auto successor = Sucessor(node);
				root = successor;

				// Successor is not immediately right of this node
				if (successor != node->GetNextRight())
				{
					if (successor->GetNextRight() != nullptr)
					{
						successor->GetNextRight()->SetParent(successor->GetParent());
						successor->GetParent()->SetNextLeft(successor->GetNextRight());
					}
					else
					{
						successor->GetParent()->SetNextLeft(nullptr);
					}						

					successor->SetParent(nullptr);
					node->GetNextLeft()->SetParent(successor);
					node->GetNextRight()->SetParent(successor);

					successor->SetNextRight(node->GetNextRight());
					successor->SetNextLeft(node->GetNextLeft());
				}
				else
				{
					successor->SetParent(nullptr);
					node->GetNextLeft()->SetParent(successor);
					successor->SetNextLeft(node->GetNextLeft());
				}
			}

			//left side first
			if (node == node->GetParent()->GetNextLeft()) 
			{
				auto successor = Sucessor(node);
				if (successor != node->GetNextRight())
				{
					if (successor->GetNextRight() != nullptr)
					{
						successor->GetNextRight()->SetParent(successor->GetParent());
						successor->GetParent()->SetNextLeft(successor->GetNextRight());
					}
					else
					{
						successor->GetParent()->SetNextLeft(nullptr);
					}
						
					successor->SetParent(node->GetParent());
					node->GetNextRight()->SetParent(successor);
					node->GetNextLeft()->SetParent(successor);

					successor->SetNextRight(node->GetNextRight());
					successor->SetNextLeft(node->GetNextLeft());

					node->GetParent()->SetNextLeft(successor);
				}
				else
				{
					successor->SetParent(node->GetParent());
					node->GetNextLeft()->SetParent(successor);
					successor->SetNextLeft(node->GetNextLeft());
					node->GetParent()->SetNextLeft(successor);
				}
			}
			else if (node == node->GetParent()->GetNextRight()) //now for the righthand side..
			{
				auto successor = Sucessor(node);

				if (successor != node->GetNextRight())
				{
					if (successor->GetNextRight() != nullptr)
					{
						successor->GetNextRight()->SetParent(successor->GetParent());
						successor->GetParent()->SetNextLeft(successor->GetNextRight());
					}
					else
					{
						successor->GetParent()->SetNextLeft(nullptr);
					}

					successor->SetParent(node->GetParent());
					node->GetNextRight()->SetParent(successor);
					node->GetNextLeft()->SetParent(successor);
					successor->SetNextRight(node->GetNextRight());
					successor->SetNextLeft(node->GetNextLeft());

					node->GetParent()->SetNextRight(successor);
				}
				else
				{
					successor->SetParent(node->GetParent());
					node->GetNextLeft()->SetParent(successor);
					successor->SetNextLeft(node->GetNextLeft());
					node->GetParent()->SetNextRight(successor);
				}
			}
		}

		totalElements--;

		delete node;
	}
}

Node* BinaryTree::Sucessor(Node* node) const
{
	Node* temp, * temp2;
	temp = temp2 = node->GetNextRight();

	while (temp != nullptr)
	{
		temp2 = temp;
		temp = temp->GetNextLeft();
	}

	return temp2;
}

