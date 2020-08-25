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

void pertTester(const std::string &activitiesStr, const std::string &preActStr,
                const std::string &timesStr, const std::string &expectedES,
                const std::string &expectedEF, const std::string &expectedLF,
                const std::string &expectedLS, const std::string &expectedSL,
                const std::string& expCriticalPath, int expShortestTime)
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
    std::string ES, EF, LF, LS, SL, criticalPath;
    int shortestTime = 0;
    p.outputData(ES, EF, LF, LS, SL, criticalPath, shortestTime);
    p.printData();
    ASSERT_EQ(ES, expectedES);
    ASSERT_EQ(EF, expectedEF);
    ASSERT_EQ(LF, expectedLF);
    ASSERT_EQ(LS, expectedLS);
    ASSERT_EQ(SL, expectedSL);
    ASSERT_EQ(criticalPath, expCriticalPath);
    ASSERT_EQ(shortestTime, expShortestTime);
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
    std::string expCriticalPath = "A->D->I";
    int shortestTime = 19;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
            expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
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
    std::string expCriticalPath = "A->E->J";
    int shortestTime = 18;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
               expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
}

TEST(PertSolverTestSuite, PERT4)
{
    std::string activitiesStr = "14";
    std::string preActStr = "-;-;-;-;D;E;A,F;G;B,H;B,H;I,J;G;C,I;K,L";
    std::string timesStr = "10,3,1,2,7,3,5,4,4,3,6,3,4,7";
    std::string expectedES = "0 0 0 0 2 9 12 17 21 21 25 17 25 31 ";
    std::string expectedEF = "10 3 1 2 9 12 17 21 25 24 31 20 29 38 ";
    std::string expectedLF = "12 21 34 2 9 12 17 21 25 25 31 31 38 38 ";
    std::string expectedLS = "2 18 33 0 2 9 12 17 21 22 25 28 34 31 ";
    std::string expectedSL = "2 18 33 0 0 0 0 0 0 1 0 11 9 0 ";
    std::string expCriticalPath = "D->E->F->G->H->I->K->N";
    int shortestTime = 38;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
               expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
}

TEST(PertSolverTestSuite, PERT6)
{
    std::string activitiesStr = "7";
    std::string preActStr = "B,C;-;-;B;B,F;-;B";
    std::string timesStr = "3,8,2,4,8,5,7";
    std::string expectedES = "8 0 0 8 8 0 8 ";
    std::string expectedEF = "11 8 2 12 16 5 15 ";
    std::string expectedLF = "16 8 13 16 16 8 16 ";
    std::string expectedLS = "13 0 11 12 8 3 9 ";
    std::string expectedSL = "5 0 11 4 0 3 1 ";
    std::string expCriticalPath = "B->E";
    int shortestTime = 16;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
               expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
}

TEST(PertSolverTestSuite, PERT7)
{
    std::string activitiesStr = "9";
    std::string preActStr = "H;-;D,E,F;B;B,H;B;D,E;-;A";
    std::string timesStr = "4,9,5,3,6,2,8,8,9";
    std::string expectedES = "8 0 15 9 9 9 15 0 12 ";
    std::string expectedEF = "12 9 20 12 15 11 23 8 21 ";
    std::string expectedLF = "14 9 23 15 15 18 23 9 23 ";
    std::string expectedLS = "10 0 18 12 9 16 15 1 14 ";
    std::string expectedSL = "2 0 3 3 0 7 0 1 2 ";
    std::string expCriticalPath = "B->E->G";
    int shortestTime = 23;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
               expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
}

TEST(PertSolverTestSuite, PERT_COST_1)
{
    std::string activitiesStr = "8";
    std::string preActStr = "-;-;-;A;B,C;B,D;B;B,D";
    std::string timesStr = "6,8,5,4,4,3,7,7";
    std::string expectedES = "0 0 0 6 8 10 8 10 ";
    std::string expectedEF = "6 8 5 10 12 13 15 17 ";
    std::string expectedLF = "6 10 13 10 17 17 17 17 ";
    std::string expectedLS = "0 2 8 6 13 14 10 10 ";
    std::string expectedSL = "0 2 8 0 5 4 2 0 ";
    std::string expCriticalPath = "A->D->H";
    int shortestTime = 17;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
               expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
}

TEST(PertSolverTestSuite, PERT_COST_3)
{
    std::string activitiesStr = "9";
    std::string preActStr = "-;H;D,E,F;A;A,H;A;D,E;-;B";
    std::string timesStr = "4,6,5,3,6,6,8,8,9";
    std::string expectedES = "0 8 14 4 8 4 14 0 14 ";
    std::string expectedEF = "4 14 19 7 14 10 22 8 23 ";
    std::string expectedLF = "9 14 23 15 15 18 23 8 23 ";
    std::string expectedLS = "5 8 18 12 9 12 15 0 14 ";
    std::string expectedSL = "5 0 4 8 1 8 1 0 0 ";
    std::string expCriticalPath = "H->B->I";
    int shortestTime = 23;
    pertTester(activitiesStr, preActStr, timesStr, expectedES,
               expectedEF, expectedLF, expectedLS, expectedSL, expCriticalPath, shortestTime);
}