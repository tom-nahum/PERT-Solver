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

// -------------------------- const definitions -------------------------
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8


// ------------------------------ functions -----------------------------


TEST(PertSolverTestSuite, SanityCheck)
{
    int activities = 1;
    PertProblem p = PertProblem(activities);
    p.preActivities[A] = INIT_ACT;
    p.times[A] = 3;
    p.calcESEF();
    ASSERT_EQ(p.getNumOfActivities(), activities);
    std::string ES, EF;
    p.printESEF(ES, EF);
    ASSERT_EQ(ES, "0 ");
    ASSERT_EQ(EF, "3 ");
}


TEST(PertSolverTestSuite, PERT1)
{
    int activities = 9;
    PertProblem p = PertProblem(activities);
    int toPreAct[] = {INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      A, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      A, B, C, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      A, B, C, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      C, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      D, E, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                      D, E, F, G, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    std::copy(toPreAct, toPreAct+activities*activities, p.preActivities);
    int toTimes[] = {5, 3, 2, 7, 5, 6, 2, 4, 7};
    std::copy(toTimes, toTimes + activities, p.times);
    p.calcESEF();
    std::string ES;
    std::string EF;
    p.printESEF(ES, EF);
    ASSERT_EQ(ES, "0 0 0 5 5 5 2 12 12 ");
    ASSERT_EQ(EF, "5 3 2 12 10 11 4 16 19 ");
}

TEST(PertSolverTestSuite, PERT3)
{
    int activities = 10;
    PertProblem p = PertProblem(activities);
    int toPreAct[] = {INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      INIT_ACT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      A, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      A, B, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      B, C, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      C, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      C, D, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,
                      E, F, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY};
    std::copy(toPreAct, toPreAct+activities*activities, p.preActivities);
    int toTimes[] = {5,2,3,7,9,2,4,3,8,4};
    std::copy(toTimes, toTimes + activities, p.times);
    p.calcESEF();
    std::string ES;
    std::string EF;
    p.printESEF(ES, EF);
    ASSERT_EQ(ES, "0 0 0 0 5 5 3 3 7 14 ");
    ASSERT_EQ(EF, "5 2 3 7 14 7 7 6 15 18 ");
    p.printDataTable();
}
