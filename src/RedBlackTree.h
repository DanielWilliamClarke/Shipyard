#pragma once

#include <string>
#include <functional>

class Node;
class BaseVessel;

class BinaryTree
{
public:
	BinaryTree();

	enum class PRINTMODE {
		ASC,
		DESC,
		NON
	};

	void Insert(int key, BaseVessel* vessel); 
	void Delete(int key);
	void Print(PRINTMODE option, std::function<void(Node*)> callback);
	void EditNode(int key, BaseVessel* vessel);
	Node* FindVessel(int key);
	Node* FindVessel(std::string name);
	std::pair<Node*, float> FindClosest(int key);
	int Size();
	
private:
	void InsertNode(Node* node, int key, BaseVessel* vessel); //private function
	//Insertion Cases
	void InsertCase1(Node* node);
	void InsertCase2(Node* node);
	void InsertCase3(Node* node);
	void InsertCase4(Node* node);
	void InsertCase5(Node* node);

	void DeleteNode(int key);
	//deletion cases
	void DeleteCase1(Node* node);
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
	Node* Sucessor(Node* node);

	Node* FindRoot(Node* node);
	Node* Find(Node* node, int key);
	Node* FindByName(Node* node, std::string name);
	std::pair<Node*, float> FindClosestMatch(Node* node, std::pair<Node*, float> closest, int key);

	void InOrderPrint(Node* node, std::function<void(Node*)> callback);
	void PostOrderPrint(Node* node, std::function<void(Node*)> callback);
	void NoOrderPrint(Node* node, std::function<void(Node*)> callback);
private:
	Node* root;
	int totalElements;
};
