/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include "gtest/gtest.h"
#include "PertProblem.h"

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


TEST(PertSolverTestSuite, ESEF_Test1)
{
    int activities = 1;
    PertProblem p = PertProblem(activities);
    p.preActivities[A] = INIT_ACTIVITY;
    p.times[A] = 3;
    p.calcESEF();
    ASSERT_EQ(p.getNumOfActivities(), activities);
    std::string ES, EF;
    p.printESEF(ES, EF);
    ASSERT_EQ(ES, "0 ");
    ASSERT_EQ(EF, "3 ");
}



TEST(PertSolverTestSuite, ESEF_Test2)
{
    int activities = 9;
    PertProblem p = PertProblem(activities);
    p.preActivities[A] = INIT_ACTIVITY;
    p.preActivities[B * activities] = INIT_ACTIVITY;
    p.preActivities[C * activities] = INIT_ACTIVITY;
    p.preActivities[D * activities] = A;
    p.preActivities[E * activities] = A;
    p.preActivities[E * activities] = B;
    p.preActivities[E * activities] = C;
    p.preActivities[F * activities] = A;
    p.preActivities[F * activities] = B;
    p.preActivities[F * activities] = C;
    p.preActivities[G * activities] = C;
    p.preActivities[H * activities] = D;
    p.preActivities[H * activities] = E;
    p.preActivities[I * activities] = D;
    p.preActivities[I * activities] = E;
    p.preActivities[I * activities] = F;
    p.preActivities[I * activities] = G;
    p.times[A] = 5;
    p.times[B] = 3;
    p.times[C] = 2;
    p.times[D] = 7;
    p.times[E] = 5;
    p.times[F] = 6;
    p.times[G] = 2;
    p.times[H] = 4;
    p.times[I] = 7;

}
