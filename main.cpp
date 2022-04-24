#include <iostream>
#include "Pathfinder.h"
#include "DepthFirstSearch.h"

int main()
{
    std::vector< std::vector<char> > tempMap = {
        {'S', '*', ' '},
        {' ', ' ', ' '},
        {' ', ' ', 'G'}
    };

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> goal = {2, 2};

    DepthFirstSearch objPathDFS = DepthFirstSearch(start, goal, tempMap);
    objPathDFS.findPath();


    return 0;
}
