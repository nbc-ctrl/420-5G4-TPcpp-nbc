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

public:
    // Constructor
    FileManager(const string& booksFile, const string& usersFile,
                            const string& booksCSVFile, const string& usersCSVFile);
    
    // File operations
    bool saveLibraryData(Library& library);
    bool loadLibraryData(Library& library);
    
    // Individual file operations
    bool saveBooksToFile(Library& library);
    bool saveUsersToFile(Library& library);
    bool loadBooksFromFile(Library& library);
    bool loadUsersFromFile(Library& library);
    
    // Utility methods
    bool fileExists(const string& filename);
    void createBackup();

    // CSV
    bool saveBooksToCSVFile(Library& library);
    bool saveUsersToCSVFile(Library& library);
    bool saveLibraryDataToCSV(Library& library);
};

#endif
