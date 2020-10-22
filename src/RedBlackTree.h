#pragma once

#include <string>
#include <functional>

class Node;
class BaseVessel;

class BinaryTree
{
public:
	BinaryTree();

	enum class TRAVERSAL_ALGO {
		INORDER,
		REVERSE,
		TOPDOWN
	};

	void Insert(int key, Node* node); 
	void Delete(int key);
	void Traverse(TRAVERSAL_ALGO algo, std::function<void(Node*)> callback);
	Node* FindVessel(int key);
	Node* FindVessel(std::string name);
	std::pair<Node*, float> FindClosest(int key);
	int Size();
	
private:
	void InsertNode(Node* node, Node* newNode); //private function
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

	void InOrderTraversal(Node* node, std::function<void(Node*)> callback);
	void PostOrderTraversal(Node* node, std::function<void(Node*)> callback);
	void NoOrderTraversal(Node* node, std::function<void(Node*)> callback);
private:
	Node* root;
	int totalElements;
};
