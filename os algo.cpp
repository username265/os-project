#include<bits/stdc++.h>
using namespace std;

struct node {
	int process;
	int arrival;
	int burst;
	int left;
};

int timeslice = 2;

int main() {
	printf("Enter the number of queries for teacher: ");
	int tq;
	scanf("%d", &tq);
	printf("Enter the number of queries for students: ");
	int sq;
	scanf("%d", &sq);
	vector<node> teacher, student;
	printf("Enter the arrival time and burst time for teacher's queries:\n");
	for(int i=0;i<tq;++i) {
		int at,bt;
		scanf("%d",&at);
		scanf("%d",&bt);
		node temp;
		temp.arrival = at;
		temp.burst = bt;
		temp.left = bt;
		temp.process = i+1;
		teacher.push_back(temp);
	}
	printf("Enter the arrival time and burst time for student's queries:\n");
	for(int i=0;i<sq;++i) {
		int at,bt;
		scanf("%d",&at);
		scanf("%d",&bt);
		node temp;
		temp.arrival = at;
		temp.burst = bt;
		temp.left = bt;
		temp.process = i+1;
		student.push_back(temp);
	}
	//sort teacher and student queue based on arrival time
	for(int i=0;i<teacher.size();++i) {
		for(int j=0;j<teacher.size()-i-1;++j) {
			if(teacher[j].arrival>teacher[j+1].arrival) {
				node temp = teacher[j];
				teacher[j] = teacher[j+1];
				teacher[j+1] = temp;
			}
		}
	}
	for(int i=0;i<student.size();++i) {
		for(int j=0;j<student.size()-i-1;++j) {
			if(student[j].arrival>student[j+1].arrival) {
				node temp = student[j];
				student[j] = student[j+1];
				student[j+1] = temp;
			}
		}
	}
	vector<node> done, running_teacher, running_student;
	int totaltime = 0;
	printf("After scheduling:\n");
	while(done.size()!=(tq+sq)) {
		printf("Time: %d\n", totaltime);
		//adding teacher's to running list
		for(int i=0;i<teacher.size();++i) {
			if(teacher[i].arrival<=totaltime) {
				running_teacher.push_back(teacher[i]);
				teacher.erase(teacher.begin() + i-1);
			}
		}
		//adding student's to student list
		for(int i=0;i<student.size();++i) {
			if(student[i].arrival<=totaltime) {
				running_student.push_back(student[i]);
				student.erase(student.begin() + i-1);
			}
		}
		if(running_teacher.size()!=0) {
			if(running_teacher[0].left<=timeslice) {
				printf("Running teacher %d, left 0\n", running_teacher[0].process);
				totaltime += running_teacher[0].left;
				running_teacher[0].left = 0;
				done.push_back(running_teacher[0]);
				running_teacher.erase(running_teacher.begin());
			}
			else {
				printf("Running teacher %d, left %d\n", running_teacher[0].process, running_teacher[0].left-timeslice);
				totaltime += timeslice;
				running_teacher[0].left -= timeslice;
				for(int i=0;i<teacher.size();++i) {
					if(teacher[i].arrival<=totaltime) {
						running_teacher.push_back(teacher[i]);
						teacher.erase(teacher.begin() + i-1);
					}
				}
				running_teacher.push_back(running_teacher[0]);
				running_teacher.erase(running_teacher.begin());
			}
		}
		else {
			if(running_student[0].left<=timeslice) {
				printf("Running student %d, left 0\n", running_student[0].process);
				totaltime += running_student[0].left;
				running_student[0].left = 0;
				done.push_back(running_student[0]);
				running_student.erase(running_student.begin());
			}
			else {
				totaltime += timeslice;
				printf("Running student %d, left %d\n", running_student[0].process, running_student[0].left-timeslice);
				running_student[0].left -= timeslice;
				for(int i=0;i<student.size();++i) {
					if(student[i].arrival<=totaltime) {
						running_student.push_back(student[i]);
						student.erase(student.begin() + i-1);
					}
				}
				running_student.push_back(running_student[0]);
				running_student.erase(running_student.begin());
			}
		}
	}
	printf("Total time taken is: %d\n", totaltime);
	return 0;
}
