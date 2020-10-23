#pragma once

class Node;

class ITreeAlgorithm
{
public:
	ITreeAlgorithm() = default;
	virtual ~ITreeAlgorithm() = default;
	virtual void BalanceOnInsert(Node* node) = 0;
	virtual void BalanceOnDelete(Node* node) = 0;
};
