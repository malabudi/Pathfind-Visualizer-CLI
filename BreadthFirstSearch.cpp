#include  "BreadthFirstSearch.h"
#include <queue>

// Constructors
BreadthFirstSearch::BreadthFirstSearch()
:PathFinder() { }

BreadthFirstSearch::BreadthFirstSearch(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap)
:PathFinder(start, goal, boardMap) { }


std::vector< std::pair<int, int> > BreadthFirstSearch::findPath()
{
    std::vector< std::pair<int, int> > path;
    std::map< std::pair<int, int>, std::pair<int, int> >::iterator iterCoords;
    int rowOffset, colOffset;
    std::pair<int, int> current, neighbor;

    // Add a "empty" position indicating its the beginning of the path with -1, -1
    std::pair<int, int> emptyPos(-1, -1);

    // BFS Algorithm uses the queue data structure
    std::queue<std::pair<int, int>> pathQueue;
    pathQueue.push(this->getStart());

    std::map< std::pair<int, int>, std::pair<int, int> > coordsDiscovered {
        {this->getStart(), emptyPos}
    };

    this->displayMap(this->getBoardMap());

    // Begin implementing BFS after setting up
    while (pathQueue.empty() == false)
    {
        current = pathQueue.front();
        pathQueue.pop();

        if (current == this->getGoal())
        {
            path = PathFinder::createFinalPath(this->getStart(), this->getGoal(), coordsDiscovered);
            this->drawPath(path, this->getBoardMap());
            this->displayMap(this->getBoardMap());
            return path;
        }

        // Offset the current position in all four directions
        for (auto iter = PathFinder::offsetCoord.begin(); iter != PathFinder::offsetCoord.end(); ++iter)
        {
            rowOffset = (iter->second).first;
            colOffset = (iter->second).second;

            neighbor.first = current.first + rowOffset;
            neighbor.second = current.second + colOffset;

            // Use a iterator to check if neighbor already exists in the map or not
            iterCoords = coordsDiscovered.find(neighbor);

            if (PathFinder::isValidPosition(neighbor, this->getBoardMap()) && iterCoords == coordsDiscovered.end())
            {
                pathQueue.push(neighbor);
                coordsDiscovered.insert(std::make_pair(neighbor, current));


                this->setBoardMap(neighbor.first, neighbor.second, 'X');
                this->displayMap(this->getBoardMap());
            }
        }
    }

    // no path found, return path not found by returning a vector with only one element inside, {-1, -1}
    std::vector< std::pair<int, int> > pathNotFound = {{-1, -1}};
    return pathNotFound;
}

