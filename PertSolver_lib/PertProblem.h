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
    static std::string toABC[];
    explicit PertProblem(int numOfActivities, const int* preActivities, const int* times);
    ~PertProblem();
    void calcESEF();
    void calcLFLS();
    void solve();
    void printData();
    void findCriticalPath();
    void outputData(std::string &ES, std::string &EF, std::string &LF,
            std::string &LS, std::string &SL, std::string &path, int& time) const;
private:
    int _numOfActivities;
    int _maxEF;
    int* _preActivities;
    int* _times;
    int* _ES;
    int* _EF;
    int* _LF;
    int* _LS;
    int* _SL;
    std::string _criticalPath;
    std::vector<std::pair<int, bool>> _criticalActs;
    void findMaxPreEF(int i, int& filled);
    bool canCalcLF(int curAct, std::vector<int> &lsOfPre, bool &found);

    int findMaxEF() const;
};


#endif //PERT_SOLVER_PERTPROBLEM_H
