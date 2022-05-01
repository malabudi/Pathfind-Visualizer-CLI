#include <utility>
#include <vector>
#include <map>

#ifndef PATHFINDER_H
#define PATHFINDER_H


class PathFinder
{
    private:
        std::pair<int, int> start;
        std::pair<int, int> goal;
        std::vector<std::vector<char>> boardMap;

    protected:
        static const std::map< std::string, std::pair<int, int> > offsetCoord;

        bool isValidPosition(std::pair<int, int> position, std::vector<std::vector<char>> boardMap);
        void drawPath(std::vector< std::pair<int, int> > path, std::vector<std::vector<char>> boardMap);

        // Returns the vector of the path created
        std::vector< std::pair<int, int> > createFinalPath(std::pair<int, int> start, std::pair<int, int> goal, std::map< std::pair<int, int>, std::pair<int, int> > coordsDiscovered);

    public:
        PathFinder();
        PathFinder(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap);

        std::vector<std::vector<char>> getBoardMap();
        std::pair<int, int> getStart();
        std::pair<int, int> getGoal();

        void setBoardMap(int xCoord, int yCoord, char symbol);
        void setBoardMap(std::vector<std::vector<char>> boardMap);
        void setStart(std::pair<int, int> start);
        void setGoal(std::pair<int, int> goal);

        void static displayMap(const std::vector<std::vector<char>>& boardMap);

        // This is where all children will implement their respective algorithms
        virtual std::vector< std::pair<int, int> > findPath() = 0;


};

#endif // PATHFINDER_H
