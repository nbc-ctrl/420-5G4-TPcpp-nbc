# NORAH-BILLIE CASTOR 
DA : 202265562

# Fonctionnalités implémentées

- numérotation automatique des ID utilisateurs.
- Import/Export CSV pour faciliter la gestion en lot (en plus du format actuel)
- Journal d’activités

# Question 1 : C++

_Expliquez en détails une fonctionnalité / notion dans le code que ne nous avons pas ou peu vu en cours. Montrez ici l’exemple sorti du code du projet._

Une notion qui n'avait pas vraiment été abordée en cours mais qui se retrouve dans le projet est l'utilisation du stringstream. C'est une classe qui fait que l'on peut traiter une chaîne de caractères comme un flux d'entrées (cin) ou de sorties (cout). Ainsi, dans le cadre de ce programme, on l'utilise pour lire chacune des lignes des données des fichiers CSV et txt. Chaque ligne de ces fichiers passe par un stringstream, ce qui permet au code de considérer ces lignes comme un flux d'entrées. Cela est utile, car cela nous permet d'utiliser _getline_ qui nécessite un flux pour découper la ligne de fichier colonne par colonne selon un délimiteur bien défini. Voici un des endroits que l'on retrouve cette notion dans le code du projet :
```
void Book::fromFileFormat(const string& line){
    stringstream ss(line);
    string elem;
    int cmptr = 0;
    while (getline(ss, elem, '|')) {
        cmptr++;
        switch (cmptr) {
            case 1 : 
                this->title = elem;
                break;
            case 2 :
                this->author = elem;
                    break;
            case 3 :
                this->isbn = elem;
                    break;
            case 4 :
                this->isAvailable = ((elem=="1") ? true : false); 
                    break;
            default :
               if (elem != "") {
                this->borrowerId = elem;
               } 
        }
    }
}
```

# Question 2 : Options de développement possible

_Proposez une solution plus adaptée pour la gestion de bibliothèque et faisant appel éventuellement à une technologie autre que le C++, et expliquez comment vous interfaceriez ça avec le C++. Quelle solution technologique utiliseriez vous ? Pensez au futur de cette bibliothèque à Alexandrie qui pourrait éventuellement contenir des millions de livres._

Pour la gestion de la bibliothèque, tout d'abord, une technologie qui gère automatiquement la mémoire serait plus efficace pour l'écriture, le débogage et la maintenance du système de gestion de la bibliothèque. Voilà pourquoi je pense que ce programme pourrait être écrit en Java ou bien même en PHP pour le développement de ce système en application transactionnelle Web. Par ailleurs, l'enregistrement et la récupération des données à partir de fichiers textes n'est pas idéale pour une bibliothéque qui contiendra éventuellement des millions de livres et potentiellement des milliers d'utilisateurs. L'utilisation d'une base de données serait plus que pertinente. Ainsi les données seraient ajoutées et gérées dans une base de données MySQL par exemple. Et l'application PHP irait chercher les données de cette BD et y enverrait toute modification pour mettre la mettre à jour.

# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de donner chemin vers le repertoire data avec l'application `bibliotheque -d <chemin verrs data>`