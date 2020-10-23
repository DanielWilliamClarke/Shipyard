#pragma once

#include <string>
#include <functional>
#include <memory>

#include "ITreeAlgorithm.h"

class Node;

class BinaryTree
{
public:
	BinaryTree(std::shared_ptr<ITreeAlgorithm> balancer);

	enum class TRAVERSAL_ALGO {
		INORDER,
		REVERSE,
		TOPDOWN
	};

	void Insert(int key, Node* node); 
	void Delete(int key);
	void Traverse(TRAVERSAL_ALGO algo, std::function<void(Node*)> callback) const;
	Node* FindVessel(int key) const;
	Node* FindVessel(std::string name) const;
	std::pair<Node*, float> FindClosest(int key) const;
	int Size() const;
	
private:

	void InsertNode(Node* node, Node* newNode); //private function
	void DeleteNode(int key);

	Node* FindRoot(Node* node) const;
	Node* Find(Node* node, int key) const;
	Node* FindByName(Node* node, std::string name) const;
	std::pair<Node*, float> FindClosestMatch(Node* node, std::pair<Node*, float> closest, int key) const;
	Node* Sucessor(Node* node) const;

	void InOrderTraversal(Node* node, std::function<void(Node*)> callback) const;
	void PostOrderTraversal(Node* node, std::function<void(Node*)> callback) const;
	void NoOrderTraversal(Node* node, std::function<void(Node*)> callback) const;

private:
	std::shared_ptr<ITreeAlgorithm> balancer;
	Node* root;
	int totalElements;
};
