/**
 * @file PertSolverTest.cpp
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 * Tests for Pert Solver program. The tests includes tests for parser,
 * and afterwords tests for the whole program. All program tests uses pertTester function,
 * which simulates Main.cpp. An explanation for each test can be found in
 * PertSolver\Google_tests\Tests_Info directory.
 */

// ------------------------------ includes ------------------------------
#include "gtest/gtest.h"
#include "PertProblem.h"
#include <algorithm>
#include "Parser.h"

// ------------------------------ functions -----------------------------

/**
 * Check edge cases of parsing times input. Check that the number of
 * activities matches the number of times the user entered.
 */
TEST(ParserTestSuite, Times1)
{
    int *times = new int[3];
    ASSERT_EQ(Parser::parseTimes(3, times, "1"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parseTimes(3, times, "1,2,3,4"), EXIT_FAILURE);
    delete[] times;
}

/**
 * Check edge cases of parsing times input. Check that the times entered are
 * valid, meaning integers (can be 0).
 */
 TEST(ParserTestSuite, Times2)
{
    int *times = new int[3];
    ASSERT_EQ(Parser::parseTimes(3, times, "1,2,q"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parseTimes(3, times, "1, ,q"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parseTimes(3, times, "1,3kr,4"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parseTimes(3, times, "5,65,9"), EXIT_SUCCESS);
    ASSERT_EQ(Parser::parseTimes(3, times, ""), EXIT_FAILURE);
    delete[] times;
}

/**
 * Check edge cases of parsing pre Activities input. Check that the number of
 * activities matches the number of ; the user entered.
 */
TEST(ParserTestSuite, PreAct1)
{
    int *preActs = new int[2];
    ASSERT_EQ(Parser::parsePreAct(2, preActs, "1;3;5"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parsePreAct(2, preActs, "1"), EXIT_FAILURE);
    delete[] preActs;
}

/**
 * Check edge cases of parsing pre Activities input. The activities should be
 * integers.
 */
TEST(ParserTestSuite, PreAct2)
{
    int *preActs = new int[4];
    ASSERT_EQ(Parser::parsePreAct(4, preActs, "--;1;2;3"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parsePreAct(4, preActs, "-;-;-;1"), EXIT_SUCCESS);
    ASSERT_EQ(Parser::parsePreAct(4, preActs, "-,-,-;-;-;1"), EXIT_FAILURE);
    ASSERT_EQ(Parser::parsePreAct(4, preActs, "1,2;3,4;5,6;7,8"), EXIT_SUCCESS);
    ASSERT_EQ(Parser::parsePreAct(4, preActs, "a,b;3;4;5"), EXIT_FAILURE);
    delete[] preActs;
}

/**
 * Check edge cases of parsing the number of activities input. The activities should be
 * integers, greater than 0.
 */
TEST(ParserTestSuite, ActivitiesNum)
{
    int activitiesNum = 0;
    ASSERT_EQ(Parser::parseActivitiesNum("-2", activitiesNum), EXIT_FAILURE);
    ASSERT_EQ(Parser::parseActivitiesNum("0", activitiesNum), EXIT_FAILURE);
    ASSERT_EQ(Parser::parseActivitiesNum("5", activitiesNum), EXIT_SUCCESS);
    ASSERT_EQ(Parser::parseActivitiesNum("A", activitiesNum), EXIT_FAILURE);
}

/**
 * A helper function for all following tests. This function simulates the run
 * of main function of the program. The function gets the input to the problem
 * (number of activities, pre activities array and times array)
 * and in addition, the expected solution. Then the function uses solve method,
 * and compare the given solution to the actual solution.
 */
void pertTester(const std::string &activitiesNum, const std::string &preAct,
                const std::string &times, const std::string &solution)
{
    //Parse input:
    int numOfActivities = 0;
    ASSERT_FALSE(Parser::parseActivitiesNum(activitiesNum, numOfActivities));
    int *preActivities = new int[numOfActivities * numOfActivities];
    std::fill(preActivities, preActivities + numOfActivities * numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parsePreAct(numOfActivities, preActivities, preAct));
    int *timesArr = new int[numOfActivities];
    std::fill(timesArr, timesArr + numOfActivities, EMPTY);
    ASSERT_FALSE(Parser::parseTimes(numOfActivities, timesArr, times));
    //Test solving algorithm
    PertProblem p = PertProblem(numOfActivities, preActivities, timesArr);
    p.solve();
    ASSERT_TRUE(p == solution);
    delete[] preActivities;
    delete[] timesArr;
}

/**
 * Generates a string representing the solution, given all the data of the solution. Each data
 * of the solution will be separated by |. We use this in operator == of pertProblem.cpp
 */
void solGenerator(const std::string &ES, const std::string &EF, const std::string &LF,
                  const std::string &LS, const std::string &SL, const std::string &path,
                  const std::string &shortestTime, std::string &solution)
{
    solution.append(ES + "|" + EF + "|" + LF + "|" + LS + "|" + SL + "|"
                    + path + "|" + shortestTime);
}

TEST(PertSolverTestSuite, PERT1)
{
    std::string solution;
    solGenerator("0 0 0 5 5 5 2 12 12 ", "5 3 2 12 10 11 4 16 19 ",
                 "5 6 6 12 12 12 12 19 19 ", "0 3 4 5 7 6 10 15 12 ",
                 "0 3 4 0 2 1 8 3 0 ", "1->4->9", "19", solution);
    pertTester("9", "-;-;-;1;1,2,3;1,2,3;3;4,5;4,5,6,7",
               "5,3,2,7,5,6,2,4,7", solution);
}

TEST(PertSolverTestSuite, PERT3)
{
    std::string solution;
    solGenerator("0 0 0 0 5 5 3 3 7 14 ", "5 2 3 7 14 7 7 6 15 18 ",
                 "5 12 10 10 14 14 18 18 18 18 ", "0 10 7 3 5 12 14 15 10 14 ",
                 "0 10 7 3 0 7 11 12 3 0 ", "1->5->10", "18", solution);
    pertTester("10", "-;-;-;-;1;1,2;2,3;3;3,4;5,6", "5,2,3,7,9,2,4,3,8,4", solution);

}

TEST(PertSolverTestSuite, PERT4)
{
    std::string solution;
    solGenerator("0 0 0 0 2 9 12 17 21 21 25 17 25 31 ", "10 3 1 2 9 12 17 21 25 24 31 20 29 38 ",
                 "12 21 34 2 9 12 17 21 25 25 31 31 38 38 ", "2 18 33 0 2 9 12 17 21 22 25 28 34 31 ",
                 "2 18 33 0 0 0 0 0 0 1 0 11 9 0 ", "4->5->6->7->8->9->11->14", "38",
                 solution);
    pertTester("14", "-;-;-;-;4;5;1,6;7;2,8;2,8;9,10;7;3,9;11,12",
               "10,3,1,2,7,3,5,4,4,3,6,3,4,7", solution);
}

TEST(PertSolverTestSuite, PERT6)
{
    std::string solution;
    solGenerator("8 0 0 8 8 0 8 ", "11 8 2 12 16 5 15 ",
                 "16 8 13 16 16 8 16 ", "13 0 11 12 8 3 9 ",
                 "5 0 11 4 0 3 1 ", "2->5", "16", solution);
    pertTester("7", "2,3;-;-;2;2,6;-;2", "3,8,2,4,8,5,7", solution);
}

TEST(PertSolverTestSuite, PERT7)
{
    std::string solution;
    solGenerator("8 0 15 9 9 9 15 0 12 ", "12 9 20 12 15 11 23 8 21 ",
                 "14 9 23 15 15 18 23 9 23 ", "10 0 18 12 9 16 15 1 14 ",
                 "2 0 3 3 0 7 0 1 2 ", "2->5->7", "23", solution);
    pertTester("9", "8;-;4,5,6;2;2,8;2;4,5;-;1", "4,9,5,3,6,2,8,8,9", solution);
}

TEST(PertSolverTestSuite, PERT_COST_1)
{
    std::string solution;
    solGenerator("0 0 0 6 8 10 8 10 ", "6 8 5 10 12 13 15 17 ",
                 "6 10 13 10 17 17 17 17 ", "0 2 8 6 13 14 10 10 ",
                 "0 2 8 0 5 4 2 0 ", "1->4->8", "17", solution);
    pertTester("8", "-;-;-;1;2,3;2,4;2;2,4", "6,8,5,4,4,3,7,7", solution);
}

TEST(PertSolverTestSuite, PERT_COST_3)
{
    std::string solution;
    solGenerator("0 8 14 4 8 4 14 0 14 ", "4 14 19 7 14 10 22 8 23 ",
                 "9 14 23 15 15 18 23 8 23 ", "5 8 18 12 9 12 15 0 14 ",
                 "5 0 4 8 1 8 1 0 0 ", "8->2->9", "23", solution);
    pertTester("9", "-;8;4,5,6;1;1,8;1;4,5;-;2", "4,6,5,3,6,6,8,8,9", solution);
}
