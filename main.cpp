/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include <iostream>
#include <string>
#include "PertProblem.h"
#include <boost/algorithm/string.hpp>
#include <vector>

// -------------------------- const definitions -------------------------
#define WELCOME "Welcome to PERT Solver!"
#define INSTRUCTIONS "Please enter the number of Activities: "
#define INPUT_ERROR "ERROR: input was not valid, try again."
#define TYPE_TIMES "Please enter the times of each activity, by order.\nFor example, if we have three activities type '18,5,22'."
#define TYPE_PRE_ACT "Please enter the Pre-Activities for each activity.\nThe format is as follow: '1,2;4,7...'.\nIf there are no pre activities, type -."

// ------------------------------ functions -----------------------------

bool inputIsNotInt(const std::string &input)
{
    for (const auto &c: input)
    {
        if (!isdigit(c))
        {
            return true;
        }
    }
    return false;
}

int timesParser(int numOfActivities, PertProblem &p, std::string &timesStr)
{
    std::vector<std::string> timesArr;
    boost::split(timesArr, timesStr, boost::is_any_of(","));
    if (timesArr.size() != numOfActivities)
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < timesArr.size(); i++)
    {
        if (inputIsNotInt(timesArr[i]))
        {
            return EXIT_FAILURE;
        }
        int curTime = std::stoi(timesArr[i]);
        p.times[i]= curTime;
    }
    return EXIT_SUCCESS;
}

int preActParser(int numOfActivities, PertProblem &p, std::string &preStr)
{
    std::vector<std::string> preArr;
    boost::split(preArr, preStr, boost::is_any_of(";"));
    if (preArr.size() != numOfActivities)
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < numOfActivities; i++)
    {
        std::string &curSubString = preArr[i];
        if (curSubString == "-")
        {
            p.preActivities[i * numOfActivities]= INIT_ACT;
            continue;
        }
        std::vector<std::string> curPreArr;
        boost::split(curPreArr, curSubString, boost::is_any_of(","));
        for (int j = 0; j < curPreArr.size(); j++)
        {
            if (inputIsNotInt(curPreArr[j]))
            {
                return EXIT_FAILURE;
            }
            int curTime = std::stoi(curPreArr[j]);
            p.preActivities[i * numOfActivities + j]= curTime;
        }
    }
    return EXIT_SUCCESS;
}

int activityParser(const std::string &activitiesStr, int& numOfActivities)
{
    if (inputIsNotInt(activitiesStr))
    {
        return EXIT_FAILURE;
    }
    numOfActivities = std::stoi(activitiesStr);
    if (numOfActivities == 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int userInterface()
{
    std::cout << WELCOME << std::endl;
    std::cout << INSTRUCTIONS << std::endl;
    std::string activitiesStr;
    std::cin >> activitiesStr;
    int numOfActivities = 0;
    if (activityParser(activitiesStr, numOfActivities)){
        std::cerr << INPUT_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    PertProblem p = PertProblem(numOfActivities);
    std::cout << TYPE_PRE_ACT << std::endl;
    std::string preStr;
    std::cin >> preStr;
    if (preActParser(numOfActivities, p, preStr))
    {
        std::cerr << INPUT_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << TYPE_TIMES << std::endl;
    std::string timesStr;
    std::cin >> timesStr;
    if (timesParser(numOfActivities, p, timesStr))
    {
        std::cerr << INPUT_ERROR << std::endl;
        return EXIT_FAILURE;
    }
    p.printDataTable();
    return EXIT_SUCCESS;
}


int main()
{
    return userInterface();
}



