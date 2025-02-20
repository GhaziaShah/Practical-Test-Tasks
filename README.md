1)  Task 1 file has been added.
2)  For Task 2 Google Sheets link is added and the script is added through a notepad file separately.
3)  PDF with question answers and screenshots is added.




* C++ Implementation: Task 1
  The goal of the C++ program is to read a CSV file containing task details, filter out completed and overdue tasks, and generate a summary report of pending tasks. The final report is saved as a text file on the user's desktop.


+ Approach
  
Reading the file
*)The program first attempts to open the task_report.csv file from the working directory.
Initially, I was unaware of how to properly read CSV files without using sstream, so I sought AI assistance to understand character-based parsing. Instead of using stringstream, I manually iterated through each character of a line, splitting values based on commas.

Parsing the Data
*)The CSV file contains five fields: Task ID, Task Name, Status, Due Date, and Assigned To.
To store the parsed values, an array of strings (values[5]) is used, and the program iterates over each character in the line, appending it to the correct field until a comma is encountered.
If a line has fewer than 5 fields, it is skipped as a malformed entry to ensure data integrity.

Date Handling and Comparison
*)Since I had not worked with date parsing in C++ before, I used AI assistance to understand how to manipulate and compare dates using the ctime library.
The function parseDate() converts a date string (YYYY-MM-DD) into a time_t format, which allows for easy comparison.
The function isOverdue() compares a task’s due date with the given report date (2025-02-13) to determine whether it is overdue.

Filtering and Processing Tasks
*)The program iterates through all parsed tasks and filters out those that are marked as "Completed" or are overdue.
The remaining pending tasks are written to a summary report file.

Saving the Summary Report
*)Instead of storing the output file in the program’s directory, I wanted to make sure it gets saved in a universally accessible location.
AI helped in using the getenv("USERPROFILE") function to retrieve the user's home directory on Windows, and the report file is saved to Desktop\\task_summary.txt.

Error Handling
*)The program includes error handling for missing files, incorrect date formats, and malformed CSV entries.
If the task_report.csv file is missing or cannot be opened, an error message is displayed, and the program exits.
If the summary report file cannot be created, the program alerts the user and terminates execution.





* Google Apps Script Implementation: Task 2
+ Approach
The purpose of this script is to automate the extraction of pending tasks from a Google Sheet and transfer them to a task board, while also maintaining a log of processed entries. This was my first time working with Google Apps Script, so I had to take AI assistance for the code, how to access Google Sheets data, and how to manipulate it programmatically.



Connecting to the Google Sheet
*)The script accesses the Google Sheet using SpreadsheetApp.openById(targetSheetId).
Initially, I was unsure about how to properly reference multiple sheets within the same script, so AI helped me learn how to use getSheetByName() to get references to specific sheets (Sheet1, Task Board, and Logs).

Extracting Task Data
*)The script retrieves all data from Sheet1 using getDataRange().getValues(), which returns a 2D array.
It then identifies the index positions of important columns like "Task Name," "Assigned To," "Date/Time," and "Status."
If any of these columns are missing, an error is logged, and the script stops execution.

Filtering Pending Tasks
*)The script iterates over the rows of data and checks if a task's status is "Pending."
If a task is pending, its details are extracted and stored in arrays (newTasks for the task board and logEntries for logging).
Formatting Date and Time

Google Sheets stores date-time values in a special format, so AI helped me understand how to use Utilities.formatDate() to properly extract the date and time separately.
*)The formatDateTime() function converts a timestamp into YYYY-MM-DD for the task board and hh:mm a for the logs.
 
Inserting Data into the Task Board and Log Sheets
*)If pending tasks exist, they are added to the "Task Board" sheet using getRange().setValues().
Similarly, the task name and extracted time are added to the "Logs" sheet to keep a record of processed tasks.

Error Handling
*)If any required sheets are missing, the script logs an error message and stops execution.
The script is enclosed in a try-catch block to handle unexpected errors gracefully.
If no pending tasks are found, the script exits without making unnecessary changes.
