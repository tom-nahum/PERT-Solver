/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include <iostream>
#include <vector>
#include "Parser.h"
#include <boost/algorithm/string.hpp>
#include <map>

// -------------------------- const definitions -------------------------


// ------------------------------ functions -----------------------------

bool Parser::inputIsNotInt(const std::string &input)
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

int Parser::parseTimes(int numOfActivities, int *times, const std::string &timesStr)
{
    std::vector<std::string> timesArr;
    boost::split(timesArr, timesStr, boost::is_any_of(","));
    if (timesArr.size() != numOfActivities)
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < timesArr.size(); i++)
    {
        if (Parser::inputIsNotInt(timesArr[i]))
        {
            return EXIT_FAILURE;
        }
        int curTime = std::stoi(timesArr[i]);
        times[i] = curTime;
    }
    return EXIT_SUCCESS;
}

int Parser::parsePreAct(int numOfActivities, int *preActivities, const std::string &preStr)
{
    std::map<std::string, int> map = {{"A", 0},
                                      {"B", 1},
                                      {"C", 2},
                                      {"D", 3},
                                      {"E", 4},
                                      {"F", 5},
                                      {"G", 6},
                                      {"H", 7},
                                      {"I", 8},
                                      {"J", 9},
                                      {"K", 10},
                                      {"L", 11}};
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
            preActivities[i * numOfActivities] = INIT_ACT;
            continue;
        }
        std::vector<std::string> curPreArr;
        boost::split(curPreArr, curSubString, boost::is_any_of(","));
        for (int j = 0; j < curPreArr.size(); j++)
        {
            auto itr = map.find(curPreArr[j]);
            if (itr == map.end())
            {
                return EXIT_FAILURE;
            }
            int curPre = map[curPreArr[j]];
            preActivities[i * numOfActivities + j] = curPre;
        }
    }
    return EXIT_SUCCESS;
}


int Parser::parseActivityNum(const std::string &activitiesStr, int &numOfActivities)
{
    if (Parser::inputIsNotInt(activitiesStr))
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