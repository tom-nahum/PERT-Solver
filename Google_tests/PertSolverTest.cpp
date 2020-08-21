/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include "gtest/gtest.h"
#include "PertProblem.h"
#include <algorithm>
#include "Parser.h"

// -------------------------- const definitions -------------------------

// ------------------------------ functions -----------------------------

void helperTest(const std::string &activitiesStr, const std::string &preActStr,
                const std::string &timesStr, const std::string &expectedES, const std::string &expectedEF)
{
    int numOfActivities;
    ASSERT_FALSE(Parser::parseActivityNum(activitiesStr, numOfActivities));
    int *preActivities = new int[numOfActivities * numOfActivities];
    std::fill(preActivities, preActivities + numOfActivities * numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parsePreAct(numOfActivities, preActivities, preActStr));
    int *times = new int[numOfActivities];
    std::fill(times, times + numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parseTimes(numOfActivities, times, timesStr));
    PertProblem p = PertProblem(numOfActivities, preActivities, times);
    p.calcESEF();
    std::string ES, EF;
    p.printESEF(ES, EF);
    p.printDataTable();
    ASSERT_EQ(ES, expectedES);
    ASSERT_EQ(EF, expectedEF);
    delete[] preActivities;
    delete[] times;
}

TEST(PertSolverTestSuite, PERT1)
{
    std::string activitiesStr = "9";
    std::string preActStr = "-;-;-;A;A,B,C;A,B,C;C;D,E;D,E,F,G";
    std::string timesStr = "5,3,2,7,5,6,2,4,7";
    std::string expectedES = "0 0 0 5 5 5 2 12 12 ";
    std::string expectedEF = "5 3 2 12 10 11 4 16 19 ";
    helperTest(activitiesStr, preActStr, timesStr, expectedES, expectedEF);
}

TEST(PertSolverTestSuite, PERT3)
{
    std::string activitiesStr = "10";
    std::string preActStr = "-;-;-;-;A;A,B;B,C;C;C,D;E,F";
    std::string timesStr = "5,2,3,7,9,2,4,3,8,4";
    std::string expectedES = "0 0 0 0 5 5 3 3 7 14 ";
    std::string expectedEF = "5 2 3 7 14 7 7 6 15 18 ";
    helperTest(activitiesStr, preActStr, timesStr, expectedES, expectedEF);
}
