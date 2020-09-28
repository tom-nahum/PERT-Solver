/**
 * @file PertProblem.cpp
 * @author  Tom Nahum, https://www.linkedin.com/in/tom-nachum/
 * @contact tom.nachum@gmail.com, +972-54-540-0958
 *
 * @section DESCRIPTION
 * An implementation of the PertProblem.h file.
 */

// ------------------------------ includes ------------------------------
#include "PertProblem.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

// ------------------------------ functions -----------------------------

PertProblem::PertProblem(int numOfActivities, const int *preActivities, const int *times)
        : _actsNum(numOfActivities), _maxEF(0),
        _preActivities(new int[numOfActivities * numOfActivities]),
        _times(new int[numOfActivities]), _ES(new int[numOfActivities]), _EF(new int[numOfActivities]),
        _LF(new int[numOfActivities]), _LS(new int[numOfActivities]), _SL(new int[numOfActivities]), _criticalPath(),
        _criticalActs()
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

PertProblem &PertProblem::operator=(const PertProblem &other)
{
    if (this == &other)
    {
        return *this;
    }
    _actsNum = other._actsNum;
    _maxEF = other._maxEF;
    _criticalPath = other._criticalPath;
    _criticalActs = other._criticalActs;
    delete[] _preActivities;
    delete[] _times;
    delete[] _ES;
    delete[] _EF;
    delete[] _LF;
    delete[] _LS;
    delete[] _SL;
    _preActivities = new int[_actsNum * _actsNum];
    _times = new int[_actsNum];
    _ES = new int[_actsNum];
    _EF = new int[_actsNum];
    _LF = new int[_actsNum];
    _LS = new int[_actsNum];
    _SL = new int[_actsNum];
    for (int i = 0; i < _actsNum; i++)
    {
        _times[i] = other._times[i];
        _ES[i] = other._ES[i];
        _EF[i] = other._EF[i];
        _LF[i] = other._LF[i];
        _LS[i] = other._LS[i];
        _SL[i] = other._SL[i];
        for (int j = 0; j < _actsNum; j++)
        {
            _preActivities[i * _actsNum + j] = other._preActivities[i * _actsNum + j];
        }
    }
    return *this;
}

PertProblem::PertProblem(const PertProblem &p)
        : PertProblem(p._actsNum, p._preActivities, p._times)
{
    for (int i = 0; i < _actsNum; i++)
    {
        _times[i] = p._times[i];
        _ES[i] = p._ES[i];
        _EF[i] = p._EF[i];
        _LF[i] = p._LF[i];
        _LS[i] = p._LS[i];
        _SL[i] = p._SL[i];
        for (int j = 0; j < _actsNum; j++)
        {
            _preActivities[i * _actsNum + j] = p._preActivities[i * _actsNum + j];
        }
    }
}

std::ostream &operator<<(std::ostream &os, const PertProblem &p)
{
    std::string space = std::string(p._actsNum * 2 - 4, ' ');
    os << "Act\tPre" << space << "T\tES\tEF\tLF\tLS\tSL\n";
    for (int i = 0; i < p._actsNum; i++)
    {
        os << i + 1 << "\t";
        for (int j = 0; j < p._actsNum; j++)
        {
            int curPre = p._preActivities[i * p._actsNum + j];
            if (curPre == INIT_ACT)
            {
                os << '-';
            }
            else if (curPre != EMPTY)
            {
                os << curPre + 1;
                if (p._preActivities[i * p._actsNum + j + 1] != EMPTY)
                {
                    os << ',';
                }
            }
            else
            {
                os << ' ' << ' ';
            }
        }
        os << p._times[i] << "\t" << p._ES[i] << "\t" <<
           p._EF[i] << "\t" << p._LF[i] << "\t" << p._LS[i] << "\t" << p._SL[i] << "\n";
    }
    os << "\n";
    os << CRITICAL_PATH << p._criticalPath << "\n";
    os << SHORTEST_PATH << p._maxEF << "\n";
    os << "\n\n";
    return os;
}

bool operator==(const PertProblem &p, const std::string &s)
{
    //parse given string
    std::string expES, expEF, expLF, expLS, expSL, expPath;
    int expTime = 0;
    std::vector<std::string> tables;
    boost::split(tables, s, boost::is_any_of("|"));
    if (tables.size() != 7)
    {
        return false;
    }
    expES = tables[0];
    expEF = tables[1];
    expLF = tables[2];
    expLS = tables[3];
    expSL = tables[4];
    expPath = tables[5];
    expTime = std::stoi(tables[6]);
    //parse this pert problem
    std::string ES, EF, LF, LS, SL;
    for (int i = 0; i < p._actsNum; i++)
    {
        ES.append(std::to_string(p._ES[i])).append(" ");
        EF.append(std::to_string(p._EF[i])).append(" ");
        LF.append(std::to_string(p._LF[i])).append(" ");
        LS.append(std::to_string(p._LS[i])).append(" ");
        SL.append(std::to_string(p._SL[i])).append(" ");
    }
    //compare all elements
    return !(ES != expES || EF != expEF || LF != expLF || LS != expLS || SL != expSL
             || p._criticalPath != expPath || p._maxEF != expTime);
}

PertProblem& PertProblem::operator=(PertProblem other) noexcept {
    swap(*this,other);
    return *this;
}

