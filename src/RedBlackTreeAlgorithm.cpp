#include "RedBlackTreeAlgorithm.h"
#include "Node.h"

void RedBlackTreeAlgorithm::BalanceOnInsert(Node* node)
{
	if (node->GetParent() == nullptr)
		node->SetColour(false); //black
	else
		InsertCase2(node);
}

void RedBlackTreeAlgorithm::InsertCase2(Node* node)
{
	if (node->GetParent()->GetColour() == false)
		return; /* tree's all cool yo */
	else
		InsertCase3(node);
}

void RedBlackTreeAlgorithm::InsertCase3(Node* node)
{
	Node* uNode = Uncle(node);
	Node* gpNode;

	if ((uNode != nullptr) && (uNode->GetColour() == true))
	{
		node->GetParent()->SetColour(false); //black
		uNode->SetColour(false);			 // black
		gpNode = GrandParent(node);
		gpNode->SetColour(true); //red
		BalanceOnInsert(gpNode);
	}
	else
		InsertCase4(node);
}

void RedBlackTreeAlgorithm::InsertCase4(Node* node)
{
	Node* gpNode = GrandParent(node);

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

void RedBlackTreeAlgorithm::InsertCase5(Node* node)
{
	Node* gpNode = GrandParent(node);

	node->GetParent()->SetColour(false); //black
	gpNode->SetColour(true);			 // red

	if (node == node->GetParent()->GetNextLeft())
		RotateRight(gpNode);
	else
		RotateLeft(gpNode);
}

void RedBlackTreeAlgorithm::BalanceOnDelete(Node* node)
{
	if (node->GetParent() != nullptr)
		DeleteCase2(node);
}

void RedBlackTreeAlgorithm::DeleteCase2(Node* node)
{
	Node* sibNode = Sibling(node);

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

void RedBlackTreeAlgorithm::DeleteCase3(Node* node)
{
	Node* sibNode = Sibling(node);

	if ((node->GetParent()->GetColour() == false) && (sibNode->GetColour() == false) && (sibNode->GetNextLeft()->GetColour() == false) && (sibNode->GetNextRight()->GetColour() == false))
	{
		sibNode->SetColour(true); // is now red
		BalanceOnDelete(node->GetParent());
	}
	else
		DeleteCase4(node);
}

void RedBlackTreeAlgorithm::DeleteCase4(Node* node)
{
	Node* sibNode = Sibling(node);

	if ((node->GetParent()->GetColour() == true) && (sibNode->GetColour() == false) && (sibNode->GetNextLeft()->GetColour() == false) && (sibNode->GetNextRight()->GetColour() == false))
	{
		sibNode->SetColour(true);
		node->GetParent()->SetColour(false);
	}
	else
		DeleteCase5(node);
}

void RedBlackTreeAlgorithm::DeleteCase5(Node* node)
{
	Node* sibNode = Sibling(node);

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

void RedBlackTreeAlgorithm::DeleteCase6(Node* node)
{
	Node* sibNode = Sibling(node);

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

//rotation algorithms
void RedBlackTreeAlgorithm::RotateLeft(Node* node)
{
	Node* rotateRootNode;

	rotateRootNode = node->GetNextRight();
	node->SetNextRight(rotateRootNode->GetNextLeft());

	if (rotateRootNode->GetNextLeft() != nullptr)
		rotateRootNode->GetNextLeft()->SetParent(node);

	if (node->GetParent() != nullptr)
		rotateRootNode->SetParent(node->GetParent());
	else
		rotateRootNode->SetParent(nullptr);

	if (node->GetParent() == nullptr)
		node->SetParent(rotateRootNode); //check for root
	else if (node == node->GetParent()->GetNextLeft())
		node->GetParent()->SetNextLeft(rotateRootNode);
	else
		node->GetParent()->SetNextRight(rotateRootNode);

	rotateRootNode->SetNextLeft(node);
	node->SetParent(rotateRootNode);
}

void RedBlackTreeAlgorithm::RotateRight(Node* rotateRootNode)
{
	Node* node;

	node = rotateRootNode->GetNextLeft();
	rotateRootNode->SetNextLeft(node->GetNextRight());

	if (node->GetNextRight() != nullptr)
		node->GetNextRight()->SetParent(rotateRootNode);

	if (rotateRootNode->GetParent() != nullptr)
		node->SetParent(rotateRootNode->GetParent());
	else
		node->SetParent(nullptr);

	if (rotateRootNode->GetParent() == nullptr)
		rotateRootNode->SetParent(node); //check for root
	if (rotateRootNode == rotateRootNode->GetParent()->GetNextLeft())
		rotateRootNode->GetParent()->SetNextLeft(node);
	else
		rotateRootNode->GetParent()->SetNextRight(node);

	node->SetNextRight(rotateRootNode);
	rotateRootNode->SetParent(node);
}

Node* RedBlackTreeAlgorithm::Sibling(Node* node)
{
	if (node == node->GetParent()->GetNextLeft())
		return node->GetParent()->GetNextRight();
	else
		return node->GetParent()->GetNextLeft();
}

//red black Implementations
Node* RedBlackTreeAlgorithm::GrandParent(Node* node)
{
	if ((node != nullptr) && (node->GetParent() != nullptr))
		return node->GetParent()->GetParent();
	else
		return node = nullptr;
}

Node* RedBlackTreeAlgorithm::Uncle(Node* node)
{
	Node* gpNode = GrandParent(node);

	if (gpNode == nullptr)
		return nullptr; // no GrandParent therefore parent is root
	if (node->GetParent() == gpNode->GetNextLeft())
		return gpNode->GetNextRight();
	else
		return gpNode->GetNextLeft();
}