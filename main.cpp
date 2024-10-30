#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

struct Problem {
    string name;
    string specialty;
};

struct Doctor {
    string id;
    string specialty;
};

Problem currentProblem;

bool isSpecialist(const Doctor& doc) {
    return doc.specialty == currentProblem.specialty;
}

int main() {
    ifstream inFile("input.txt");

    int numProblems, numDoctors;
    inFile >> numProblems;

    vector<Problem> problems(numProblems);
    for (Problem& c : problems) {
        inFile >> c.name >> c.specialty;
    }

    inFile >> numDoctors;
    vector<Doctor> doctors(numDoctors);
    for (Doctor& d : doctors) {
        inFile >> d.id >> d.specialty;
    }

    for (const Problem& p : problems) {
        currentProblem = p;
        auto docIt = find_if(doctors.begin(), doctors.end(), isSpecialist);

        if (docIt != doctors.end()) {
            cout << p.name << " " << "Acceptat" <<endl;
            doctors.erase(docIt);
        }
        else
        {
            cout << p.name << " " << "Respins" << endl;
        }
        
    }

    inFile.close();

    return 0;
}
