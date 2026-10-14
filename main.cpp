#include <iostream>
#include <limits>
#include <string>
#include <filesystem>

#include "library.h"
#include "filemanager.h"

using namespace std;

void clearScreen() {
    system("cls || clear");
}

void pauseForInput() {
    cout << "\nAppuyez sur Entrée pour continuer...";
    cin.ignore();
    cin.get();
}

void displayMenu() {
    cout << "\n=== SYSTÈME DE GESTION DE BIBLIOTHÈQUE PERSONNELLE ===\n";
    cout << "1.  Ajouter un Livre\n";
    cout << "2.  Supprimer un Livre\n";
    cout << "3.  Rechercher des Livres par Titre\n";
    cout << "4.  Rechercher des Livres par Auteur\n";
    cout << "5.  Afficher Tous les Livres\n";
    cout << "6.  Afficher les Livres Disponibles\n";
    cout << "7.  Ajouter un Utilisateur\n";
    cout << "8.  Afficher Tous les Utilisateurs\n";
    cout << "9.  Emprunter un Livre\n";
    cout << "10. Retourner un Livre\n";
    cout << "11. Statistiques de la Bibliothèque\n";
    cout << "12. Sauvegarder les Données\n";
    cout << "13. Créer une Sauvegarde\n";
    cout << "14. Exporter les données dans un fichier CSV\n";
    cout << "15. Importer les données d'un fichier CSV\n";
    cout << "0.  Quitter\n";
    cout << "======================================================\n";
    cout << "Entrez votre choix : ";
}

string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void printUsage(const char* programName) {
    cerr << "Usage: " << programName << " [--data-dir|-d <répertoire>]\n";
}

