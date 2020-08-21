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

PertProblem::PertProblem(int numOfActivities, int* preActivities, int* times)
        : _numOfActivities(numOfActivities),
        _preActivities(new int[numOfActivities * numOfActivities]),
        _times(new int[numOfActivities]), _ES(new int[numOfActivities]), _EF(new int[numOfActivities]),
        _LF(new int[numOfActivities]), _LS(new int[numOfActivities]), _SL(new int[numOfActivities])
{
    for (int i = 0; i < numOfActivities; i++)
    {
        _times[i] = times[i];
        _ES[i] = EMPTY;
        _EF[i] = EMPTY;
        _LF[i] = EMPTY;
        _LS[i] = EMPTY;
        _SL[i] = EMPTY;
        for (int j = 0; j < numOfActivities; j++)
        {
            _preActivities[i * numOfActivities + j] = preActivities[i * numOfActivities + j];
        }
    }
}

PertProblem::~PertProblem()
{
    delete[] _preActivities;
    delete[] _times;
    delete[] _ES;
    delete[] _EF;
    delete[] _LF;
    delete[] _LS;
    delete[] _SL;
}

int PertProblem::getNumOfActivities()
{
    return _numOfActivities;
}

void PertProblem::printDataTable()
{
    std::string toABC[] = {"A","B","C","D","E","F","G","H","I","J"};
    std::string space = std::string(_numOfActivities * 2 - 4, ' ');
    std::cout << "Act\tPre"<<space<<"T\tES\tEF\tLF\tLS\tSL\n";
    for (int i = 0; i < _numOfActivities; i++)
    {
        std::cout << toABC[i] << "\t";
        for (int j = 0; j < _numOfActivities; j++)
        {
            int curPre = _preActivities[i * _numOfActivities + j];
            if (curPre == INIT_ACT)
            {
                std::cout << '-';
            }
            else if (curPre != EMPTY)
            {
                std::cout << toABC[curPre];
                if (_preActivities[i * _numOfActivities + j + 1] != EMPTY)
                {
                    std::cout << ',';
                }
            }
            else{
                std::cout<<' '<<' ';
            }
        }
        std::cout << _times[i] << "\t" << _ES[i] << "\t" <<
                  _EF[i] << "\t" << _LF[i] << "\t" << _LS[i] << "\t" << _SL[i] << std::endl;
    }
}

void PertProblem::printESEF(std::string &ES, std::string &EF) const
{
    for (int i = 0; i < _numOfActivities; i++)
    {
        ES.append(std::to_string(_ES[i])).append(" ");
        EF.append(std::to_string(_EF[i])).append(" ");
    }
}

void PertProblem::findMaxPreEF(int i, int &filled)
{
    int max = 0;
    for (int j = i * _numOfActivities; j < (i * _numOfActivities) + _numOfActivities; j++)
    {
        int activity = _preActivities[j];
        if (activity != EMPTY)
        {
            if (_EF[activity] == EMPTY)
            { //in case that we didn't fiiled a pre activity EF
                return; //we skeep the current activity for now, and back to it in the next iteration.
            }
            max = fmax(max, _EF[activity]);
        }
    }
    _ES[i] = max;
    _EF[i] = _ES[i] + _times[i];
    filled++;
}

void PertProblem::calcESEF()
{
    int filled = 0;
    while (filled != _numOfActivities)
    {
        for (int i = 0; i < _numOfActivities && (_EF[i] == EMPTY); i++)
        {
            int curActivity = _preActivities[i * _numOfActivities];
            if (curActivity == INIT_ACT)
            {
                _ES[i] = 0;
                _EF[i] = _times[i];
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