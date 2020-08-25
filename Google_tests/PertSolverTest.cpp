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
                const std::string &timesStr, const std::string &solution)
{
    //Parse input:
    int numOfActivities = 0;
    ASSERT_FALSE(Parser::parseActivitiesNum(activitiesStr, numOfActivities));
    int *preActivities = new int[numOfActivities * numOfActivities];
    std::fill(preActivities, preActivities + numOfActivities * numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parsePreAct(numOfActivities, preActivities, preActStr));
    int *times = new int[numOfActivities];
    std::fill(times, times + numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parseTimes(numOfActivities, times, timesStr));
    //Test solving algorithm
    PertProblem p = PertProblem(numOfActivities, preActivities, times);
    p.solve();
    std::cout << p;
    ASSERT_TRUE(p == solution);
    delete[] preActivities;
    delete[] times;
}

void solGenerator(const std::string &ES, const std::string &EF, const std::string &LF,
                  const std::string &LS, const std::string &SL, const std::string &path,
                  const std::string &shortestTime, std::string &concat)
{
    concat.append(ES + "|" + EF + "|" + LF + "|" + LS + "|" + SL + "|"
    + path + "|" + shortestTime);
}

TEST(PertSolverTestSuite, PERT1)
{
    std::string activitiesStr = "9";
    std::string preActStr = "-;-;-;A;A,B,C;A,B,C;C;D,E;D,E,F,G";
    std::string timesStr = "5,3,2,7,5,6,2,4,7";
    std::string solution;
    solGenerator("0 0 0 5 5 5 2 12 12 ","5 3 2 12 10 11 4 16 19 ",
            "5 6 6 12 12 12 12 19 19 ","0 3 4 5 7 6 10 15 12 ",
            "0 3 4 0 2 1 8 3 0 ", "A->D->I", "19", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);
}

TEST(PertSolverTestSuite, PERT3)
{
    std::string activitiesStr = "10";
    std::string preActStr = "-;-;-;-;A;A,B;B,C;C;C,D;E,F";
    std::string timesStr = "5,2,3,7,9,2,4,3,8,4";
    std::string solution;
    solGenerator("0 0 0 0 5 5 3 3 7 14 ","5 2 3 7 14 7 7 6 15 18 ",
                 "5 12 10 10 14 14 18 18 18 18 ","0 10 7 3 5 12 14 15 10 14 ",
                 "0 10 7 3 0 7 11 12 3 0 ", "A->E->J", "18", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);

}

TEST(PertSolverTestSuite, PERT4)
{
    std::string activitiesStr = "14";
    std::string preActStr = "-;-;-;-;D;E;A,F;G;B,H;B,H;I,J;G;C,I;K,L";
    std::string timesStr = "10,3,1,2,7,3,5,4,4,3,6,3,4,7";
    std::string solution;
    solGenerator("0 0 0 0 2 9 12 17 21 21 25 17 25 31 ","10 3 1 2 9 12 17 21 25 24 31 20 29 38 ",
                 "12 21 34 2 9 12 17 21 25 25 31 31 38 38 ","2 18 33 0 2 9 12 17 21 22 25 28 34 31 ",
                 "2 18 33 0 0 0 0 0 0 1 0 11 9 0 ", "D->E->F->G->H->I->K->N", "38", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);
}

TEST(PertSolverTestSuite, PERT6)
{
    std::string activitiesStr = "7";
    std::string preActStr = "B,C;-;-;B;B,F;-;B";
    std::string timesStr = "3,8,2,4,8,5,7";
    std::string solution;
    solGenerator("8 0 0 8 8 0 8 ","11 8 2 12 16 5 15 ",
                 "16 8 13 16 16 8 16 ","13 0 11 12 8 3 9 ",
                 "5 0 11 4 0 3 1 ", "B->E", "16", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);
}

TEST(PertSolverTestSuite, PERT7)
{
    std::string activitiesStr = "9";
    std::string preActStr = "H;-;D,E,F;B;B,H;B;D,E;-;A";
    std::string timesStr = "4,9,5,3,6,2,8,8,9";
    std::string solution;
    solGenerator("8 0 15 9 9 9 15 0 12 ","12 9 20 12 15 11 23 8 21 ",
                 "14 9 23 15 15 18 23 9 23 ","10 0 18 12 9 16 15 1 14 ",
                 "2 0 3 3 0 7 0 1 2 ", "B->E->G", "23", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);
}

TEST(PertSolverTestSuite, PERT_COST_1)
{
    std::string activitiesStr = "8";
    std::string preActStr = "-;-;-;A;B,C;B,D;B;B,D";
    std::string timesStr = "6,8,5,4,4,3,7,7";
    std::string solution;
    solGenerator("0 0 0 6 8 10 8 10 ","6 8 5 10 12 13 15 17 ",
                 "6 10 13 10 17 17 17 17 ","0 2 8 6 13 14 10 10 ",
                 "0 2 8 0 5 4 2 0 ", "A->D->H", "17", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);
}

TEST(PertSolverTestSuite, PERT_COST_3)
{
    std::string activitiesStr = "9";
    std::string preActStr = "-;H;D,E,F;A;A,H;A;D,E;-;B";
    std::string timesStr = "4,6,5,3,6,6,8,8,9";
    std::string solution;
    solGenerator("0 8 14 4 8 4 14 0 14 ","4 14 19 7 14 10 22 8 23 ",
                 "9 14 23 15 15 18 23 8 23 ","5 8 18 12 9 12 15 0 14 ",
                 "5 0 4 8 1 8 1 0 0 ", "H->B->I",  "23", solution);
    pertTester(activitiesStr, preActStr, timesStr, solution);
}
