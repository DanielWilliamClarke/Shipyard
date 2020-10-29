#include "RedBlackTreeAlgorithm.h"
#include "Node.h"

void RedBlackTreeAlgorithm::BalanceOnInsert(Node* node)
{
	if (node->GetParent() == nullptr)
	{
		node->SetColour(false); //black
		return;
	}
	InsertCase2(node);
}

void RedBlackTreeAlgorithm::InsertCase2(Node* node)
{
	if (node->GetParent()->GetColour())
	{
		InsertCase3(node);
	}
}

void RedBlackTreeAlgorithm::InsertCase3(Node* node)
{
	auto uncleNode = Uncle(node);
	if (uncleNode != nullptr && uncleNode->GetColour() == true)
	{
		node->GetParent()->SetColour(false); //black
		uncleNode->SetColour(false);			 // black

		auto grandparentNode = GrandParent(node);
		grandparentNode->SetColour(true); //red
		BalanceOnInsert(grandparentNode);
		return;
	}
	InsertCase4(node);
}

void RedBlackTreeAlgorithm::InsertCase4(Node* node)
{
	auto grandparentNode = GrandParent(node);

	if (node == node->GetParent()->GetNextRight() && node->GetParent() == grandparentNode->GetNextLeft())
	{
		RotateLeft(node->GetParent());
		node = node->GetNextLeft();
	}
	else if (node == node->GetParent()->GetNextLeft() && node->GetParent() == grandparentNode->GetNextRight())
	{
		RotateRight(node->GetParent());
		node = node->GetNextRight();
	}
	InsertCase5(node);
}

void RedBlackTreeAlgorithm::InsertCase5(Node* node)
{
	auto grandparentNode = GrandParent(node);
	node->GetParent()->SetColour(false);
	grandparentNode->SetColour(true);	
	node == node->GetParent()->GetNextLeft() ?
		RotateRight(grandparentNode) :
		RotateLeft(grandparentNode);
}

void RedBlackTreeAlgorithm::BalanceOnDelete(Node* node)
{
	if (node->GetParent() != nullptr)
	{
		DeleteCase2(node);
	}
}

void RedBlackTreeAlgorithm::DeleteCase2(Node* node)
{
	auto siblingNode = Sibling(node);

	if (siblingNode->GetColour()) //if red
	{
		node->GetParent()->SetColour(true); //is now red
		siblingNode->SetColour(false);			//is not black

		node == node->GetParent()->GetNextLeft() ?
			RotateLeft(node->GetParent()) :
			RotateRight(node->GetParent());
	}

	DeleteCase3(node);
}

void RedBlackTreeAlgorithm::DeleteCase3(Node* node)
{
	auto siblingNode = Sibling(node);

	if (!node->GetParent()->GetColour() && !siblingNode->GetColour() &&
		!siblingNode->GetNextLeft()->GetColour() && !siblingNode->GetNextRight()->GetColour())
	{
		siblingNode->SetColour(true); // is now red
		BalanceOnDelete(node->GetParent());
		return;
	}

	DeleteCase4(node);
}

void RedBlackTreeAlgorithm::DeleteCase4(Node* node)
{
	auto siblingNode = Sibling(node);

	if (node->GetParent()->GetColour() && !siblingNode->GetColour() &&
		!siblingNode->GetNextLeft()->GetColour() && !siblingNode->GetNextRight()->GetColour())
	{
		siblingNode->SetColour(true);
		node->GetParent()->SetColour(false);
		return;
	}
	
	DeleteCase5(node);
}

void RedBlackTreeAlgorithm::DeleteCase5(Node* node)
{
	auto siblingNode = Sibling(node);

	if (!siblingNode->GetColour())
	{
		if (node == node->GetParent()->GetNextLeft() && 
			!siblingNode->GetNextRight()->GetColour() == false &&
			siblingNode->GetNextLeft()->GetColour())
		{
			siblingNode->SetColour(true);
			siblingNode->GetNextLeft()->SetColour(false);
			RotateRight(siblingNode);
		}
		else if (node == node->GetParent()->GetNextRight() &&
			siblingNode->GetNextRight()->GetColour() &&
			!siblingNode->GetNextLeft()->GetColour())
		{
			siblingNode->SetColour(true);
			siblingNode->GetNextRight()->SetColour(false);
			RotateLeft(siblingNode);
		}
	}

	DeleteCase6(node);
}

void RedBlackTreeAlgorithm::DeleteCase6(Node* node)
{
	auto siblingNode = Sibling(node);

	siblingNode->SetColour(node->GetParent()->GetColour());
	node->GetParent()->SetColour(false);

	if (node == node->GetParent()->GetNextLeft())
	{
		siblingNode->GetNextRight()->SetColour(false);
		RotateLeft(node->GetParent());
	}
	else
	{
		siblingNode->GetNextRight()->SetColour(false);
		RotateRight(node->GetParent());
	}
}

//rotation algorithms
void RedBlackTreeAlgorithm::RotateLeft(Node* node)
{
	auto rotateRootNode = node->GetNextRight();
	node->SetNextRight(rotateRootNode->GetNextLeft());

	if (rotateRootNode->GetNextLeft() != nullptr)
	{
		rotateRootNode->GetNextLeft()->SetParent(node);
	}		

	if (node->GetParent() != nullptr)
	{
		rotateRootNode->SetParent(node->GetParent());
	}
	else
	{
		rotateRootNode->SetParent(nullptr);
	}
		
	if (node->GetParent() == nullptr)
	{
		node->SetParent(rotateRootNode); //check for root
	}
	else if (node == node->GetParent()->GetNextLeft())
	{
		node->GetParent()->SetNextLeft(rotateRootNode);
	}
	else
	{
		node->GetParent()->SetNextRight(rotateRootNode);
	}
	
	rotateRootNode->SetNextLeft(node);
	node->SetParent(rotateRootNode);
}

void RedBlackTreeAlgorithm::RotateRight(Node* rotateRootNode)
{
	auto node = rotateRootNode->GetNextLeft();
	rotateRootNode->SetNextLeft(node->GetNextRight());

	if (node->GetNextRight() != nullptr)
	{
		node->GetNextRight()->SetParent(rotateRootNode);
	}

	if (rotateRootNode->GetParent() != nullptr)
	{
		node->SetParent(rotateRootNode->GetParent());
	}
	else
	{
		node->SetParent(nullptr);
	}
		
	if (rotateRootNode->GetParent() == nullptr)
	{
		rotateRootNode->SetParent(node); //check for root
	}
	if (rotateRootNode == rotateRootNode->GetParent()->GetNextLeft())
	{
		rotateRootNode->GetParent()->SetNextLeft(node);
	}
	else
	{
		rotateRootNode->GetParent()->SetNextRight(node);
	}

	node->SetNextRight(rotateRootNode);
	rotateRootNode->SetParent(node);
}

Node* RedBlackTreeAlgorithm::Sibling(Node* node)
{
	return node == node->GetParent()->GetNextLeft() ?
		node->GetParent()->GetNextRight() :
		node->GetParent()->GetNextLeft();
}

//red black Implementations
Node* RedBlackTreeAlgorithm::GrandParent(Node* node)
{
	return node != nullptr && node->GetParent() != nullptr ?
		node->GetParent()->GetParent() :
		nullptr;
}

Node* RedBlackTreeAlgorithm::Uncle(Node* node)
{
	return GrandParent(node) != nullptr ?
		Sibling(node->GetParent()) :
		nullptr;
}