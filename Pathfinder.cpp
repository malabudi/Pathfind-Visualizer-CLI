#include "Pathfinder.h"
#include <iostream>

const std::map< std::string, std::pair<int, int> > PathFinder::offsetCoord {
    {"right", {1, 0} },
    {"up", {0, 1} },
    {"left", {-1, 0} },
    {"down", {0, -1} }
};

// Constructors
PathFinder::PathFinder()
{
    this->start = {0, 0};
    this->goal = {0, 0};
}

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
void PathFinder::setBoardMap(int xCoord, int yCoord, char symbol)
{
    this->boardMap[xCoord][yCoord] = symbol;
}

void PathFinder::setBoardMap(std::vector<std::vector<char>> boardMap)
{
    this->boardMap = boardMap;
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
    int colLen = boardMap[0].size();

    return ( ( (xPos < rowLen && xPos >= 0) && (yPos < colLen && yPos >= 0) ) &&  (boardMap[xPos][yPos] != '*') );
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


void PathFinder::displayMap(const std::vector<std::vector<char>>& boardMap) {
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\t";

    // Display what column is being shown numerically
    for (int i = 0; i < boardMap[0].size(); ++i)
    {
        // Single digits take up more white space
        if ((i + 1) < 10)
            std::cout << "  " << i + 1 << " ";

        // Double digits take up less space, no triple digits since maps will not be that big for a command line interface
        else
            std::cout << " " << i + 1 << " ";
    }

    std::cout << std::endl;

    for (int x = 0; x < boardMap.size(); ++x)
    {
        std::cout << " " << x + 1 << "\t| ";

        for (int y = 0; y < boardMap[x].size(); ++y)
        {
            std::cout << boardMap[x][y] << " | ";
        }

        std::cout << std::endl;
    }

    std::cout << "----------------------------------------------------------------------------------------------\n" << std::endl;
}
