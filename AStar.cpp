#include "AStar.h"
#include <queue>
#include <cmath>

AStar::AStar() { }

AStar::AStar(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap) { }

// Also known as the Manhattan distance, this formula is often used to calculate the shortest distance, very popular with GPS and games
int AStar::calcHeuristicDistance(const std::pair<int, int>& goal, const std::pair<int, int>& neighbor)
{
    int x1 = goal.first;
    int y1 = goal.second;

    int x2 = neighbor.first;
    int y2 = neighbor.second;

    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector< std::pair<int, int> > AStar::findPath()
{
    // A Star algorithm uses the priority queue along with calculating the shortest distance, read below for more info:
    // By giving a PQ the datatype, and a vector + greater with the datatype for the pq, it will treat it as a min heap in c++
    // The int value in the outer pair will represent the f distance, the g value + the heuristic distance
    // The g value represents how far a node is from the start, for every node the path discovers it adds by one
    std::priority_queue< std::pair< int, std::pair<int, int> >, std::vector< std::pair< int, std::pair<int, int> > >, std::greater< std::pair< int, std::pair<int, int> > > > pathPriorityQueue;
    pathPriorityQueue.push(std::make_pair(0, this->getStart()));

    std::pair<int, int> emptyPos(-1, -1);
    std::map< std::pair<int, int>, std::pair<int, int> > coordsDiscovered {
        {this->getStart(), emptyPos}
    };

    std::map< std::pair<int, int>, int > gValues {
        {this->getStart(), 0}
    };

    std::vector< std::pair<int, int> > path;
    std::map< std::pair<int, int>, int >::iterator iterG_Value;
    int rowOffset, colOffset, neighborG_Value, fValue;
    std::pair<int, int> current, neighbor;

    // Begin implementing A* after setting up
    while (pathPriorityQueue.empty() == false)
    {
        current = pathPriorityQueue.top().second;
        pathPriorityQueue.pop();

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
            iterG_Value = gValues.find(neighbor);

            if (PathFinder::isValidPosition(neighbor, this->getBoardMap()) && iterG_Value == gValues.end())
            {
                neighborG_Value = gValues.at(current) + 1;
                gValues.insert(std::make_pair(neighbor, neighborG_Value));
                fValue = neighborG_Value + this->calcHeuristicDistance(this->getGoal(), neighbor);
                pathPriorityQueue.push(std::make_pair(fValue, neighbor));
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
