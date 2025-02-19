#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Task {
    int taskID;
    string taskName;
    string status;
    string dueDate;
    string assignedTo;
};

time_t parseDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        cerr << "Error: Invalid date format: " << date << endl;
        return -1;
    }

    struct tm tm = {};
    tm.tm_year = stoi(date.substr(0, 4)) - 1900;  // Year since 1900
    tm.tm_mon  = stoi(date.substr(5, 2)) - 1;    // Month (0-based)
    tm.tm_mday = stoi(date.substr(8, 2));        // Day

    return mktime(&tm);  // Convert to time_t
}

bool isOverdue(const string& dueDate, const string& reportDate) {
    return parseDate(dueDate) < parseDate(reportDate);
}

int main() {
    ifstream file("task_report.csv");
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    string homePath = getenv("USERPROFILE");
	string filePath = homePath + "\\Desktop\\task_summary.txt";  
    
    ofstream outFile(filePath);
    if (!outFile) {
        cout << "Error creating summary file at: " << filePath << endl;
        return 1;
    }


    string line;
    getline(file, line);

    Task tasks[100]; 
    int count = 0;
    string reportDate = "2025-02-13"; 
    while (getline(file, line) && count < 100) {
        int field = 0;
        string values[5]; 
        for (char c : line) {
            if (c == ',') {
                field++; 
            } else {
                values[field] += c; 
            }
        }

        if (field < 4) {
            cout << "Skipping malformed entry: " << line << endl;
            continue;
        }

        tasks[count].taskID = stoi(values[0]);
        tasks[count].taskName = values[1];
        tasks[count].status = values[2];
        tasks[count].dueDate = values[3];
        tasks[count].assignedTo = values[4];

        count++;
    }
    file.close();

    int pendingCount = 0;
    string mostUrgentTask = "None";
    outFile << "Task Summary Report (Report Date: " << reportDate << ")\n";
    outFile << "--------------------------------------\n";

    for (int i = 0; i < count; i++) {
        if (tasks[i].status == "Completed" || isOverdue(tasks[i].dueDate, reportDate)) {
            continue;
        }
        if (mostUrgentTask == "None" || parseDate(tasks[i].dueDate) < parseDate(mostUrgentTask)) {
            mostUrgentTask = tasks[i].dueDate;
        }
        outFile << "Task ID: " << tasks[i].taskID << " | " << tasks[i].taskName
                << " | Due: " << tasks[i].dueDate << " | Assigned To: " << tasks[i].assignedTo << "\n";
        pendingCount++;
    }

    outFile << "\nPending Tasks: " << pendingCount << "\n";
    outFile << "Most Urgent Task: " << mostUrgentTask << "\n";

    outFile.close();
    cout << "Summary saved to task_summary.txt" << endl;

    return 0;
}
 