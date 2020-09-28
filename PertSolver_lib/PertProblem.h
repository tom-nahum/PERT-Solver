/**
 * @file PertProblem.h
 * @author  Tom Nahum, https://www.linkedin.com/in/tom-nachum/
 * @contact tom.nachum@gmail.com, +972-54-540-0958
 *
 * @section DESCRIPTION
 * A class representing a PERT Problem. A pert problem consist of activities and data
 * tables for each activity, As detailed below.
 * The main goal of the class is to fill the data tables,
 * according to the algorithm taught in class.
 * As part of the solution there is a critical path
 * and the minimal time to execute the problem.
 */

// ------------------------------ includes ------------------------------
#include <string>
#include <vector>

// -------------------------- const definitions -------------------------
#ifndef PERT_SOLVER_PERTPROBLEM_H
#define PERT_SOLVER_PERTPROBLEM_H
#define EMPTY -2
#define INIT_ACT -1
#define CRITICAL_PATH "Critical Path is: "
#define SHORTEST_PATH "The shortest time to finish the project is: "

// ------------------------------ functions -----------------------------


class PertProblem
{
public:
    /**
     * A constructor for a Pert problem.
     * @param numOfActivities: The number of activities that the problem consist of.
     * @param preActivities: An array that holds the pre activities for each activity.
     * @param times: An array that hold the time it takes to execute each activity.
     */
    explicit PertProblem(int numOfActivities, const int *preActivities, const int *times);

    /**
     * A destructor for the problem.
     */
    ~PertProblem();

    /**
     * A method that solve the problem, according to the algorithm taught in class.
     */
    void solve();

    /**
     * Copy Constructor for pert problem.
     */
    PertProblem(const PertProblem &p);

    /**
     * Operator = for pert problem.
     * @param other: The pert problem at the rhs.
     */
    PertProblem &operator=(const PertProblem &other);

    /**
     * Move constructor & operator = (Rule of 5)
     */
    PertProblem &operator=(PertProblem other) noexcept;

    /**
    * Helper function for move constructor
    */
    friend void swap(PertProblem &lhs, PertProblem &rhs) noexcept;

    /**
     * Operator Overloading for output operator.
     * @param p: the problem to output.
     */
    friend std::ostream &operator<<(std::ostream &os, const PertProblem &p);

    /**
     * Operator Overloading for comparison operator. Mainly build for testing usage.
     * @param p: The pert problem to be compared.
     * @param s: A string representing the desired solution of the problem.
     * @return: True if the solution string match the problem solution string,
     * False otherwise.
     */
    friend bool operator==(const PertProblem &p, const std::string &s);

private:
    /** The number of activities of the problem. **/
    int _actsNum;

    /** The max element in EF arr. This is the shortest time of problem execution. **/
    int _maxEF;

    /** An Array that holds all pre activities of each activity. **/
    int *_preActivities;

    /** An Array that holds all the time of each activity. **/
    int *_times;

    /** An Array that holds the ES (Earliest start) of each activity. **/
    int *_ES;

    /** An Array that holds the EF (Earliest finish) of each activity. **/
    int *_EF;

    /** An Array that holds the LF (Last Finish) of each activity. **/
    int *_LF;

    /** An Array that holds the LS (Last start) of each activity. **/
    int *_LS;

    /** An Array that holds the SL (Slack values) of each activity. **/
    int *_SL;

    /** A string representing the critical path of the problem. **/
    std::string _criticalPath;

    /** A vector that holds all the critical activities of the problem
     * (A critical activity is an activity that it's slack value is 0). **/
    std::vector<std::pair<int, bool>> _criticalActs;

    /** A method that calculate ES & EF according to the algorithm learned in class. **/
    void calcESEF();

    /** A helper function for calculating ES & EF **/
    void findMaxPreEF(int curAct, int &filled);

    /** A method that calculate LF & LS according to the algorithm learned in class. **/
    void calcLFLS();

    /** A helper function for calculating LF & LS **/
    bool canCalcLF(int curAct, std::vector<int> &lsOfPre, bool &found) const;

    /** A method to find the critical path of the problem. **/
    void findCriticalPath();

    /** A helper function to find critical path **/
    int findFirstCriAct(int &numOfActs);

    /** A helper function to find critical path **/
    void addToPath(int& numOfCriActs, int& preAct, std::pair<int, bool> &criAct);

    /** A simple method that find the maximal value in EF array. **/
    int findMaxEF() const;

};


#endif //PERT_SOLVER_PERTPROBLEM_H
