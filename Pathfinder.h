#include <tuple>
#include <vector>

#ifndef PATHFINDER_H
#define PATHFINDER_H


class PathFinder
{
    private:
        std::tuple<int> start;
        std::tuple<int> goal;
        std::vector<std::vector<char>> boardMap;

    public:
        // This is where all children will implement their respective algorithms to pathfind
        virtual void findPath(const std::tuple<int> start, const std::tuple<int> goal, std::vector<std::vector<char>>& boardMap) = 0;
        void setBoardMap(std::vector<std::vector<char>> boardMap);
};

#endif // PATHFINDER_H
