#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <set>

using namespace std;

static const int open = 9;
static const int close = 17;

struct Problem {
    string name;
    string specialty;
    int arrivalHour;
    int severity;
    int duration;

    bool operator< (const Problem& other) const
    {
        if (arrivalHour != other.arrivalHour)
            return  (arrivalHour > other.arrivalHour);
        if (severity != other.severity)
            return (severity < other.severity);

        return (duration > other.duration);
    }
};

struct Doctor {
    string id;
    set<string> specialities;
    int available_time = 0;
    vector<Problem> solvedProblems;
};

int main() {
    ifstream inFile("input2.txt");

    int no_Problems, no_Doctors;
    inFile >> no_Problems;

    priority_queue<Problem> problemsQueue;
    for (int problemIdx = 0; problemIdx < no_Problems; problemIdx++)
    {
        Problem problem;
        inFile >> problem.name >> problem.specialty >> problem.arrivalHour
            >> problem.duration >> problem.severity;
        problemsQueue.push(problem);
    }


    inFile >> no_Doctors;

    map<string, Doctor> doctorsById;
    map<string, set<string>> doctorIdsBySpeciality;
    for (int doctorIdx = 0; doctorIdx < no_Doctors; doctorIdx++)
    {
        Doctor doctor;
        inFile >> doctor.id;

        int numSpecialities;
        inFile >> numSpecialities;


        for (int idx = 0; idx < numSpecialities; idx++)
        {
            std::string speciality;
            inFile >> speciality;
            doctor.specialities.insert(speciality);


            doctorIdsBySpeciality[speciality].insert(doctor.id);
        }

        doctor.available_time = open;

        doctorsById[doctor.id] = doctor;
    }

    while (!problemsQueue.empty())
    {
        Problem currentProblem = problemsQueue.top();
        problemsQueue.pop();

        const auto& doctorsIt = doctorIdsBySpeciality.find(currentProblem.specialty);
        if (doctorsIt == doctorIdsBySpeciality.end())
            continue;

        const set<string>& doctorIdsSet = doctorsIt->second;
        for (const string& doctorId : doctorIdsSet)
        {
            Doctor& doctor = doctorsById[doctorId];

            if (doctor.available_time <= currentProblem.arrivalHour
                && currentProblem.arrivalHour + currentProblem.duration <= close)
            {
                doctor.available_time = currentProblem.arrivalHour + currentProblem.duration;
                doctor.solvedProblems.push_back(currentProblem);
                break;
            }
        }
    }
    for (auto& doctorEntry : doctorsById)
    {
        Doctor& doctor = doctorEntry.second;
        if (doctor.solvedProblems.size() > 0)
        {
            cout << doctor.id << " " << doctor.solvedProblems.size() << " ";
            for (const Problem& problem : doctor.solvedProblems)
                cout << problem.name << " " << problem.arrivalHour << " ";
            cout << endl;
        }
    }
    return 0;
}
