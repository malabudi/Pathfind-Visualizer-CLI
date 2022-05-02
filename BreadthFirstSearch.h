#include "Pathfinder.h"

#ifndef BFS_H
#define BFS_H

class BreadthFirstSearch : public PathFinder
{
    public:
        BreadthFirstSearch();
        BreadthFirstSearch(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap);

        virtual std::vector< std::pair<int, int> > findPath();
};

#endif
