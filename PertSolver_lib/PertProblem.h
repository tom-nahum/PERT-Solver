/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include <string>

// -------------------------- const definitions -------------------------
#ifndef PERT_SOLVER_PERTPROBLEM_H
#define PERT_SOLVER_PERTPROBLEM_H
#define EMPTY -2
#define INIT_ACT -1

// ------------------------------ functions -----------------------------

class PertProblem
{
public:
    explicit PertProblem(int numOfActivities, int* preActivities, int* times);
    ~PertProblem();
    int getNumOfActivities();
    void calcESEF();
    void solve();
    void printDataTable();
    void printESEF(std::string &ES, std::string &EF) const;

private:
    int _numOfActivities;
    int* _preActivities;
    int* _times;
    int* _ES;
    int* _EF;
    int* _LF;
    int* _LS;
    int* _SL;
    void findMaxPreEF(int i, int& filled);
};


#endif //PERT_SOLVER_PERTPROBLEM_H
