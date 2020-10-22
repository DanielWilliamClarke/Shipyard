#pragma once

#include <string>
#include <memory>
#include <map>

class Node;
class BaseVessel;
class BinaryTree;

class Library
{
public:
	Library(std::shared_ptr<BinaryTree> tree);

	template<class KEY, class OPTION, class DATA>
	void PrintOptions(std::string title, std::map<KEY, std::pair<OPTION, DATA>> options) const;

	template<class KEY, class OPTION, class DATA>
	DATA MakeSelection(std::map<KEY, std::pair<OPTION, DATA>> options) const;

	void InsertVessel() const;
	void DeleteVessel() const;
	void GetVessel() const;
	void SelectEditVessel() const;
	void Size() const;
	void PrintVessels() const;
	void Hydrophone() const;
	void EndGraceful() const;
private: 

	BaseVessel* FillVessel() const;
	void StreamOut(int key, BaseVessel* vesselPtr) const;
	int ValidateCin() const;
	void StreamPercent(std::pair<Node*, float> closest) const;

private:
	std::shared_ptr<BinaryTree> tree;
};