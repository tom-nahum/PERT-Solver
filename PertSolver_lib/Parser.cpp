/**
 * @file Parser.cpp
 * @author  Tom Nahum, https://www.linkedin.com/in/tom-nachum/
 * @contact tom.nachum@gmail.com, +972-54-540-0958
 *
 * @section DESCRIPTION
 * An implementation of the parser.h file
 */

// ------------------------------ includes ------------------------------
#include <vector>
#include "Parser.h"
#include <boost/algorithm/string.hpp>
#include <map>

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

int Parser::parseActivitiesNum(const std::string &activitiesStr, int &numOfActivities)
{
    if (Parser::inputIsNotInt(activitiesStr))
    {
        return EXIT_FAILURE;
    }
    numOfActivities = std::stoi(activitiesStr);
    if (numOfActivities == 0) //num of activities cannot be 0.
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int Parser::parsePreAct(int numOfActivities, int *preActivities, const std::string &preStr)
{
    std::vector<std::string> preArr;
    boost::split(preArr, preStr, boost::is_any_of(";"));
    if (preArr.size() != numOfActivities)
        //if not enough ';' has entered, meaning that the user didn't entered pre activities for some activities.
    {
        return EXIT_FAILURE;
    }
    for (int curAct = 0; curAct < numOfActivities; curAct++)
    {
        std::string &curSubString = preArr[curAct];
        if (curSubString == "-") //A symbol for an activity with no pre activities.
        {
            preActivities[curAct * numOfActivities] = INIT_ACT;
            continue;
        }
        //parse pre activities for cur activity
        std::vector<std::string> curPreArr;
        boost::split(curPreArr, curSubString, boost::is_any_of(","));
        for (int preIdx = 0; preIdx < curPreArr.size(); preIdx++)
        {
            if (Parser::inputIsNotInt(curPreArr[preIdx]))
            {
                return EXIT_FAILURE;
            }
            int curPre = std::stoi(curPreArr[preIdx]);
            preActivities[curAct * numOfActivities + preIdx] = curPre - 1;
            //In order to make users life easier, the countdown of the activities starts from 1
        }
    }
    return EXIT_SUCCESS;
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
        if (inputIsNotInt(timesArr[i]))
        {
            return EXIT_FAILURE;
        }
        int curTime = std::stoi(timesArr[i]);
        times[i] = curTime;
    }
    return EXIT_SUCCESS;
}
