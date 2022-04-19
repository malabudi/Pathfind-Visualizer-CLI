#include "Pathfinder.h"

#ifndef DFS_H
#define DFS_H

class DepthFirstSearch : public PathFinder
{
    public:
        DepthFirstSearch(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap);

        virtual std::vector< std::pair<int, int> > findPath();
};

#endif
