#include <iostream>
#include <algorithm>
#include "Pathfinder.h"
#include "DepthFirstSearch.h"

/*
    Pick the size of your map, length & width
    Where would you like the start position to be
    Where do you want your goal
    Where the obstacles should be


Sub:
What algorithms would you like to use to pathfind
---List algorithms
    Draw map and find path

Would you like to reset map and choose different algorithm
1 - yes
2 - no

if 2 then book it END
*/

// Function prototypes
void trimWhiteSpace(std::string& str);
void displayMainMenu();
void displayMapMenu();
void askMapDimensions(int& rowSize, int& colSize);
void createMap(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap);
void validateMenuChoice(std::string& choice, std::string choiceOne, std::string choiceTwo, std::string choiceThree);
void askStartGoalPositions(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap);


int main()
{
    std::vector< std::vector<char> > userMap;

    std::pair<int, int> start;
    std::pair<int, int> goal;
    std::string choice;
    DepthFirstSearch objPathDFS;

    std::cout << "Welcome to the Pathfinding Visualizer\n" << std::endl;

    while (choice.compare("quit") != 0)
    {
        displayMainMenu();
        std::getline(std::cin, choice);
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower); // transforms the string to all lowercase
        trimWhiteSpace(choice);
        validateMenuChoice(choice, "pick", "create", "quit");

        // Picking a preset map
        if (choice.compare("pick") == 0)
        {
            displayMapMenu();
            std::getline(std::cin, choice);
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            validateMenuChoice(choice, "small", "medium", "large");

            if (choice.compare("small") == 0)
            {
                userMap  = {
                    {'S', '*', ' ', ' ', ' '},
                    {' ', '*', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {'*', ' ', '*', ' ', 'G'},
                    {'*', ' ', '*', ' ', ' '}
                };

                start = {0, 0};
                goal = {3, 4};

                // temp - user must eventually pick algorithm

                objPathDFS.setStart(start);
                objPathDFS.setGoal(goal);
                objPathDFS.setBoardMap(userMap);

                std::vector< std::pair<int, int> > path = objPathDFS.findPath();
            }
        }
        else if (choice.compare("create") == 0)
        {
            // Cant create obstacles yet, no validation yet
            createMap(start, goal, userMap);
        }

        // Ask for DFS BFS or A* and validate choice
    }






    return 0;
}


void askMapDimensions(int& rowSize, int& colSize)
{
    std::cout << "How many rows would you like to have for your map: ";
    std::cin >> rowSize;

    std::cout << "How many columns would you like to have for your map: ";
    std::cin >> colSize;
}

void askStartGoalPositions(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap)
{
    int startX, startY, goalX, goalY;

    std::cout << "Please enter the x value for the starting position on the map: ";
    std::cin >> startX;
    std::cout << "Please enter the y value for the starting position on the map: ";
    std::cin >> startY;

    start.first = startX - 1;
    start.second = startY - 1;
    customMap[startX - 1][startY - 1] = 'S';
    PathFinder::displayMap(customMap);


    std::cout << "Please enter the x value for the goal position on the map: ";
    std::cin >> goalX;
    std::cout << "Please enter the y value for the goal position on the map: ";
    std::cin >> goalY;

    goal.first = goalX - 1;
    goal.second = goalY - 1;
    customMap[goalX - 1][goalY - 1] = 'G';
    PathFinder::displayMap(customMap);
}



void createMap(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap)
{
    int rowSize, colSize;
    customMap.clear();

    askMapDimensions(rowSize, colSize);

    std::vector<char> oneRow(colSize, ' ');

    for (int i = 0; i < rowSize; ++i)
        customMap.push_back(oneRow);

    PathFinder::displayMap(customMap);
    askStartGoalPositions(start, goal, customMap);
}


void displayMainMenu()
{
    std::cout << "Please choose from the commands below: " << std::endl;
    std::cout << "pick - pick between a few maps varying in size to pathfind" << std::endl;
    std::cout << "create - create a map of your own by providing the size, and locations of the start goal and obstacles" << std::endl;
    std::cout << "quit - close the program" << std::endl;
}


void displayMapMenu()
{
    std::cout << "What map would you like to pick from below: " << std::endl;
    std::cout << "small - A small 5 x 5 map with some obstacles and fairly easy pathfinding." << std::endl;
}


void validateMenuChoice(std::string& choice, std::string choiceOne, std::string choiceTwo, std::string choiceThree)
{
    while (choice.compare(choiceOne) != 0 && choice.compare(choiceTwo) != 0 && choice.compare(choiceThree) != 0)
    {
        std::cout << "The command you have entered is invalid" << std::endl;
        displayMainMenu();
        std::getline(std::cin, choice);
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        trimWhiteSpace(choice);
    }
}


void trimWhiteSpace(std::string& str)
{
    const std::string whitespace = " \n\t\r\f";
    str.erase(0, str.find_first_not_of(whitespace));
    str.erase(str.find_last_not_of(whitespace) + 1);
}
