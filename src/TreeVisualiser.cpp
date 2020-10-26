#include <sstream>

#include "TreeVisualiser.h"

#include "Node.h"
#include "Vessel.h"

// Dumps a representation of the tree to cout
void TreeVisualiser::Display(Node* root, std::ostream& stream) const
{
    if (GetMaxDepth(root) == 0)
    {
        stream << "EMPTY TREE" << std::endl;
        return;
    }

    // This tree is not empty, so get a list of node values...
    const auto rowsDisp = GetRowDisplay(root);
    // then format these into a text representation...
    auto formattedRows = RowFormatter(rowsDisp);
    // then trim excess space characters from the left sides of the text...
    TrimRowsLeft(formattedRows);
    // then dump the text to cout.
    for (const auto& row : formattedRows) 
    {
        stream << ' ' << row << std::endl;
    }
}

unsigned int TreeVisualiser::GetMaxDepth(Node* root) const
{ 
    return root ? root->MaxDepth() : 0;
}

// get_row_display builds a vector of vectors of cell_display structs
// each vector of cell_display structs represents one row, starting at the root
std::vector<std::vector<CellDisplay>> TreeVisualiser::GetRowDisplay(Node* root) const
{
    // start off by traversing the tree to
    // build a vector of vectors of Node pointers
    std::vector<Node*> stack;
    std::vector<std::vector<Node*>> rows;
    if (!root)
    {
        return {};
    }

    Node* currentNode = root;
    const int maxDepth = root->MaxDepth();
    rows.resize(maxDepth);
    int depth = 0;
    for (;;) 
    {
        // Max-depth Nodes are always a leaf or null
        // This special case blocks deeper traversal
        if (depth == maxDepth - 1)
        {
            rows[depth].push_back(currentNode);
            if (depth == 0)
            {
                break;
            }
            --depth;
            continue;
        }

        // First visit to node?  Go to left child.
        if (stack.size() == depth) 
        {
            rows[depth].push_back(currentNode);
            stack.push_back(currentNode);
            if (currentNode)
            {
                currentNode = currentNode->GetNextLeft();
            }
            ++depth;
            continue;
        }

        // Odd child count? Go to right child.
        if (rows[depth + 1].size() % 2) 
        {
            currentNode = stack.back();
            if (currentNode)
            {
                currentNode = currentNode->GetNextRight();
            }
            ++depth;
            continue;
        }

        // Time to leave if we get here

        // Exit loop if this is the root
        if (depth == 0)
        {
            break;
        }

        stack.pop_back();
        currentNode = stack.back();
        --depth;
    }

    // Use rows of Node pointers to populate rows of cell_display structs.
    // All possible slots in the tree get a cell_display struct,
    // so if there is no actual Node at a struct's location,
    // its boolean "present" field is set to false.
    // The struct also contains a string representation of
    // its Node's value, created using a std::stringstream object.
    std::vector<std::vector<CellDisplay>> rowsDisp;
    std::stringstream ss;
    for (const auto& row : rows) 
    {
        rowsDisp.emplace_back();
        for (Node* node : row) 
        {
            if (node)
            {
                ss << node->GetVessel()->GetSignature();
                rowsDisp.back().push_back(CellDisplay(ss.str()));
                ss.clear();
            }
            else 
            {
                rowsDisp.back().push_back(CellDisplay());
            }
        }
    }
    return rowsDisp;
}

