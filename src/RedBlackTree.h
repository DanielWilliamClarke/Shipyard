#pragma once
#include <exception>
#include <string>

#define ERRORMSG "No Elements"
#define UNFOUND "Not Found"
#define NAMEFIND "End Search"
#define DUPLICATE "Item already in table"
#define EMPTY "Table is now Empty"
#define CLOSEST "End Closest Match"

class Node;
class BaseVessel;

class BinaryTree
{
public:
	BinaryTree();
	void Insert(int keyGen, BaseVessel* vesselPtr); //public version
	void EditNode(int key, BaseVessel* vesselPtr);
	void PublicPrint(int printSelect);//public function
	void FindVesselID(int idFind);
	void FindVesselName(std::string findName);
	void Hydrophone(int idFind);
	int Size();
	void DeletePublic(int selectID);

private:
	void InsertNode(Node* node, int keyGen, BaseVessel* vesselPtr); //private function
	//Insertion Cases
	void InsertCase1(Node* node);
	void InsertCase2(Node* node);
	void InsertCase3(Node* node);
	void InsertCase4(Node* node);
	void InsertCase5(Node* node);

	void DeleteCurrent(int selectID);
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
	Node* Find(Node* node, int idFind);
	Node* FindByName(Node* node, std::string findName);
	Node* FindClosestMatch(Node* node, int idFind);

	void InOrderPrint(Node* node);
	void PostOrderPrint(Node* node);
	void NoOrderPrint(Node* node);
private:
	int element;
	double percentageP1; //calculating percentage
	double percentage;
	double max; // for closest matcH
	Node* root; //first node pointer
	Node* closestNode; //closest node used in hydrophone
	bool foundFlag;
};
