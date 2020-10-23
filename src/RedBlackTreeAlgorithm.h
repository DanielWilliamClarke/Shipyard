#pragma once

#include "ITreeAlgorithm.h"

class Node;

class RedBlackTreeAlgorithm : public ITreeAlgorithm
{
public:
	RedBlackTreeAlgorithm() = default;
	virtual ~RedBlackTreeAlgorithm() = default;

	virtual void BalanceOnInsert(Node* node) override;
	virtual void BalanceOnDelete(Node* node) override;

private:
	//Insertion Cases
	void InsertCase2(Node* node);
	void InsertCase3(Node* node);
	void InsertCase4(Node* node);
	void InsertCase5(Node* node);

	//deletion cases
	void DeleteCase2(Node* node);
	void DeleteCase3(Node* node);
	void DeleteCase4(Node* node);
	void DeleteCase5(Node* node);
	void DeleteCase6(Node* node);

	//rotation Algorithms
	void RotateLeft(Node* node);
	void RotateRight(Node* node);

	//red black tree implementations
	Node* GrandParent(Node* node);
	Node* Uncle(Node* node);
	Node* Sibling(Node* node);
};