void swap(PertProblem& lhs, PertProblem& rhs) noexcept {
    std::swap(lhs._actsNum, rhs._actsNum);
    std::swap(lhs._maxEF, rhs._maxEF);
    std::swap(lhs._preActivities, rhs._preActivities);
    std::swap(lhs._times, rhs._times);
    std::swap(lhs._ES, rhs._ES);
    std::swap(lhs._EF, rhs._EF);
    std::swap(lhs._LF, rhs._LF);
    std::swap(lhs._LS, rhs._LS);
    std::swap(lhs._SL, rhs._SL);
    std::swap(lhs._criticalPath, rhs._criticalPath);
    std::swap(lhs._criticalActs, rhs._criticalActs);
}

void PertProblem::findMaxPreEF(int curAct, int &filled)
{
    int max = 0;
    //for all the pre activities og given activity
    for (int j = curAct * _actsNum; j < (curAct * _actsNum) + _actsNum; j++)
    {
        int pre = _preActivities[j];
        if (pre != EMPTY)
        {
            if (_EF[pre] == EMPTY)
            { //in case that we didn't filled a pre activity EF
                return; //we will skip the current activity for now, and back to it at the next iteration.
            }
            max = (int) fmax(max, _EF[pre]);
        }
    }
    _ES[curAct] = max;
    _EF[curAct] = _ES[curAct] + _times[curAct];
    filled++;
}

void PertProblem::calcESEF()
{
    int filled = 0;
    while (filled != _actsNum)
    {
        for (int curAct = 0; curAct < _actsNum; curAct++)
        {
            if (_EF[curAct] == EMPTY)
            {
                int preAct = _preActivities[curAct * _actsNum];
                if (preAct == INIT_ACT)
                {
                    _ES[curAct] = 0;
                    _EF[curAct] = _times[curAct];
                    filled++;
                }
                else
                {
                    findMaxPreEF(curAct, filled);
                }
            }
        }
    }
}

bool PertProblem::canCalcLF(int curAct, std::vector<int> &lsOfPre, bool &found) const
{
    for (int act = _actsNum - 1; act >= 0; act--)
    {
        if (act != curAct)
        {
            for (int j = 0; j < _actsNum; j++)
            {
                int pre = _preActivities[act * _actsNum + j];
                if (pre == EMPTY)
                {
                    continue;
                }
                else if (pre == curAct)
                {
                    found = true;
                    if (_LS[act] == EMPTY)
                    {
                        return false;
                    }
                    lsOfPre.push_back(_LS[act]);
                }
            }
        }
    }
    return true;
}

void PertProblem::calcLFLS()
{
    int filled = 0;
    int maxEF = findMaxEF();
    while (filled != _actsNum)
    {
        for (int curAct = _actsNum - 1; curAct >= 0; curAct--)
        {
            if (_LS[curAct] == EMPTY)
            {
                //looking for cur activity in pre-activities of other activities:
                bool found = false;
                std::vector<int> lsOfPre;
                if (!canCalcLF(curAct, lsOfPre, found))
                {
                    continue; //to the next activity, later we will fill this one.
                }
                filled++;
                if (!found) //in pre activities of other activity
                {
                    _LF[curAct] = maxEF;
                    _LS[curAct] = maxEF - _times[curAct];
                }
                else
                {
                    _LF[curAct] = *std::min_element(lsOfPre.begin(), lsOfPre.end());
                    _LS[curAct] = _LF[curAct] - _times[curAct];
                }
            }
        }
    }
}

int PertProblem::findMaxEF() const
{
    return *(std::max_element(_EF, _EF + _actsNum));
}

void PertProblem::solve()
{
    calcESEF();
    calcLFLS();
    //calc SL
    for (int i = 0; i < _actsNum; i++)
    {
        _SL[i] = _LF[i] - _EF[i];
        if (_SL[i] == 0)
        {
            _criticalActs.emplace_back(i, false);
        }
    }
    findCriticalPath();
    _maxEF = findMaxEF();
}

int PertProblem::findFirstCriAct(int &numOfActs)
{
    int initAct = 0;
    for (auto &criAct : _criticalActs)
    {
        if (_preActivities[criAct.first * _actsNum] == INIT_ACT)
        {
            initAct = criAct.first;
            criAct.second = true;
            numOfActs--;
        }
    }
    _criticalPath.append(std::to_string(initAct + 1));
    //The user counted the activities from 1.
    return initAct;
}

void PertProblem::addToPath(int& numOfCriActs, int& preAct, std::pair<int, bool> &criAct)
{
    int act = criAct.first;
    //for every j, a pre activity (idx) of the current critical activity
    for (int j = _actsNum * act; (j < _actsNum * act + _actsNum) && j != EMPTY; j++)
    {
        if (preAct == _preActivities[j])
        {
            _criticalPath.append("->");
            _criticalPath.append(std::to_string(act + 1));
            numOfCriActs--;
            preAct = act; //moving on with the path
            criAct.second = true; //we finished with this critical activity
        }
    }
}

void PertProblem::findCriticalPath()
{
    int numOfCriActs = _criticalActs.size();
    int preAct = findFirstCriAct(numOfCriActs);
    while (numOfCriActs != 0)
    {
        for (auto &criAct : _criticalActs)
        {
            if (!criAct.second) //if we didn't add this critical activity to path yet
            {
                addToPath(numOfCriActs, preAct, criAct);
            }
        }
    }
}
