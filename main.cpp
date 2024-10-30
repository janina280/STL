#include <iostream>
#include <vector>
#include <string>
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

int main() {
    ifstream inFile("input.txt");

    int no_Problems, no_Doctors;
    inFile >> no_Problems;

    vector<Problem> problems(no_Problems);
    for (Problem& p : problems) {
        inFile >> p.name >> p.specialty;
    }

    inFile >> no_Doctors;
    vector<Doctor> doctors(no_Doctors);
    for (Doctor& d : doctors) {
        inFile >> d.id >> d.specialty;
    }

    for (const Problem& p : problems) {
        currentProblem = p;
        bool found = false;

        for (size_t i = 0; i < doctors.size(); ++i) {
            if (doctors[i].specialty == currentProblem.specialty) {
                cout << p.name << " " << "Acceptat" << endl;
                doctors.erase(doctors.begin() + i);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << p.name << " " << "Respins" << endl;
        }
    }

    inFile.close();

    return 0;
}
