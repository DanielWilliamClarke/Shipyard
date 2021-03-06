#pragma once

class BaseVessel;

class Node
{
public:
	Node(BaseVessel* vessel, Node* parent = nullptr);
	virtual ~Node() = default;

	static int GenerateKey();
	BaseVessel* GetVessel() const;
	void SetVessel(BaseVessel* vessel);
	void SetParent(Node *parent);
	Node* GetParent() const;
	void SetNextLeft(Node *nextLeft);
	Node* GetNextLeft() const;
	void SetNextRight(Node *nextRight);
	Node* GetNextRight() const;
	void SetColour(bool Colour);
	bool GetColour() const;

	unsigned int MaxDepth() const;
private:
	BaseVessel *vessel; //allows data to be put in tree regardless of type
	Node *parent; //pointer to node parent
	Node *left; //pointer to the next left node
	Node *right;// pointer to next right node
	bool colour; // red is true, black is false
};