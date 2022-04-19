#include "DepthFirstSearch.h"
#include <stack>

DepthFirstSearch::DepthFirstSearch(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap)
:PathFinder(start, goal, boardMap)
{

}

std::vector< std::pair<int, int> > DepthFirstSearch::findPath()
{
    // Add a "null" position indicating its the beginning of the path
    std::pair<int, int> nullPos(-1, -1);

    // DFS Algorithm uses a stack
    std::stack<std::pair<int, int>> pathStack;

    // We will use a map to keep track of the successful path discovered, initialize the map with start key and nulLPos val
    std::map< std::pair<int, int>, std::pair<int, int> > coordsDiscovered {
        {this->getStart(), nullPos}
    };

    pathStack.push(this->getStart());

    std::pair<int, int> current = pathStack.top();
    pathStack.pop();

    // Begin implementing DFS after setting up
    while (pathStack.empty() == false)
    {
        // Find and return path
    }

    // no path found, return path not found
}
