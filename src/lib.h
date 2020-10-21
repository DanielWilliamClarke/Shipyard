#pragma once

#include <string>
#include <memory>

class Node;
class BaseVessel;
class BinaryTree;

class Library
{
public:
	Library(std::shared_ptr<BinaryTree> tree);

	void InsertVessel() const;
	void DeleteVessel() const;
	void GetVessel() const;
	void SelectEditVessel() const;
	void SizeOfList() const;
	void PrintVessels() const;
	void HydrophoneSim() const;
	void EndGraceful() const;
private: 
	void StreamOut(int key, std::string vesselName, BaseVessel* vesselPtr) const;
	BaseVessel* FillVesselPtr() const;
	std::string SetName() const;
	int ValidateCin() const;
	void Percent(Node* node, double percentage) const;

private:
	std::shared_ptr<BinaryTree> tree;
};