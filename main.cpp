/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include <iostream>
#include <algorithm>
#include <string>
#include "PertProblem.h"
#include "Parser.h"

// -------------------------- const definitions -------------------------
#define WELCOME "Welcome to PERT Solver!"
#define INSTRUCTIONS "Please enter the number of Activities: "
#define INPUT_ERROR "ERROR: input was not valid, try again."
#define TYPE_TIMES "Please enter the times of each activity, by order.\nFor example, if we have three activities type '18,5,22'."
#define TYPE_PRE_ACT "Please enter the Pre-Activities for each activity.\nThe format is as follow: '1,2;4,7...'.\nIf there are no pre activities, type -."

// ------------------------------ functions -----------------------------

int userInterface()
{
    std::cout << WELCOME << std::endl;
    std::cout << INSTRUCTIONS << std::endl;
    std::string activitiesStr;
    std::cin >> activitiesStr;
    int numOfActivities = 0;
    if (Parser::parseActivityNum(activitiesStr, numOfActivities)){
        std::cerr << INPUT_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    int* preActivities = new int[numOfActivities*numOfActivities];
    std::fill(preActivities,preActivities+numOfActivities*numOfActivities,EMPTY);
    std::cout << TYPE_PRE_ACT << std::endl;
    std::string preStr;
    std::cin >> preStr;
    if (Parser::parsePreAct(numOfActivities, preActivities, preStr))
    {
        std::cerr << INPUT_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << TYPE_TIMES << std::endl;
    std::string timesStr;
    std::cin >> timesStr;
    int* times = new int[numOfActivities];
    std::fill(times,times+numOfActivities,EMPTY);
    if (Parser::parseTimes(numOfActivities, times, timesStr))
    {
        std::cerr << INPUT_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    PertProblem p = PertProblem(numOfActivities,preActivities,times);
    delete[] preActivities;
    delete[] times;
    p.printDataTable();
    return EXIT_SUCCESS;
}


int main()
{
    return userInterface();
    //TODO: create a dictionary to allow the user enter letters and not numbers, and then delete the multiple defines in the test cpp
    //TODO: create more informatical messages for each error
    //TODO: for the tests, create in parser class a method that uses all the sub method that parse all the input at onece
    //TODO: allow the user to make mastakes, while typing pre activities and times, by while loop. if he mistakes just init the array
}



