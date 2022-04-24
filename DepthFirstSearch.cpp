#include "DepthFirstSearch.h"
#include <stack>

DepthFirstSearch::DepthFirstSearch(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap)
:PathFinder(start, goal, boardMap) { }

std::vector< std::pair<int, int> > DepthFirstSearch::findPath()
{
    std::map< std::pair<int, int>, std::pair<int, int> >::iterator iterCoords;
    int xOffset, yOffset;
    std::pair<int, int> current, neighbor;

    // Add a "empty" position indicating its the beginning of the path with -1, -1
    std::pair<int, int> emptyPos(-1, -1);

    // DFS Algorithm uses the stack data structure
    std::stack<std::pair<int, int>> pathStack;
    pathStack.push(this->getStart());

    // We will use a map to keep track of the successful path discovered, initialize the map with start key and nulLPos val
    std::map< std::pair<int, int>, std::pair<int, int> > coordsDiscovered {
        {this->getStart(), emptyPos}
    };

    this->displayMap();

    // Begin implementing DFS after setting up
    while (pathStack.empty() == false)
    {
        current = pathStack.top();
        pathStack.pop();

        if (current == this->getGoal())
            return PathFinder::createFinalPath(this->getStart(), this->getGoal(), coordsDiscovered);

        // Offset the current position in all four directions
        for (auto iter = PathFinder::offsetCoord.begin(); iter != PathFinder::offsetCoord.end(); ++iter)
        {
            xOffset = (iter->second).first;
            yOffset = (iter->second).second;

            neighbor.first = current.first + xOffset;
            neighbor.second = current.second + yOffset;

            // Use a iterator to check if neighbor already exists in the map or not
            iterCoords = coordsDiscovered.find(neighbor);

            if (PathFinder::isValidPosition(neighbor, this->getBoardMap()) && iterCoords == coordsDiscovered.end()) {
                pathStack.push(neighbor);
                coordsDiscovered.insert(std::make_pair(neighbor, current));

                // Update and display the map
                this->setBoardMap(neighbor.first, neighbor.second);
                this->displayMap();
            }

        }
    }

    // no path found, return path not found by returning a vector with only one element inside, {-1, -1}
    std::vector< std::pair<int, int> > pathNotFound = {{-1, -1}};
    return pathNotFound;
}
