#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

#include "library.h"

using namespace std;

class FileManager {
private:
    string booksFileName;
    string usersFileName;
    string booksCSVFileName;
    string usersCSVFileName;
    string actionsFileName;

public:
    // Constructor
    FileManager(const string& booksFile, const string& usersFile,
                const string& booksCSVFile, const string& usersCSVFile,
                const string& actionsFile);
    
    // File operations
    bool saveLibraryData(Library& library);
    bool loadLibraryData(Library& library);
    
    // Individual file operations
    bool saveBooksToFile(Library& library);
    bool saveUsersToFile(Library& library);
    bool saveActionToFile(string actionLine);
    bool loadBooksFromFile(Library& library);
    bool loadUsersFromFile(Library& library);
    
    // Utility methods
    bool fileExists(const string& filename);
    void createBackup();

    // CSV
    bool saveBooksToCSVFile(Library& library);
    bool saveUsersToCSVFile(Library& library);
    bool saveLibraryDataToCSV(Library& library);
    bool loadLibraryDataFromCSV(Library& library);
    bool loadBooksFromCSVFile(Library& library);
    bool loadUsersFromCSVFile(Library& library);
};

#endif


// ====== SOURCE(S) ====== 
// (1) : https://en.cppreference.com/cpp/chrono/system_clock/now