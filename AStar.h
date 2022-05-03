#include "Pathfinder.h"

#ifndef ASTAR_H
#define ASTAR_H

class AStar : public PathFinder
{
    private:
        // Also known as the Manhattan distance
        int calcHeuristicDistance(const std::pair<int, int>& goal, const std::pair<int, int>& neighbor);

    public:
        AStar();
        AStar(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap);

        virtual std::vector< std::pair<int, int> > findPath();
};

#endif // ASTAR_H