int main(int argc, char* argv[]) {
    string dataDir;
    //static int idUser = 0;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--data-dir" || arg == "-d") {
            if (i + 1 >= argc) {
                cerr << "Erreur : " << arg << " nécessite un répertoire.\n";
                printUsage(argv[0]);
                return 1;
            }
            dataDir = argv[++i];
        } else {
            cerr << "Erreur : argument inconnu '" << arg << "'.\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    string booksFile;
    string usersFile;
    string booksCSVFile;
    string usersCSVFile;
    string actionsFile;
    if (!dataDir.empty()) {
        if (!filesystem::is_directory(dataDir)) {
            cerr << "Erreur : le répertoire " << dataDir << " n'existe pas.\n";
            printUsage(argv[0]);
            return 1;
        }
        booksFile = (filesystem::path(dataDir) / "books.txt").string();
        usersFile = (filesystem::path(dataDir) / "users.txt").string();
        booksCSVFile = (filesystem::path(dataDir) / "bookscsv.csv").string();
        usersCSVFile = (filesystem::path(dataDir) / "userscsv.csv").string();
        actionsFile = (filesystem::path(dataDir) / "journal.txt").string();
    }

    Library library;
    FileManager fileManager(booksFile, usersFile, booksCSVFile, usersCSVFile, actionsFile);
    
    // Load existing data
    cout << "Chargement des données de la bibliothèque...\n";
    cout << dataDir << " : chemin des donnees\n";
    cout << booksFile << " : chemin des donnees livres\n";
    cout << usersFile << " : chemin des donnees utilisateurs\n";
    fileManager.loadLibraryData(library);
    
    int choice;
    bool running = true;
    string journalLine;
    
    while (running) {
        displayMenu();
        
        if (!(cin >> choice)) {
            cout << "Saisie invalide. Veuillez entrer un nombre.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pauseForInput();
            continue;
        }
        cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1: { // Add Book
                string title = getInput("Entrez le titre du livre : ");
                string author = getInput("Entrez l'auteur du livre : ");
                string isbn = getInput("Entrez l'ISBN du livre : ");
                
                if (library.findBookByISBN(isbn)) {
                    cout << "Erreur : Un livre avec l'ISBN " << isbn << " existe déjà.\n";
                } else {
                    Book newBook(title, author, isbn);
                    library.addBook(newBook);
                    journalLine = "[AJOUT LIVRE] " + newBook.toFileFormat();
                    fileManager.saveActionToFile(journalLine);
                    cout << "Livre ajouté avec succès ! (Sauvegardez avec no 12)\n";
                }
                pauseForInput();
                break;
            }
            
            case 2: { // Remove Book
                string isbn = getInput("Entrez l'ISBN du livre à supprimer : ");
                string livreSupp = "";
                Book* bookFound = library.findBookByISBN(isbn);
                
                if (bookFound != nullptr) {
                    livreSupp = library.findBookByISBN(isbn)->toFileFormat();
                    
                    if(library.removeBook(isbn)) {
                        cout << "Livre supprimé avec succès ! (Sauvegardez avec no 12)\n";
                    }
                } else {
                    cout << "Livre non trouvé.\n";
                }
                journalLine = "[RETRAIT LIVRE] " + livreSupp;
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            }
            
            case 3: { // Search by Title
                string title = getInput("Entrez le titre à rechercher : ");
                auto results = library.searchBooksByTitle(title);
                
                if (results.empty()) {
                    cout << "Aucun livre trouvé avec ce titre.\n";
                } else {
                    cout << "\n=== RÉSULTATS DE RECHERCHE ===\n";
                    for (size_t i = 0; i < results.size(); ++i) {
                        cout << "\nRésultat " << (i + 1) << " :\n";
                        cout << results[i]->toString() << "\n";
                        cout << "-----------------------------\n";
                    }
                }
                journalLine = "[RECHERCHE TITRE] " + title;
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            }
            
            case 4: { // Search by Author
                string author = getInput("Entrez l'auteur à rechercher : ");
                auto results = library.searchBooksByAuthor(author);
                
                if (results.empty()) {
                    cout << "Aucun livre trouvé de cet auteur.\n";
                } else {
                    cout << "\n=== RÉSULTATS DE RECHERCHE ===\n";
                    for (size_t i = 0; i < results.size(); ++i) {
                        cout << "\nRésultat " << (i + 1) << " :\n";
                        cout << results[i]->toString() << "\n";
                        cout << "-----------------------------\n";
                    }
                }
                journalLine = "[RECHERCHE AUTEUR] " + author;
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            }
            
            case 5: // Display All Books
                library.displayAllBooks();
                pauseForInput();
                journalLine = "[AFFICHAGE LIVRES]";
                fileManager.saveActionToFile(journalLine);
                break;
            
            case 6: // Display Available Books
                library.displayAvailableBooks();
                journalLine = "[AFFICHAGE LIVRES DISPOS]";
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            
            case 7: { // Add User
                string name = getInput("Entrez le nom de l'utilisateur : ");
                string userId;
                // string userId = getInput("Entrez l'ID de l'utilisateur : ");
                int nbUsers = library.getAllUsers().size() + 1;
                if (nbUsers <= 9) {
                    userId = "USR00" + to_string(nbUsers);
                } else if (nbUsers <= 99) {
                    userId = "USR0" + to_string(nbUsers);
                } else {
                    userId = "USR" + to_string(nbUsers);
                }
                
                cout << "ID de l'utilisateur : " << userId << "\n";
                
                if (library.findUserById(userId)) {
                    cout << "Erreur : Un utilisateur avec l'ID " << userId << " existe déjà.\n";
                } else {
                    User newUser(name, userId);
                    library.addUser(newUser);
                    journalLine = "[AJOUT UTILISATEUR] " + newUser.toFileFormat();
                    fileManager.saveActionToFile(journalLine);
                    cout << "Utilisateur ajouté avec succès ! (Sauvegardez avec no 12)\n";
                }
                pauseForInput();
                break;
            }
            
            case 8: // Display All Users
                library.displayAllUsers();
                journalLine = "[AFFICHAGE UTILISATEURS]";
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            
            case 9: { // Check Out Book
                string isbn = getInput("Entrez l'ISBN du livre à emprunter : ");
                string userId = getInput("Entrez l'ID de l'utilisateur : ");
                Book* bookFound = library.findBookByISBN(isbn);
                User* userFound = library.findUserById(userId);
                string livreSupp = "";
                string userSupp =  "";
               
                if (bookFound != nullptr && userFound != nullptr) {
                    cout << "ok1\n";
                    livreSupp = library.findBookByISBN(isbn)->toFileFormat();
                    cout << "ok2\n";
                    userSupp = library.findUserById(userId)->toFileFormat();
                    cout << "ok3\n";

                    if (library.checkOutBook(isbn, userId)) {
                        cout << "ok4\n";
                        int pos = userSupp.find('|'); // source : (1)
                        cout << "ok5\n";
                        journalLine = "[EMPRUNT LIVRE] " + livreSupp + userSupp.substr(0, pos);
                        cout << "ok6\n";
                        fileManager.saveActionToFile(journalLine);
                        cout << "ok7\n";
                        cout << "Livre emprunté avec succès ! (Sauvegardez avec no 12)\n";
                    } else {
                        cout << "Erreur : Impossible d'emprunter le livre. Vérifiez l'ISBN, l'ID utilisateur et la disponibilité du livre.\n";
                    }
                }
                else {
                    cout << "Erreur : Impossible d'emprunter le livre. Vérifiez l'ISBN, l'ID utilisateur et la disponibilité du livre.\n";
                }
                cout << "ok8\n";
                pauseForInput();
                break;
            }
            
            case 10: { // Return Book
                string isbn = getInput("Entrez l'ISBN du livre à retourner : ");
                
                if (library.returnBook(isbn)) {
                journalLine = "[RETOUR LIVRE]";
                fileManager.saveActionToFile(journalLine);
                    cout << "Livre retourné avec succès ! (Sauvegardez avec no 12)\n";
                } else {
                    cout << "Erreur : Impossible de retourner le livre. Vérifiez l'ISBN et que le livre est bien emprunté.\n";
                }
                pauseForInput();
                break;
            }
            
            case 11: { // Library Statistics
                cout << "\n=== STATISTIQUES DE LA BIBLIOTHÈQUE ===\n";
                cout << "Total des Livres : " << library.getTotalBooks() << "\n";
                cout << "Livres Disponibles : " << library.getAvailableBookCount() << "\n";
                cout << "Livres Empruntés : " << library.getCheckedOutBookCount() << "\n";
                cout << "Total des Utilisateurs : " << library.getAllUsers().size() << "\n";
                journalLine = "[IMPRESSION STATS]";
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            }
            
            case 12: { // Save Data
                if (!dataDir.empty()) {
                    if (fileManager.saveLibraryData(library)) {
                    journalLine = "[SAUVEGARDER]";
                    fileManager.saveActionToFile(journalLine);
                        cout << "Données de la bibliothèque sauvegardées avec succès !\n";
                    } else {
                        cout << "Erreur lors de la sauvegarde des données de la bibliothèque.\n";
                    }
                } else {
                    cerr << "Erreur : Les chemins sont vides. Lancez AVEC --datat-dir.\n";
                }
                pauseForInput();
                break;
                
            }
            
            case 13: { // Create Backup
                fileManager.createBackup();
                journalLine = "[CREATION SAUVEGARDE]";
                fileManager.saveActionToFile(journalLine);
                pauseForInput();
                break;
            }

            case 14: { // Save Data to CSV
                if (!dataDir.empty()) {
                    if (fileManager.saveLibraryDataToCSV(library)) {
                        journalLine = "[EXPORT EN CSV]";
                        fileManager.saveActionToFile(journalLine);
                        cout << "Données de la bibliothèque sauvegardées en CSV avec succès !\n";
                    } else {
                        cout << "Erreur lors de la sauvegarde des données de la bibliothèque en CSV.\n";
                    }
                } else {
                    cerr << "Erreur : Les chemins sont vides. Lancez AVEC --datat-dir.\n";
                }
                pauseForInput();
                break;
            }

            case 15: { // Get Data from CSV
                if (fileManager.loadLibraryDataFromCSV(library)) {
                    journalLine = "[IMPORT EN CSV]";
                    fileManager.saveActionToFile(journalLine);
                    cout << "Données du fichier CSV importées avec succès ! Voir avec no 5\n";
                } else {
                    cout << "Erreur lors de l'importation des données en CSV.\n";
                }
                pauseForInput();
                break;
            }
            
            case 0: // Exit
                cout << "Sauvegarde des données avant la fermeture...\n";
                journalLine = "[QUITTER]";
                fileManager.saveActionToFile(journalLine);
                fileManager.saveLibraryData(library);
                cout << "Merci d'avoir utilisé le Système de Gestion de Bibliothèque Personnelle !\n";
                running = false;
                break;
            
            default:
                cout << "Choix invalide. Veuillez réessayer.\n";
                pauseForInput();
                break;
        }
    }
    
    return 0;
}

// ====== SOURCE(S) ====== 
// (1) : https://www.geeksforgeeks.org/cpp/substring-in-cpp/#:~:text=Extract%20Substring%20Before%20a%20Character