/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#ifndef PERTSOLVER_PARSER_H
#define PERTSOLVER_PARSER_H
#include <iostream>
#include "PertProblem.h"
#include <map>

// -------------------------- const definitions -------------------------


// ------------------------------ functions -----------------------------



class Parser
{
public:
    static bool inputIsNotInt(const std::string &input);
    static int parseTimes(int numOfActivities, int* times, const std::string &timesStr);
    static int parsePreAct(int numOfActivities, int* preActivities,const std::string &preStr);
    static int parseActivitiesNum(const std::string &activitiesStr, int& numOfActivities);
};


#endif //PERTSOLVER_PARSER_H
