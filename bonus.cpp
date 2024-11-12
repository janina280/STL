#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

struct Problem {
	string name;
	string specialty;
	int duration;
};

struct Doctor {
	string id;
	string specialty;
};

int main() {
	ifstream inFile("input4_bonus.txt");
	int count = 0;
	int hours = 8;
	int no_Problems, no_Doctors;
	inFile >> no_Problems;

	vector<Problem> problems(no_Problems);
	for (Problem& problem : problems) {
		inFile >> problem.name >> problem.specialty >> problem.duration;
	}

	inFile >> no_Doctors;
	vector<Doctor> doctors(no_Doctors);
	for (Doctor& doctor : doctors) {
		inFile >> doctor.id >> doctor.specialty;
	}

	for (const Doctor& doctor : doctors)
	{
		vector<string>problem_find;
		hours = 8;
		count = 0;

		auto problem_it = find_if(
			problems.begin(),
			problems.end(),
			[&](const Problem& problem) {
				return doctor.specialty == problem.specialty && hours - problem.duration >= 0;
			});
		while (problem_it != problems.end())
		{
			count++;
			hours = hours - problem_it->duration;
			problem_find.push_back(problem_it->name);
			problems.erase(problem_it);

			problem_it = find_if(
				problems.begin(),
				problems.end(),
				[&](const Problem& problem) {
					return doctor.specialty == problem.specialty && hours - problem.duration >= 0;
				});
		}
		cout << doctor.id << " " << count << " ";
		for (auto problem : problem_find)
		{
			cout << problem << " ";
		}
		cout << '\n';

	}
	inFile.close();

	return 0;
}
