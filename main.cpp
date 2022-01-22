#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctype.h>
using namespace std; 

class Student {
private:
	struct courseInfo { //make array of structs
		string courseName = "";
		string courseGrade;
		int courseCredits = 0;
		double gradeConversion = 0.0;
	};
	string currSemester;
	courseInfo courses[5]; //no one takes 5+ classes right?...right??
	string name;
	int numCourses;
	double GPAverage = 0.0;
	int semesterCreds = 0;
public: 
	void getData();
	void getName();
	void calculateGPA();
	void printData() const;
	void resetStudent();
	
};

void Student::getName() {
	cout << "Enter your name and student ID (optional)...\n";
	getline(cin, name);
	while (!isalpha(name[0])) {
		cout << "Please enter a valid name!\n";
		//cin.ignore();
		getline(cin, name);
	}
}

void Student::resetStudent() {//keeps name
	numCourses = 0;
	GPAverage = 0.0;
	semesterCreds = 0;
	currSemester = "";
	for (int i = 0; i < 5; i++) {
		courses[i].courseName = "";
		courses[i].courseGrade = "";
		courses[i].courseCredits = 0;
	}

}
void Student::getData() {
	string classGrade;
	string classCredits;
	string courseCount;

	cout << "Enter semester...\n";

	getline(cin, currSemester);
	while (!isalpha(currSemester[0])) {
		cout << "Please enter a valid semester! (e.g. Fall 2021, Winter 2020, W21, F22, S23)\n";
		getline(cin, currSemester);

	}
	cout << "How many courses did you take?\n";
	getline(cin, courseCount);
	int val = 0;
	for (int i = 0; i < courseCount.size(); i++) {
		while (!isdigit(courseCount[i]) || (courseCount[i] == '.') || (courseCount[0] == '0') || (courseCount.size() > 1) || (courseCount[i] == '6') || (courseCount[i] == '7') || (courseCount[i] == '8') || (courseCount[i] == '9') ) {
			cout << "Please enter a valid number of courses!\n";
			getline(cin, courseCount);
			val = 1;
			break;
		}
		if (val == 1) {
			i = -1;
			val = 0;
		}
	}
	numCourses = stoi(courseCount);

	
	if (numCourses == 1) {
		cout << endl << numCourses << " course taken in " << currSemester << " semester." << endl;
	}
	else {
		cout << endl << numCourses << " courses taken in " << currSemester << " semester." << endl;
	}

	for (int i = 0; i < numCourses; i++) {
		if (numCourses == 1) {
			cout << "\nEnter the name of the course...\n";
			//cin.ignore();
			getline(cin, courses[i].courseName);
		}
		else {
			if (i == 0) { 
				cout << "\nEnter the name of course #" << i + 1 << endl;
				getline(cin, courses[i].courseName);
			}
			else {
				cout << "\nEnter the name of course #" << i + 1 << endl;
				cin.ignore();
				while (courses[i].courseName == "") {
					getline(cin, courses[i].courseName);
				}
			}
		}
		cout << "\nHow many credits?\n";
		cin >> classCredits;
		int val2 = 0;
		for (int j = 0; j < classCredits.size(); j++) {
			while (!isdigit(classCredits[j]) || (classCredits.size() > 1) || (classCredits[j] == '.')) {
				//cin.ignore(); //come back to this for second input invalid
				cout << "Please enter a valid number of credits!\n";
				cin >> classCredits;
				val2 = 1;
				break;
			}
			if (val2 == 1) {
				j = -1;
				val2 = 0;
			}
		}
		courses[i].courseCredits = stoi(classCredits);
		while ((courses[i].courseCredits < 1) || (courses[i].courseCredits > 4 )) {
			cout << "Please enter a valid number of credits!\n";
			cin >> courses[i].courseCredits;
		}

		cout << "Excellent! What grade did you receive? (e.g. A, B+, C-, D, E)\n";
		cin >> classGrade;
		for (int j = 0; j < classGrade.size(); j++) {
			while (!isalpha(classGrade[0]) || (classGrade[0] > 122) || (classGrade[0] < 65) ) { //checks all upper and lower case bounds
				cin.ignore();
				cout << "Please enter a valid grade!\n";
				cin >> classGrade;
			}
		}
		for (int i = 0; i < classGrade.size(); i++) {
			classGrade[0] = toupper(classGrade[0]);
		}
		courses[i].courseGrade = classGrade;
	}

	calculateGPA();
}

