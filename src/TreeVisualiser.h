#pragma once 

#include <ostream>
#include <vector>
#include <string>

class Node;

struct CellDisplay {
    CellDisplay() : present(false) {}
    CellDisplay(std::string valstr) : valstr(valstr), present(true) {}

    std::string valstr;
    bool present;
};

class TreeVisualiser
{
public:
	TreeVisualiser() = default;
	virtual ~TreeVisualiser() = default;

	void Display(Node* root, std::ostream& stream) const;
private:
    unsigned int GetMaxDepth(Node* root) const;
    std::vector<std::vector<CellDisplay>> GetRowDisplay(Node* root) const;
    std::vector<std::string> RowFormatter(const std::vector<std::vector<CellDisplay>>& rowsDisp) const;

    static void TrimRowsLeft(std::vector<std::string>& rows);
};