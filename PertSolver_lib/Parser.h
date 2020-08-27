/**
 * @file Parser.h
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 * A static class for parsing user's input.
 */

// ------------------------------ includes ------------------------------
#ifndef PERTSOLVER_PARSER_H
#define PERTSOLVER_PARSER_H

#include <iostream>
#include "PertProblem.h"
#include <map>

// ------------------------------ functions -----------------------------

class Parser
{
public:
    /**
     * Gets a string and returns true if the string is not representing integer.
     */
    static bool inputIsNotInt(const std::string &input);

    /**
     * Gets a string and checks if it represents an integer greater than 0.
     * @return 0 if it does, 1 otherwise.
     */
    static int parseActivitiesNum(const std::string &activitiesStr, int &numOfActivities);

    /**
     * Parse the pre activities string, in the format: "1,2;3,4;5,6",
     * in this example, we have 3 activities, each one has 2 previous activities.
     * We put the result in preActivities.
     * @return 0 if the parsing ended with no errors. 1 otherwise.
     */
    static int parsePreAct(int numOfActivities, int *preActivities, const std::string &preStr);

    /**
     * Parse the times string given by the user, and put the result in tines.
     * The format is as follows: "1,2,3,4". meaning that there are 4 activities,
     * the time it takes to perform the first activity is 1, etc.
     * @return 0 if the parsing ended with no errors. 1 otherwise.
     */
    static int parseTimes(int numOfActivities, int *times, const std::string &timesStr);

private:
    /**
     * Prevent creation of Parser instance.
     */
    Parser() = default;
};


#endif //PERTSOLVER_PARSER_H
