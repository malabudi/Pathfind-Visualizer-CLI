#include <iostream>
#include <algorithm>
#include <limits>
#include "Pathfinder.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "AStar.h"
#include <fstream>

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
void validateYesNo(std::string& choice);
void validateInt(int& input);
void askStartGoalPositions(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap);
void askFileCreation(std::string& fileChoice);
void printMapToFile(std::ofstream& file, const std::vector< std::vector<char> >& userMap, const std::string& algorithm);


int main()
{
    std::vector< std::pair<int, int> > path;
    std::vector< std::vector<char> > userMap, finalMap;
    std::pair<int, int> start;
    std::pair<int, int> goal;
    std::string menuChoice, algorithm;
    DepthFirstSearch pathFindDFS;
    BreadthFirstSearch pathFindBFS;
    AStar pathFindAStar;
    std::string fileCreationChoice;

    std::cout << "Welcome to the Pathfinding Visualizer" << std::endl;

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
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', '*', ' '},
                    {' ', ' ', '*', ' ', ' '},
                    {'*', ' ', '*', ' ', ' '}
                };

                start = {0, 0};
                goal = {0, 4};
            }
            else if (menuChoice.compare("medium") == 0)
            {
                userMap  = {
                    {' ', ' ', ' ', ' ', '*', ' ', ' ', '*', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*'},
                    {' ', ' ', '*', ' ', '*', ' ', ' ', '*', ' ', ' '},
                    {'*', 'S', ' ', ' ', '*', ' ', ' ', '*', ' ', ' '},
                    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', '*', ' ', '*', ' ', ' ', ' ', '*', ' '},
                    {' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', 'G'}
                };

                start = {4, 1};
                goal = {9, 9};
            }
            else if (menuChoice.compare("large") == 0)
            {
                userMap  = {
                    {' ', ' ', '*', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', '*', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' '},
                    {'*', ' ', '*', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', ' ', '*', ' ', ' ', ' '},
                    {'*', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '},
                    {' ', ' ', '*', ' ', 'S', ' ', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '},
                    {' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', '*', ' ', ' ', '*', '*', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'*', '*', ' ', '*', ' ', ' ', '*', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', '*', ' ', '*', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', '*', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', ' ', '*', ' '},
                    {' ', '*', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', '*', '*', '*', ' ', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'*', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*'},
                    {' ', ' ', ' ', ' ', ' ', '*', '*', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' ', 'G', ' ', '*'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
                };

                start = {4, 5};
                goal = {21, 22};
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
                pathFindDFS.setStart(start);
                pathFindDFS.setGoal(goal);
                pathFindDFS.setBoardMap(userMap);
                path = pathFindDFS.findPath();

                algorithm = "Algorithm: Depth First Search";
                finalMap = pathFindDFS.getBoardMap();
            }
            else if (menuChoice.compare("bfs") == 0)
            {
                pathFindBFS.setStart(start);
                pathFindBFS.setGoal(goal);
                pathFindBFS.setBoardMap(userMap);
                path = pathFindBFS.findPath();

                algorithm = "Algorithm: Breadth First Search";
                finalMap = pathFindBFS.getBoardMap();
            }
            else if (menuChoice.compare("astar") == 0)
            {
                pathFindAStar.setStart(start);
                pathFindAStar.setGoal(goal);
                pathFindAStar.setBoardMap(userMap);
                path = pathFindAStar.findPath();

                algorithm = "Algorithm: A Star";
                finalMap = pathFindAStar.getBoardMap();
            }

            // -1 means that each class returned path not found
            if (path[0].first == -1)
            {
                std::cout << "\nPath not found!\n" << std::endl;
            }
            else
            {
                std::cout << "\nPath found!" << std::endl;
                std::cout << "The X represents all coordinates or nodes discovered by the AI" << std::endl;
                std::cout << "The O represents the path found and traveled beginning from S towards the goal G while avoiding the obstacles *\n" << std::endl;
            }

            askFileCreation(fileCreationChoice);

            if (fileCreationChoice.compare("Y") == 0)
            {
                std::ofstream mapFile("pathfinded_map.txt");
                printMapToFile(mapFile, finalMap, algorithm);
            }
        }

        start = {};
        goal = {};
        userMap.clear();
        path.clear();
        algorithm.clear();
    }

    std::cout << "\nThank you for using the Pathfinding visualizer!" << std::endl;

    return 0;
}

// Files
void askFileCreation(std::string& fileChoice)
{
    std::cout << "Would you like to save the map to a text file? (Y or N)" << std::endl;
    std::getline(std::cin, fileChoice);

    validateYesNo(fileChoice);
}

void printMapToFile(std::ofstream& file, const std::vector< std::vector<char> >& userMap, const std::string& algorithm)
{
    file.exceptions(std::ofstream::badbit | std::ofstream::failbit);

    try
    {
        file << "The map created after the path has been found if no obstacles blocked the goal:\n";
        file << "X represents cells discovered, O represents the path taken to travel from start to the goal\n";
        file << algorithm << "\n\n";

        for (int i = 0; i < userMap.size(); ++i)
        {
            file << "|";

            for (int j = 0; j < userMap[i].size(); ++j)
            {
                file << userMap[i][j] << "|";
            }

                file << "\n";
        }

        file.close();

        std::cout << "File saved!" << std::endl;
    }
    catch (std::ofstream::failure& exc)
    {
        std::cerr << exc.what() << std::endl;
        file.close();
    }
}


// Map creation
void askMapDimensions(int& rowSize, int& colSize)
{
    std::cout << "\nRule for creating map:" << std::endl;
    std::cout << "Largest size allowed is 25x25, minimum size is 5x5 for any map you create" << std::endl;

    std::cout << "How many rows would you like to have for your map: ";
    std::cin >> rowSize;

    validateInt(rowSize);

    std::cout << "How many columns would you like to have for your map: ";
    std::cin >> colSize;

    validateInt(colSize);
    validateMapDimensions(rowSize, colSize);
}

void askStartGoalPositions(std::pair<int, int>& start, std::pair<int, int>& goal, std::vector< std::vector<char> >& customMap)
{
    int startX, startY, goalX, goalY;

    std::cout << "Please enter the x value for the starting position \"S\" on the map: " << std::endl;
    std::cin >> startX;
    validateInt(startX);
    std::cout << "Please enter the y value for the starting position \"S\" on the map: " << std::endl;
    validateInt(startY);
    std::cin >> startY;

    validateChosenPosition(startX, startY, customMap);

    start.first = startY - 1;
    start.second = startX - 1;
    customMap[startY - 1][startX - 1] = 'S';
    PathFinder::displayMap(customMap);


    std::cout << "Please enter the x value for the goal position \"G\" on the map: " << std::endl;
    validateInt(goalX);
    std::cin >> goalX;
    std::cout << "Please enter the y value for the goal position \"G\" on the map: " << std::endl;
    validateInt(goalY);
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

    validateYesNo(choice);

    while (choice.compare("Y") == 0)
    {
        std::cout << "Please enter the x value for where you want the obstacle \"*\" on the map: " << std::endl;
        std::cin >> obstacleX;
        validateInt(obstacleX);
        std::cout << "Please enter the y value for where you want the obstacle \"*\" on the map: " << std::endl;
        std::cin >> obstacleY;
        validateInt(obstacleY);

        validateChosenPosition(obstacleX, obstacleY, customMap);

        customMap[obstacleY - 1][obstacleX - 1] = '*';
        PathFinder::displayMap(customMap);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Would you like to add another obstacle? (Y or N)" << std::endl;
        std::getline(std::cin, choice);
        validateYesNo(choice);
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    askObstacles(customMap);
}


// Menu
void displayMainMenu()
{
    std::cout << "\nPlease choose from the commands below: " << std::endl;
    std::cout << "pick - pick between a few maps varying in size to pathfind" << std::endl;
    std::cout << "create - create a map of your own by providing the size, and locations of the start goal and obstacles" << std::endl;
    std::cout << "quit - close the program" << std::endl;
}


void displayMapMenu()
{
    std::cout << "\nWhat map would you like to pick from below: " << std::endl;
    std::cout << "small - A small 5 x 5 map with few obstacles and fairly easy pathfinding." << std::endl;
    std::cout << "medium - A medium 10 x 10 map with moderate obstacles and decently difficult pathfinding." << std::endl;
    std::cout << "large - A large 25 x 25 map with many obstacles and difficult pathfinding (will be the slowest)." << std::endl;
}


void displayAlgoMenu()
{
    std::cout << "\nWhat algorithm would you like to use in order to pathfind" << std::endl;
    std::cout << "DFS - Depth first search algorithm which uses a stack" << std::endl;
    std::cout << "BFS - Breadth first search algorithm which uses a queue" << std::endl;
    std::cout << "aStar - A Star or A* which uses a priority queue, this is the most quickest and efficient of the three" << std::endl;
}

// Input Validation
void validateInt(int& input)
{
    while (std::cin.fail())
    {
        std::cin.clear(); // clear fail bit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid Input, Please enter an integer" << std::endl;
        std::cin >> input;
      }
}

void validateYesNo(std::string& choice)
{
    trimWhiteSpace(choice);

    if (choice[0] >= 'a' && choice[0] <= 'z')
        choice[0] -= 32;

    while (choice.size() > 1 || (choice[0] != 'Y' && choice[0] != 'N'))
    {
        std::cout << "\nInvalid input, please either type Y or N" << std::endl;
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
