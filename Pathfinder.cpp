#include "Pathfinder.h"
#include <iostream>

const std::map< std::string, std::pair<int, int> > PathFinder::offsetCoord {
    {"right", {1, 0} },
    {"up", {0, 1} },
    {"left", {-1, 0} },
    {"down", {0, -1} }
};

// Constructors
PathFinder::PathFinder(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap)
{
    this->start = start;
    this->goal = goal;
    this->boardMap = boardMap;
}


// Gets
std::vector<std::vector<char>> PathFinder::getBoardMap()
{
    return this->boardMap;
}

std::pair<int, int> PathFinder::getStart()
{
    return this->start;
}

std::pair<int, int> PathFinder::getGoal()
{
    return this->goal;
}


// Sets
void PathFinder::setBoardMap(int xCoord, int yCoord)
{
    this->boardMap[xCoord][yCoord] = 'X';
}

void PathFinder::setStart(std::pair<int, int> start)
{
    this->start = start;
}

void PathFinder::setGoal(std::pair<int, int> goal)
{
    this->goal = goal;
}


// Methods
bool PathFinder::isValidPosition(std::pair<int, int> position, std::vector<std::vector<char>> boardMap)
{
    int xPos = position.first;
    int yPos = position.second;
    int rowLen = boardMap.size();
    int rowCol = boardMap[0].size();

    //              If the position selected is within the map               AND     If the position is not on a obstacle
    return ( ( (xPos < rowLen && xPos >= 0) && (yPos < rowCol && yPos >= 0) ) &&  (boardMap[xPos][yPos] != '*') );
}


std::vector< std::pair<int, int> > PathFinder::createFinalPath(std::pair<int, int> start, std::pair<int, int> goal, std::map< std::pair<int, int>, std::pair<int, int> > coordsDiscovered)
{
    std::vector< std::pair<int, int> > path;

    std::pair<int, int> currentCoord = goal;

    // Traverse through the map backwards starting at the goal to push back all coords traversed into the path vector
    while (currentCoord != start) {
        path.push_back(currentCoord);
        currentCoord = coordsDiscovered[currentCoord];
    }

    path.push_back(start);

    return path;
}


void PathFinder::displayMap() {
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;

    for (std::vector<char> row : this->boardMap)
    {
        std::cout << " ";

        for (char col : row)
        {
            std::cout << col << " | ";
        }

        std::cout << std::endl;
    }

    std::cout << "----------------------------------------------------------------------------------------------\n" << std::endl;
}
