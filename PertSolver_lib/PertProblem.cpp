/**
 * @file
 * @author  Tom Nahum <tom.nachum@gmail.com>
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------
#include "PertProblem.h"
#include <cmath>
#include <iostream>

// -------------------------- const definitions -------------------------


// ------------------------------ functions -----------------------------

void PertProblem::initArrays() const
{
    for (int i = 0; i < numOfActivities; i++)
    {
        times[i] = EMPTY_CELL;
        _ES[i] = EMPTY_CELL;
        _EF[i] = EMPTY_CELL;
        _LF[i] = EMPTY_CELL;
        _LS[i] = EMPTY_CELL;
        _SL[i] = EMPTY_CELL;
        for (int j = 0; j < numOfActivities; j++)
        {
            preActivities[i * numOfActivities + j] = EMPTY_CELL;
        }
    }
}

PertProblem::PertProblem(int numOfActivities)
        : numOfActivities(numOfActivities),
        preActivities(new int[numOfActivities * numOfActivities]),
        times(new int[numOfActivities]), _ES(new int[numOfActivities]), _EF(new int[numOfActivities]),
        _LF(new int[numOfActivities]), _LS(new int[numOfActivities]), _SL(new int[numOfActivities])
{
    initArrays();
}

PertProblem::~PertProblem()
{
    delete[] preActivities;
    delete[] times;
    delete[] _ES;
    delete[] _EF;
    delete[] _LF;
    delete[] _LS;
    delete[] _SL;
}

int PertProblem::getNumOfActivities()
{
    return numOfActivities;
}

void PertProblem::printDataTable()
{
    std::cout << "Act\tPre\t\tT\tES\tEF\tLF\tLS\tSL\n";
    for (int i = 0; i < numOfActivities; i++)
    {
        std::cout << i << "\t";
        for (int j = 0; j < numOfActivities; j++)
        {
            int curPre = preActivities[i * numOfActivities + j];
            if (curPre == INIT_ACTIVITY)
            {
                std::cout << '-';
            }
            else if (curPre != EMPTY_CELL)
            {
                std::cout << curPre;
                if (preActivities[i * numOfActivities + j + 1] != EMPTY_CELL)
                {
                    std::cout << ',';
                }
            }
        }
        std::cout << "\t\t" << times[i] << "\t" << _ES[i] << "\t" <<
                  _EF[i] << "\t" << _LF[i] << "\t" << _LS[i] << "\t" << _SL[i] << std::endl;
    }
}

void PertProblem::printESEF(std::string &ES, std::string &EF) const
{
    for (int i = 0; i < numOfActivities; i++)
    {
        ES.append(std::to_string(_ES[i])).append(" ");
        EF.append(std::to_string(_EF[i])).append(" ");
    }
}

void PertProblem::findMaxPreEF(int i, int &filled)
{
    int max = 0;
    for (int j = i * numOfActivities; j < (i * numOfActivities) + numOfActivities; j++)
    {
        int activity = preActivities[j];
        if (activity != EMPTY_CELL)
        {
            if (_EF[activity] == EMPTY_CELL)
            { //in case that we didn't fiiled a pre activity EF
                return; //we skeep the current activity for now, and back to it in the next iteration.
            }
            max = fmax(max, _EF[activity]);
        }
    }
    _ES[i] = max;
    _EF[i] = _ES[i] + times[i];
    filled++;
}

void PertProblem::calcESEF()
{
    int filled = 0;
    while (filled != numOfActivities)
    {
        for (int i = 0; i < numOfActivities && (_EF[i] == EMPTY_CELL); i++)
        {
            int curActivity = preActivities[i * numOfActivities];
            if (curActivity == INIT_ACTIVITY)
            {
                _ES[i] = 0;
                _EF[i] = times[i];
                filled++;
            }
            else
            {
                findMaxPreEF(i, filled);
            }
        }
    }
}

void PertProblem::solve()
{
    calcESEF();

}