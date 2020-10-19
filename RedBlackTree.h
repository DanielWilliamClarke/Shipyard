#pragma once
#include <exception>
#include <string>
#include "Vessel.h"

#define ERRORMSG "No Elements"
#define UNFOUND "Not Found"
#define NAMEFIND "End Search"
#define DUPLICATE "Item already in table"
#define EMPTY "Table is now Empty"
#define CLOSEST "End Closest Match"

class Node;

class binaryTree
{
public:
	binaryTree();
	//insert node to tree
	void insertNode(Node* node, int keyGen, std::string vesselName, BaseVessel* vesselPtr); //private function
	void insert(int keyGen, std::string vesselName, BaseVessel* vesselPtr); //public version

	//allows user to edit a vessel in tree
	void editNode(int key);
	void editNodeName(int Key);
	
	//print functions
	void inOrderPrint(Node* node);//ASC  
	void postOrderPrint(Node* node);//DESC
	void noOrderPrint(Node* node);//no order
	//sets up out at top level;
	void publicPrint(int printSelect);//public function

	//find element in the list and set current pointer
	Node* find(Node* node, int idFind);
	Node* findByName(Node* node, std::string findName);
	Node* findClosestMatch(Node* node, int idFind);
	//find a price bu signature in tree
	void FindVesselID(int idFind);
	//find a vessel by name in tree
	void findVesselName(std::string findName);
	//find closest match to a vessel in tree and return a pecentage match
	void hydrophone(int idFind);
	
	//return the number of nodes in a tree
	int size();
	//delete element pointed at by current pointer
	void deletePublic(int selectID);
	void deleteCurrent(int selectID);
	//to find the sucessor of a node
	Node* sucessor(Node* node);
	
	//red black tree implementations
	Node* grandParent(Node* node);
	Node* uncleNode(Node* node);
	Node* siblingNode(Node* node);
	//rotation Algorithms
	void rotateLeft(Node* node);
	void rotateRight(Node* node);
	//Insertion Cases
	void insertCase1(Node* node);
	void insertCase2(Node* node);
	void insertCase3(Node* node);
	void insertCase4(Node* node);
	void insertCase5(Node* node);
	//deletion cases
	void deleteCase1(Node* node);
	void deleteCase2(Node* node);
	void deleteCase3(Node* node);
	void deleteCase4(Node* node);
	void deleteCase5(Node* node);
	void deleteCase6(Node* node);

	Node* findRoot(Node* node);
	
private:
	//probably need some data members
	int _element;
	double _percentageP1; //calculating percentage
	double _percentage;
	double _max; // for closest matcH
	Node* _root; //first node pointer
	Node* _closestNode; //closest node used in hydrophone

	bool _foundFlag;
	
};
