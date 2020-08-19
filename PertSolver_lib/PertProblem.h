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
#define EMPTY_CELL -2
#define INIT_ACTIVITY -1

// ------------------------------ functions -----------------------------

class PertProblem
{
public:
    int numOfActivities;
    int* preActivities;
    int* times;
    explicit PertProblem(int numOfActivities);
    ~PertProblem();
    int getNumOfActivities();
    void calcESEF();
    void solve();
    void printDataTable();
    void printESEF(std::string &ES, std::string &EF) const;

private:
    int* _ES;
    int* _EF;
    int* _LF;
    int* _LS;
    int* _SL;
    void findMaxPreEF(int i, int& filled);
    void initArrays() const;
};


#endif //PERT_SOLVER_PERTPROBLEM_H
