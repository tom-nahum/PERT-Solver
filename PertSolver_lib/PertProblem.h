/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include <string>
#include <vector>

// -------------------------- const definitions -------------------------
#ifndef PERT_SOLVER_PERTPROBLEM_H
#define PERT_SOLVER_PERTPROBLEM_H
#define EMPTY -2
#define INIT_ACT -1

// ------------------------------ functions -----------------------------

class PertProblem
{
public:
    explicit PertProblem(int numOfActivities, const int* preActivities, const int* times);
    ~PertProblem();
    void calcESEF();
    void calcLFLS();
    void solve();
    void printDataTable();
    void outputData(std::string &ES, std::string &EF, std::string &LF, std::string &LS, std::string &SL) const;

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

    bool canCalcLF(int curAct, std::vector<int> &lsOfPre, bool &found);
};


#endif //PERT_SOLVER_PERTPROBLEM_H