//finds GPA and semester credits
void Student::calculateGPA() {
	double gradeSum = 0.0;

	for (int i = 0; i < numCourses; i++) {
		if ( (courses[i].courseGrade == "A") || (courses[i].courseGrade == "A+") || (courses[i].courseGrade == "a+") || (courses[i].courseGrade == "a")) {
			courses[i].gradeConversion = 4.0;
		}
		else if ((courses[i].courseGrade == "A-") || (courses[i].courseGrade == "a-" )) {
			courses[i].gradeConversion = 3.7;
		}
		else if (courses[i].courseGrade == "B+" || (courses[i].courseGrade == "b+")) {
			courses[i].gradeConversion = 3.3;
		}
		else if ((courses[i].courseGrade == "B") || (courses[i].courseGrade == "b")) {
			courses[i].gradeConversion = 3.0;
		}
		else if ((courses[i].courseGrade == "B-") || (courses[i].courseGrade == "b-")) {
			courses[i].gradeConversion = 2.7;
		}
		else if ((courses[i].courseGrade == "C+") || (courses[i].courseGrade == "c+")) {
			courses[i].gradeConversion = 2.3;
		}
		else if (courses[i].courseGrade == "C" || (courses[i].courseGrade == "c")) {
			courses[i].gradeConversion = 2.0;
		}
		else if ((courses[i].courseGrade == "C-") || (courses[i].courseGrade == "c-")) {
			courses[i].gradeConversion = 1.7;
		}
		else if ((courses[i].courseGrade == "D+") || (courses[i].courseGrade == "d+")) {
			courses[i].gradeConversion = 1.3;
		}
		else if ((courses[i].courseGrade == "D") || (courses[i].courseGrade == "d")) {
			courses[i].gradeConversion = 1.0;
		}
		else {
			courses[i].courseGrade = "E"; //force grade to E if anything else is given
			courses[i].gradeConversion = 0.0;
		}
	}



	//find grade sum
	for (int i = 0; i < numCourses; i++) {
		gradeSum += courses[i].gradeConversion;
	}
	//now to find GPA we will multiply 100 * numCourses
	GPAverage = (gradeSum / numCourses);

	if (GPAverage > 3.4) {
		cout << "\n[INFO] Good job! You did pretty well this semester! Have a nice break! You deserve it.\n";
	}
	else if (GPAverage > 3.0) {
		cout << "\n[INFO] Not bad! There's room for improvement but you did it!\n";
	}
	else {
		cout << "\n[INFO] Come on man! You can do better than this!\n";
	}

	for (int i = 0; i < numCourses; i++) {
		semesterCreds += courses[i].courseCredits;
	}

}

void Student::printData() const { //prints data to console and output file

	//writing data to file
	ofstream studentReport;
	studentReport.open("ReportCard.txt", ios::app);

	cout << endl << endl << endl;
	studentReport << setw(20) << setfill('-') << " " << endl;
	studentReport << name << endl;

	cout << currSemester << endl;
	studentReport << currSemester << endl;
	//just to keep English syntax
	if (numCourses < 2) {
		cout << numCourses << " COURSE" << endl;
		studentReport << numCourses << " COURSE" << endl;
	}
	else {
		cout << numCourses << " COURSES\n";
		studentReport << numCourses << " COURSES\n";
	}
	cout << semesterCreds << " Credits\n";
	studentReport << semesterCreds << " Credits\n";
	for (int i = 0; i < numCourses; i++) {
		cout << courses[i].courseName << " // " << courses[i].courseGrade << " (" << courses[i].courseCredits << " credits)" << endl;
		studentReport << courses[i].courseName << " // " << courses[i].courseGrade << " (" << courses[i].courseCredits << " credits)" << endl;
	}
	if (GPAverage == 4 || GPAverage == 3 || GPAverage == 2 || GPAverage == 1) {
		cout << "Grade Point Average: " << setprecision(2) << GPAverage << ".0" <<  endl;
		studentReport << "Grade Point Average: " << setprecision(2) << GPAverage << ".0" << endl;
	}
	else {
		cout << "Grade Point Average: " << setprecision(2) << GPAverage << endl;
		studentReport << "Grade Point Average: " << setprecision(2) << GPAverage << endl;
	}
	
	studentReport.close(); //closing file
}



int main() {
	cout << ">Report Card Maker v3.1 by Mohamed Al-Omairi\n\n";
	Student mainStudent;
	mainStudent.getName();
	mainStudent.getData();
	mainStudent.printData(); 

	char userInput; 
	cout << "Semester saved and written to ReportCard.txt! Would you like to add more data? (Y/N) \n";
	cin >> userInput; 
	cout << endl << endl;
	while ((userInput == 'Y') || (userInput == 'y')) {
		mainStudent.resetStudent();
		cin.ignore();
		mainStudent.getData();
		mainStudent.printData();
		cout << "Semester saved and written to ReportCard.txt! Would you like to add more data? (Y/N) \n";
		cin >> userInput;
	}
	cout << "Shutting down...make sure to find your file in ReportCardMaker's installation folder!\n";
	system("pause");
	return 0;
	}