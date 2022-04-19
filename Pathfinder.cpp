#include "Pathfinder.h"

const std::map< std::string, std::pair<int, int> > offsetCoord {
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
    int rowCol = boardMap[0].size();

    //              If the position selected is within the map               AND     If the position is not on a obstacle
    return ( ( (xPos < rowLen && xPos >= 0) && (yPos < rowCol && yPos >= 0) ) &&  (boardMap[xPos][yPos] != '*') );
}


void createPath(const std::pair<int, int>& start, std::pair<int, int>& goal, const std::map< std::pair<int, int>, std::pair<int, int> >& coordsDiscovered)
{

}