// row_formatter takes the vector of rows of cell_display structs 
// generated by get_row_display and formats it into a test representation
// as a vector of strings
std::vector<std::string> TreeVisualiser::RowFormatter(const std::vector<std::vector<CellDisplay>>& rowsDisp) const 
{
    using stringSize = std::string::size_type;

    // First find the maximum value string length and put it in cell_width
    stringSize cellWidth = 0;
    for (const auto& rowDisp : rowsDisp)
    {
        for (const auto& cellDisplay : rowDisp) 
        {
            if (cellDisplay.present && cellDisplay.valstr.length() > cellWidth)
            {
                cellWidth = cellDisplay.valstr.length();
            }
        }
    }

    // make sure the cell_width is an odd number
    if (cellWidth % 2 == 0)
    {
        ++cellWidth;
    }

    // formatted_rows will hold the results
    std::vector<std::string> formattedRows;

    // some of these counting variables are related,
    // so its should be possible to eliminate some of them.
    stringSize rowCount = rowsDisp.size();

    // this row's element count, a power of two
    stringSize rowElemCount = 1 << (rowCount - 1);

    // left_pad holds the number of space charactes at the beginning of the bottom row
    stringSize leftPad = 0;

    // Work from the level of maximum depth, up to the root
    // ("formatted_rows" will need to be reversed when done) 
    for (stringSize r = 0; r < rowCount; ++r) 
    {
        const auto& cellDisplayRow = rowsDisp[rowCount - r - 1]; // r reverse-indexes the row
        // "space" will be the number of rows of slashes needed to get
        // from this row to the next.  It is also used to determine other
        // text offsets.
        stringSize space = (stringSize(1) << r) * (cellWidth + 1) / 2 - 1;
        // "row" holds the line of text currently being assembled
        std::string row;
        // iterate over each element in this row
        for (stringSize count = 0; count < rowElemCount; ++count) 
        {
            // add padding, more when this is not the leftmost element
            row += std::string(count ? leftPad * 2 + 1 : leftPad, ' ');
            if (cellDisplayRow[count].present) 
            {
                // This position corresponds to an existing Node
                const std::string& valstr = cellDisplayRow[count].valstr;
                // Try to pad the left and right sides of the value string
                // with the same number of spaces.  If padding requires an
                // odd number of spaces, right-sided children get the longer
                // padding on the right side, while left-sided children
                // get it on the left side.
                stringSize longPadding = cellWidth - valstr.length();
                stringSize shortPadding = longPadding / 2;
                longPadding -= shortPadding;
                row += std::string(count % 2 ? shortPadding : longPadding, ' ');
                row += valstr;
                row += std::string(count % 2 ? longPadding : shortPadding, ' ');
            }
            else
            {
                // This position is empty, Nodeless...
                row += std::string(cellWidth, ' ');
            }
        }
        // A row of spaced-apart value strings is ready, add it to the result vector
        formattedRows.push_back(row);

        // The root has been added, so this loop is finsished
        if (rowElemCount == 1)
        {
            break;
        }

        // Add rows of forward- and back- slash characters, spaced apart
        // to "connect" two rows' Node value strings.
        // The "space" variable counts the number of rows needed here.
        stringSize leftSpace = space + 1;
        stringSize rightSpace = space - 1;
        for (stringSize sr = 0; sr < space; ++sr)
        {
            std::string row;
            for (stringSize count = 0; count < rowElemCount; ++count)
            {
                if (count % 2 == 0)
                {
                    row += std::string(count ? leftSpace * 2 + 1 : leftSpace, ' ');
                    row += cellDisplayRow[count].present ? '/' : ' ';
                    row += std::string(rightSpace + 1, ' ');
                }
                else 
                {
                    row += std::string(rightSpace, ' ');
                    row += cellDisplayRow[count].present ? '\\' : ' ';
                }
            }
            formattedRows.push_back(row);
            ++leftSpace;
            --rightSpace;
        }
        leftPad += space + 1;
        rowElemCount /= 2;
    }

    // Reverse the result, placing the root node at the beginning (top)
    std::reverse(formattedRows.begin(), formattedRows.end());

    return formattedRows;
}

// Trims an equal number of space characters from
// the beginning of each string in the vector.
// At least one string in the vector will end up beginning
// with no space characters.
void TreeVisualiser::TrimRowsLeft(std::vector<std::string>& rows)
{
    if (!rows.size())
    {
        return;
    }

    auto min_space = rows.front().length();
    for (const auto& row : rows) 
    {
        auto index = row.find_first_not_of(' ');
        if (index == std::string::npos)
        {
            index = row.length();
        }
        if (index == 0)
        {
            return;
        }
        if (index < min_space)
        {
            min_space = index;
        }
    }

    for (auto& row : rows) 
    {
        row.erase(0, min_space);
    }
}