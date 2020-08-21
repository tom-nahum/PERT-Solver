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
                const std::string &timesStr, const std::string &expectedES,
                const std::string &expectedEF, const std::string &expectedLF,
                const std::string &expectedLS, const std::string &expectedSL)
{
    int numOfActivities = 0;
    ASSERT_FALSE(Parser::parseActivitiesNum(activitiesStr, numOfActivities));
    int *preActivities = new int[numOfActivities * numOfActivities];
    std::fill(preActivities, preActivities + numOfActivities * numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parsePreAct(numOfActivities, preActivities, preActStr));
    int *times = new int[numOfActivities];
    std::fill(times, times + numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parseTimes(numOfActivities, times, timesStr));
    PertProblem p = PertProblem(numOfActivities, preActivities, times);
    p.solve();
    std::string ES, EF, LF, LS, SL;
    p.outputData(ES, EF, LF, LS, SL);
    p.printDataTable();
    ASSERT_EQ(ES, expectedES);
    ASSERT_EQ(EF, expectedEF);
    ASSERT_EQ(LF, expectedLF);
    ASSERT_EQ(LS, expectedLS);
    ASSERT_EQ(SL, expectedSL);
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
    std::string expectedLF = "5 6 6 12 12 12 12 19 19 ";
    std::string expectedLS = "0 3 4 5 7 6 10 15 12 ";
    std::string expectedSL = "0 3 4 0 2 1 8 3 0 ";
    helperTest(activitiesStr, preActStr, timesStr, expectedES, expectedEF, expectedLF, expectedLS, expectedSL);
}

TEST(PertSolverTestSuite, PERT3)
{
    std::string activitiesStr = "10";
    std::string preActStr = "-;-;-;-;A;A,B;B,C;C;C,D;E,F";
    std::string timesStr = "5,2,3,7,9,2,4,3,8,4";
    std::string expectedES = "0 0 0 0 5 5 3 3 7 14 ";
    std::string expectedEF = "5 2 3 7 14 7 7 6 15 18 ";
    std::string expectedLF = "5 12 10 10 14 14 18 18 18 18 ";
    std::string expectedLS = "0 10 7 3 5 12 14 15 10 14 ";
    std::string expectedSL = "0 10 7 3 0 7 11 12 3 0 ";
    helperTest(activitiesStr, preActStr, timesStr, expectedES, expectedEF, expectedLF, expectedLS, expectedSL);
}
