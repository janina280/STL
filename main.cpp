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

int main() {
	ifstream inFile("input2.txt");

	int no_Problems, no_Doctors;
	inFile >> no_Problems;

	vector<Problem> problems(no_Problems);
	for (Problem& problem : problems) {
		inFile >> problem.name >> problem.specialty;
	}

	inFile >> no_Doctors;
	vector<Doctor> doctors(no_Doctors);
	for (Doctor& doctor : doctors) {
		inFile >> doctor.id >> doctor.specialty;
	}

	for (const Doctor& doctor : doctors)
	{
		auto problem_it = find_if(problems.begin(), problems.end(), [&](const Problem& problem) {return doctor.specialty == problem.specialty; });
		if (problem_it != problems.end())
		{
			cout << doctor.id << " " << problem_it->name << " " << '\n';
			problems.erase(problem_it);
		}
	}

	inFile.close();

	return 0;
}
