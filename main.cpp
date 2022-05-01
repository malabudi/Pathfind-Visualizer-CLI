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
void displayAlgoMenu();
void askMapDimensions(int& rowSize, int& colSize);
void createMap(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap);
void validateMenuChoice(std::string& choice, std::string choiceOne, std::string choiceTwo, std::string choiceThree);
void validateMapDimensions(int& rowSize, int& colSize);
void validateChosenPosition(int& xPos, int& yPos, const std::vector< std::vector<char> >& customMap);
void validateObstacleChoice(std::string& choice);
void askStartGoalPositions(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap);


int main()
{
    std::vector< std::vector<char> > userMap;

    std::pair<int, int> start;
    std::pair<int, int> goal;
    std::string menuChoice;
    DepthFirstSearch objPathDFS;

    std::cout << "Welcome to the Pathfinding Visualizer\n" << std::endl;

    while (menuChoice.compare("quit") != 0)
    {
        displayMainMenu();
        std::getline(std::cin, menuChoice);
        std::transform(menuChoice.begin(), menuChoice.end(), menuChoice.begin(), ::tolower); // transforms the string to all lowercase
        trimWhiteSpace(menuChoice);
        validateMenuChoice(menuChoice, "pick", "create", "quit");

        // Picking a preset map
        if (menuChoice.compare("pick") == 0)
        {
            displayMapMenu();
            std::getline(std::cin, menuChoice);
            std::transform(menuChoice.begin(), menuChoice.end(), menuChoice.begin(), ::tolower);
            trimWhiteSpace(menuChoice);
            validateMenuChoice(menuChoice, "small", "medium", "large");

            if (menuChoice.compare("small") == 0)
            {
                userMap  = {
                    {'S', '*', ' ', ' ', 'G'},
                    {' ', '*', ' ', ' ', ' '},
                    {' ', ' ', ' ', '*', ' '},
                    {'*', ' ', '*', ' ', ' '},
                    {'*', ' ', '*', ' ', ' '}
                };

                start = {0, 0};
                goal = {0, 4};
            }
        }
        else if (menuChoice.compare("create") == 0)
        {
            createMap(start, goal, userMap);
        }


        if (menuChoice.compare("quit") != 0)
        {
            displayAlgoMenu();
            std::getline(std::cin, menuChoice);
            std::transform(menuChoice.begin(), menuChoice.end(), menuChoice.begin(), ::tolower);
            trimWhiteSpace(menuChoice);
            validateMenuChoice(menuChoice, "dfs", "bfs", "astar");

            if (menuChoice.compare("dfs") == 0)
            {
                objPathDFS.setStart(start);
                objPathDFS.setGoal(goal);
                objPathDFS.setBoardMap(userMap);
                std::vector< std::pair<int, int> > path = objPathDFS.findPath();
            }
            else if (menuChoice.compare("bfs") == 0)
            {

            }
            else if (menuChoice.compare("astar") == 0)
            {

            }
        }

    }

    return 0;
}

// Map creation
void askMapDimensions(int& rowSize, int& colSize)
{
    std::cout << "\nRule for creating map:" << std::endl;
    std::cout << "Largest size allowed is 25x25, minimum size is 5x5 for any map you create" << std::endl;

    std::cout << "How many rows would you like to have for your map: ";
    std::cin >> rowSize;

    std::cout << "How many columns would you like to have for your map: ";
    std::cin >> colSize;

    validateMapDimensions(rowSize, colSize);
}

void askStartGoalPositions(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap)
{
    int startX, startY, goalX, goalY;

    std::cout << "Please enter the x value for the starting position \"S\" on the map: " << std::endl;
    std::cin >> startX;
    std::cout << "Please enter the y value for the starting position \"S\" on the map: " << std::endl;
    std::cin >> startY;

    validateChosenPosition(startX, startY, customMap);

    start.first = startY - 1;
    start.second = startX - 1;
    customMap[startY - 1][startX - 1] = 'S';
    PathFinder::displayMap(customMap);


    std::cout << "Please enter the x value for the goal position \"G\" on the map: " << std::endl;
    std::cin >> goalX;
    std::cout << "Please enter the y value for the goal position \"G\" on the map: " << std::endl;
    std::cin >> goalY;

    validateChosenPosition(goalX, goalY, customMap);

    goal.first = goalY - 1;
    goal.second = goalX - 1;
    customMap[goalY - 1][goalX - 1] = 'G';
    PathFinder::displayMap(customMap);
}

