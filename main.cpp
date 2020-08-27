/**
 * @file main.cpp
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 * Responsible for the execution of the program.
 * The program waits for user input, which includes the amount of the activities,
 * the pre activities of each activity and the time it takes to perform each activity.
 * Then, we create a Pert Problem object, and solve the problem.
 * The solution presented in a table as we learned in class.
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
#define TYPE_PRE_ACT "Please enter the Pre-Activities for each activity.\nThe format is as follow: '3;4,7;...'.\nIf there are no pre activities, type -."

// ------------------------------ functions -----------------------------

/**
 * Getting from the user the time it takes to perform each activity.
 * @param numOfActivities: The number of activities for this PERT problem.
 * @return The array containing the times of all activities.
 */
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

/**
 * Getting from the user the pre activities of each activity.
 * @param numOfActivities: The number of activities for this PERT problem.
 * @return The array containing the pre activities.
 */
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

/**
 * Getting from the user the number of activities. It must be an integer.
 * @return int, The number of activities.
 */
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


/**
 * A main function. Runs the whole program.
 * @return 0 always because if the user's input is somewhat wrong,
 * I let him try again by an infinite loop.
 */
int main()
{
    std::cout << WELCOME << std::endl << INSTRUCTIONS << std::endl;
    int numOfActivities = enterActivities();
    int *preActivities = enterPreActivities(numOfActivities);
    int *times = enterTimes(numOfActivities);
    PertProblem p = PertProblem(numOfActivities, preActivities, times);
    delete[] preActivities;
    delete[] times;
    p.solve();
    std::cout << p;
    return EXIT_SUCCESS;
}
