# Pert Solver

PERT - Program Evaluation and Review Technique.
This program solves a given pert problem, using an algorithm learned in course 
"55945 Quantitative Methods in Management", as part of business administration studies.

## Theoretical Knowledge

Pert problems are related to project administrations.
A project composed of activities, times, and priority relations (AKA pre-activities).
The purpose is to find the minimal time it takes to finish the project, considering 
the given priority relations and times of each activity. 

## Description 

The program works as follows:
* The user enters the data of the problem:
  - The number of activities the project has.
  - The time it takes to execute each activity.
  - The priority relations between the activities (meaning that for each activity, 
    the user enters the activities that needs to be done before this activity).

* We parse the input the user entered, and check it's validity.

* We solve the problem, and output the results:
  - A table with all the relevant data for each activity:
    1. ES - Earliest Starting time.
    2. EF - Earliest Finishing time.
    3. LF - Latest Finishing time.
    4. LS - Latests Starting time.
    5. SL - Slack value (A time interval which we can delay the execution of this activity, 
            without harm the minimal finish time of the project).
  - The critical path: consist of all the critical activities (activities which it's SL equals 0), 
    in the order of their execution. The time it takes to execute the path is the minimal time to execute the project.
  - The minimal time it takes to finish the project (which is the maximal value in EF column).
   