void askObstacles(std::vector< std::vector<char> >& customMap)
{
    // String instead of char is used in case the user enters more than one char, the input will not overflow into buffer
    std::string choice;
    int obstacleX, obstacleY;
    std::cout << "Would you like to add a obstacle? (Y or N)" << std::endl;
    std::getline(std::cin, choice);

    validateObstacleChoice(choice);

    while (choice.compare("Y") == 0)
    {
        std::cout << "Please enter the x value for where you want the obstacle \"*\" on the map: " << std::endl;
        std::cin >> obstacleX;
        std::cout << "Please enter the y value for where you want the obstacle \"*\" on the map: " << std::endl;
        std::cin >> obstacleY;

        validateChosenPosition(obstacleX, obstacleY, customMap);

        customMap[obstacleY - 1][obstacleX - 1] = '*';
        PathFinder::displayMap(customMap);

        std::cin.ignore(1000, '\n');
        std::cout << "Would you like to add another obstacle? (Y or N)" << std::endl;
        std::getline(std::cin, choice);
        validateObstacleChoice(choice);
    }
}

void createMap(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap)
{
    int rowSize, colSize;
    customMap.clear();

    askMapDimensions(rowSize, colSize);

    // Begin building the map
    std::vector<char> oneRow(colSize, ' ');

    for (int i = 0; i < rowSize; ++i)
        customMap.push_back(oneRow);

    PathFinder::displayMap(customMap);
    askStartGoalPositions(start, goal, customMap);
    std::cin.ignore(1000, '\n');

    askObstacles(customMap);
}


// Menu
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


void displayAlgoMenu()
{
    std::cout << "What algorithm would you like to use in order to pathfind" << std::endl;
    std::cout << "DFS - Depth first search algorithm which uses a stack" << std::endl;
    std::cout << "BFS - Breadth first search algorithm which uses a queue" << std::endl;
    std::cout << "aStar - A Star or A* which uses a priority queue, this is the MOST efficient" << std::endl;
}


// Input Validation
void validateObstacleChoice(std::string& choice)
{
    trimWhiteSpace(choice);

    if (choice[0] >= 'a' && choice[0] <= 'z')
        choice[0] -= 32;

    while (choice.size() > 1 || (choice[0] != 'Y' && choice[0] != 'N'))
    {
        std::cout << "\nInvalid input, please either type Y or N" << std::endl;
        std::cout << "Would you like to add a obstacle? (Y or N)" << std::endl;
        std::getline(std::cin, choice);

        trimWhiteSpace(choice);

        if (choice[0] >= 'a' && choice[0] <= 'z')
            choice[0] -= 32;
    }
}

void validateChosenPosition(int& xPos, int& yPos, const std::vector< std::vector<char> >& customMap)
{
    int numRows = customMap.size();
    int numCols = customMap[0].size();

    while ((yPos <= 0 || yPos > numRows) || (xPos <= 0 || xPos > numCols) || (customMap[yPos - 1][xPos - 1] != ' '))
    {
        std::cout << "\nThe position you have chosen is either out of bounds or already taken, please try again." << std::endl;
        std::cout << "Please enter the x value for the position on the map: " << std::endl;
        std::cin >> xPos;
        std::cout << "Please enter the y value for the position on the map: " << std::endl;
        std::cin >> yPos;
    }
}

void validateMapDimensions(int& rowSize, int& colSize)
{
    while ((rowSize < 5 || rowSize > 25) || (colSize < 5 || colSize > 25))
    {
        std::cout << "\nPlease make sure that the rows and columns are greater than 5x5 and less than 25x25" << std::endl;

        std::cout << "How many rows would you like to have for your map: ";
        std::cin >> rowSize;

        std::cout << "How many columns would you like to have for your map: ";
        std::cin >> colSize;
    }
}

void validateMenuChoice(std::string& choice, std::string choiceOne, std::string choiceTwo, std::string choiceThree)
{
    while (choice.compare(choiceOne) != 0 && choice.compare(choiceTwo) != 0 && choice.compare(choiceThree) != 0)
    {
        std::cout << "The command you have entered is invalid, please enter either of the following" << std::endl;
        std::cout << choiceOne << std::endl;
        std::cout << choiceTwo << std::endl;
        std::cout << choiceThree << std::endl;

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
