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
#define ACTIVITIES_ERR "ERROR: Activities must be integer, try again"
#define PRE_ACT_ERR "ERROR: an error occurred during typing the pre-activities , try again"
#define TIMES_ERR "ERROR: an error occurred during typing the times, try again"
#define TYPE_TIMES "Please enter the times of each activity, by order.\nFor example, if we have three activities type '18,5,22'."
#define TYPE_PRE_ACT "Please enter the Pre-Activities for each activity.\nThe format is as follow: '1,2;4,7...'.\nIf there are no pre activities, type -."

// ------------------------------ functions -----------------------------

int *enterTimes(int numOfActivities)
{
    int *times = new int[numOfActivities];
    std::fill(times, times + numOfActivities, EMPTY);
    std::cout << TYPE_TIMES << std::endl;
    std::string timesStr;
    std::cin >> timesStr;
    while (Parser::parseTimes(numOfActivities, times, timesStr))
    {
        std::fill(times, times + numOfActivities, EMPTY);
        std::cerr << TIMES_ERR << std::endl;
        std::cin >> timesStr;
    }
    return times;
}

int *enterPreActivities(int numOfActivities)
{
    int *preActivities = new int[numOfActivities * numOfActivities];
    std::fill(preActivities, preActivities + numOfActivities * numOfActivities, EMPTY);
    std::cout << TYPE_PRE_ACT << std::endl;
    std::string preStr;
    std::cin >> preStr;
    while (Parser::parsePreAct(numOfActivities, preActivities, preStr))
    {
        std::fill(preActivities, preActivities + numOfActivities * numOfActivities, EMPTY);
        std::cerr << PRE_ACT_ERR << std::endl;
        std::cin >> preStr;
    }
    return preActivities;
}

int enterActivities()
{
    std::string activitiesStr;
    std::cin >> activitiesStr;
    int numOfActivities = 0;
    while (Parser::parseActivitiesNum(activitiesStr, numOfActivities))
    {
        std::cerr << ACTIVITIES_ERR << std::endl;
        std::cin >> activitiesStr;
    }
    return numOfActivities;
}

void userInterface()
{
    std::cout << WELCOME << std::endl<< INSTRUCTIONS << std::endl;
    int numOfActivities = enterActivities();
    int *preActivities = enterPreActivities(numOfActivities);
    int *times = enterTimes(numOfActivities);
    PertProblem p = PertProblem(numOfActivities, preActivities, times);
    delete[] preActivities;
    delete[] times;
    p.solve();
    p.printData();
}

int main()
{
    userInterface();
    return EXIT_SUCCESS;
}
