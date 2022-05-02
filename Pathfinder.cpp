#include "Pathfinder.h"
#include <iostream>

const std::map< std::string, std::pair<int, int> > PathFinder::offsetCoord {
    {"right", {0, 1} },
    {"left", {0, -1} },
    {"up", {-1, 0} },
    {"down", {1, 0} }
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
void PathFinder::setBoardMap(int rowCoord, int colCoord, char symbol)
{
    this->boardMap[rowCoord][colCoord] = symbol;
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
void PathFinder::drawPath(std::vector< std::pair<int, int> > path, std::vector<std::vector<char>> boardMap)
{
    for (std::pair<int, int> coordinates :  path)
        this->setBoardMap(coordinates.first, coordinates.second, 'O');
}

bool PathFinder::isValidPosition(std::pair<int, int> position, std::vector<std::vector<char>> boardMap)
{
    int i = position.first;
    int j = position.second;
    int rowLen = boardMap.size();
    int colLen = boardMap[0].size();

    return ( ( (i < rowLen && i >= 0) && (j < colLen && j >= 0) ) &&  (boardMap[i][j] != '*') );
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
    std::cout << "---------------------------------------------------------------------------------------------------------------------" << std::endl;
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

    std::cout << "---------------------------------------------------------------------------------------------------------------------\n" << std::endl;
}
