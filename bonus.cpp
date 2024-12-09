#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

struct Problem {
    string name;
    string specialty;
    int severity;
    int duration;
};

struct Doctor {
    string id;
    string specialty;
    int available_time = 0;
};

int main() {
    ifstream inFile("input.txt");

    int no_Problems, no_Doctors;
    inFile >> no_Problems;
    vector<Problem> problems(no_Problems);
    for (Problem& problem : problems) {
        inFile >> problem.name >> problem.specialty >> problem.duration>> problem.severity;
    }
    inFile >> no_Doctors;

    vector<Doctor> doctors(no_Doctors);
    for (Doctor& doctor : doctors) {
        inFile >> doctor.id >> doctor.specialty;
    }
    sort(problems.begin(), problems.end(), [](const Problem& a, const Problem& b) {
        return a.severity > b.severity;
        });
    vector<vector<string>> assignments(doctors.size()); 
    for (const auto& problem : problems) {
        auto doctor_it = find_if(doctors.begin(), doctors.end(), [&](Doctor& doctor) {
            return doctor.specialty == problem.specialty && doctor.available_time + problem.duration <= 8;
            });

        if (doctor_it != doctors.end()) {
            doctor_it->available_time += problem.duration;
            int doctor_index = doctor_it - doctors.begin();
            assignments[doctor_index].push_back(problem.name);
        }
    }

    for (size_t i = 0; i < doctors.size(); ++i) {
        cout << doctors[i].id << " " << assignments[i].size() << " ";
        for (const auto& problem_name : assignments[i]) {
            cout << problem_name << " ";
        }
        cout << '\n';
    }

    inFile.close();
    return 0;
}
