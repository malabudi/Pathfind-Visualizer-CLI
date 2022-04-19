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

        static const std::map< std::string, std::pair<int, int> > offsetCoord;

    // All gets and sets will be in protected for the parent class
    protected:
        std::vector<std::vector<char>> getBoardMap();
        std::pair<int, int> getStart();
        std::pair<int, int> getGoal();

        void setBoardMap(std::vector<std::vector<char>> boardMap);
        void setStart(std::pair<int, int> start);
        void setGoal(std::pair<int, int> goal);

        std::vector< std::pair<int, int> > createPath(const std::pair<int, int>& start, std::pair<int, int>& goal, const std::map< std::pair<int, int>, std::pair<int, int> >& coordsDiscovered);

    public:
        PathFinder(std::pair<int, int> start, std::pair<int, int> goal, std::vector<std::vector<char>> boardMap);

        // This is where all children will implement their respective algorithms | Abstract member function
        virtual std::vector< std::pair<int, int> > findPath() = 0;

        bool isValidPosition(std::pair<int, int> position, std::vector<std::vector<char>> boardMap);

};

#endif // PATHFINDER_H
