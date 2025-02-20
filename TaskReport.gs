function importPendingTasks() {
  var targetSheetId = "1yfMBnMI3GNATu6KuZtirZ8Bk4gPK5ZSBz3s5CdRfWzg"; 
  var sourceSheetName = "Sheet1"; 
  var targetSheetName = "Task Board"; 
  var logSheetName = "Logs"; 

  try {
  
    var spreadsheet = SpreadsheetApp.openById(targetSheetId);

    // Get Sheets
    var sourceSheet = spreadsheet.getSheetByName(sourceSheetName);
    var targetSheet = spreadsheet.getSheetByName(targetSheetName);
    var logSheet = spreadsheet.getSheetByName(logSheetName);

    // Check if Sheets exist
    if (!sourceSheet || !targetSheet || !logSheet) {
      Logger.log("ERROR: One or more required sheets are missing.");
      return;
    }

    // Get Data from Source Sheet
    var data = sourceSheet.getDataRange().getValues();
    var headers = data[0]; // Header row
    var newTasks = [];
    var logEntries = [];

    var taskIndex = headers.indexOf("Task Name");
    var assignedIndex = headers.indexOf("Assigned To");
    var dateTimeIndex = headers.indexOf("Date/Time");
    var statusIndex = headers.indexOf("Status");

    if (taskIndex === -1 || assignedIndex === -1 || dateTimeIndex === -1 || statusIndex === -1) {
      Logger.log("ERROR: One or more columns are missing.");
      return;
    }

    for (var i = 1; i < data.length; i++) {
      var row = data[i];
      if (row[statusIndex] === "Pending") {
        var formattedDateTime = formatDateTime(row[dateTimeIndex]); // Convert date/time correctly
        newTasks.push([row[taskIndex], row[assignedIndex], formattedDateTime.date]); // Task Board Data
        logEntries.push([row[taskIndex], formattedDateTime.time]); // Logs Data
      }
    }

    if (newTasks.length > 0) {
      targetSheet.getRange(targetSheet.getLastRow() + 1, 1, newTasks.length, newTasks[0].length).setValues(newTasks);
    }
    if (logEntries.length > 0) {
      logSheet.getRange(logSheet.getLastRow() + 1, 1, logEntries.length, logEntries[0].length).setValues(logEntries);
    }

  } catch (e) {
    Logger.log("Error: " + e.message);
  }
}

function formatDateTime(dateTimeValue) {
  if (dateTimeValue instanceof Date) {
    var formattedDate = Utilities.formatDate(dateTimeValue, Session.getScriptTimeZone(), "yyyy-MM-dd"); 
    var formattedTime = Utilities.formatDate(dateTimeValue, Session.getScriptTimeZone(), "hh:mm a"); 
    return { date: formattedDate, time: formattedTime };
  }
  return { date: dateTimeValue, time: dateTimeValue }; 
}
