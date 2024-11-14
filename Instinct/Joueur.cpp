#include <iostream>
#include <vector>

#include "Joueur.h"
#include "Animal.h"
#include "CentrerTexte.h"

using namespace std;

int compteurAmour = 0;
bool saisonDesAmours = false;

bool Joueur::getPeriodeDeReproduction() const { return saisonDesAmours; }
void Joueur::setPeriodeDeReproduction(bool pdr) { 
    saisonDesAmours = pdr; 
    compteurAmour = 2; 
    cout << "Tu as demare la saison des amours" << endl;
} //update
void Joueur::incrCompteur() { if (compteurAmour == 0) { return; } compteurAmour -= 1; } //update
void Joueur::resetCompteur() { compteurAmour = 0; } //update

void Joueur::choixDebugMode(bool& debugMode) {
    cout << "Debug mode [y/N] ? > ";
    std::string ans;
    cin >> ans;
    while (cin.fail() || (ans != "y" && ans != "N"))
    {
        cin.clear();
        cin.ignore(9999, '\n');
        system("cls");
        cout << "Debug mode [y/N] ? > ";
        cin >> ans;
    }
    if (ans == "y") {
        debugMode = true;
    }
    else {
        system("cls");
    }
}

int Joueur::afficherInfos(vector<Animal>& animaux) const {
    int choix(0);
    for (int i = 0; i < 9; ++i) {
        centrerTexte(menu[i]);
        cout << endl;
    }
    cout << "\nQue voulez-vous faire durant ce tour ? > ";
    cin >> choix;
    while (cin.fail() || choix < 1 || choix > 9) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Fais un choix correct, entre 1 et 9 > ";
        cin >> choix;
    }
    return choix;
}
void Joueur::afficherInfosSolo(vector<Animal>& animaux) {
    for (unsigned int i = 0; i < animaux.size(); ++i) {
        if (animaux[i].estEnVie() == false) { continue; }
        if (i < 9) { cout << endl << " - " << animaux[i].id << ". " << animaux[i].getNom() << " (" << animaux[i].getEspece() << ")"; }
        else { cout << endl << " - " << animaux[i].id << "." << animaux[i].getNom() << " (" << animaux[i].getEspece() << ")"; }
    }
    cout << endl;
}
int Joueur::WhileCinFail(unsigned int var, vector<Animal>& animaux) {
    while (cin.fail() || var < 1 || var > animaux.size()) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Fais un choix correct, entre 1 et " << animaux.size() << " > ";
        cin >> var;
    }
    return var;
}
char Joueur::choixJoueur(int choix, vector<Animal>& animaux) {
    unsigned int choixSpecifique(0);
    unsigned int choixAnimalUn(0), choixAnimalDeux(0);
    int choixRandom;
    string animauxRandEspece[2]; string animauxRandRegime[2];
    string especeDuBebe; string regimeDuBebe; string nomDuBebe;
    switch (choix) {
    case 1: // Option : 'Nourrir' -> Rajouter des vérifications
        cout << "Tu as choisi de nourrir un animal, quel animal veux-tu nourrir ? ";
        afficherInfosSolo(animaux);
        cout << "Ton choix > ";
        cin >> choixSpecifique;
        if (cin.fail() || choixSpecifique < 1 || choixSpecifique > animaux.size()) { choixSpecifique = WhileCinFail(choixSpecifique, animaux); }
        if (animaux[choixSpecifique - 1].aFaimStatus()) { cout << animaux[choixSpecifique - 1].getNom() << " n'a pas besoin de manger pour l'instant" << endl; break; }
        animaux[choixSpecifique - 1].setFaim(true);
        cout << " - Tu as rempli la pense de " << animaux[choixSpecifique - 1].getNom() << endl;
        break;
    case 2: // Option : 'Tuer' -> Rajouter des vérifications
        cout << "Tu as choisi de tuer un animal, quel animal veux-tu tuer ? ";
        afficherInfosSolo(animaux);
        cout << "Ton choix > ";
        cin >> choixSpecifique;
        if (cin.fail() || choixSpecifique < 1 || choixSpecifique > animaux.size()) { choixSpecifique = WhileCinFail(choixSpecifique, animaux); }
        animaux[choixSpecifique - 1].setVie(false);
        cout << " - Tu as ote la vie de " << animaux[choixSpecifique - 1].getNom() << endl;
        break;
    case 3: // Option : 'Provoquer un conflit' -> Rajouter des vérifications
        cout << "Tu as choisi de provoquer un conflit entre deux animaux, lesquels veux-tu se faire affronter ?";
        afficherInfosSolo(animaux);
        cout << "Ton choix pour le combattant numero 1 > ";
        cin >> choixAnimalUn;
        if (cin.fail() || choixAnimalUn < 1 || choixAnimalUn > animaux.size()) { choixAnimalUn = WhileCinFail(choixAnimalUn, animaux); }
        cout << endl << "Ton choix pour le combattant numero 2 > ";
        cin >> choixAnimalDeux;
        while (cin.fail() || choixAnimalDeux < 1 || choixAnimalDeux > animaux.size() || choixAnimalDeux == choixAnimalUn) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Fais un choix correct, entre 1 et " << animaux.size() << " et different du combattant numero 1 > ";
            cin >> choixAnimalDeux;
        }
        if (animaux[choixAnimalUn - 1].getRegime() == "neutre" || animaux[choixAnimalDeux - 1].getRegime() == "neutre") {
            cout << endl << "Les capybaras ne se battent jamais" << endl;
            break; 
        }
        if (animaux[choixAnimalUn - 1].getRegime() != animaux[choixAnimalDeux - 1].getRegime()) {
            // L'un des combattant est prédateur, l'autre une proie -> le prédateur tue et mange la proie
            if (animaux[choixAnimalUn - 1].getRegime() == "predateur") {
                cout << endl << " - " << animaux[choixAnimalUn - 1].getNom() << " (" << animaux[choixAnimalUn - 1].getEspece() << ") a battu " <<
                    animaux[choixAnimalDeux - 1].getNom() << " (" << animaux[choixAnimalDeux - 1].getEspece() << ")" << endl;
                animaux[choixAnimalDeux - 1].setVie(false);
                break;
            }
            cout << endl << " - " << animaux[choixAnimalDeux - 1].getNom() << " (" << animaux[choixAnimalDeux - 1].getEspece() << ") a battu " <<
                animaux[choixAnimalUn - 1].getNom() << " (" << animaux[choixAnimalUn - 1].getEspece() << ")" << endl;
            animaux[choixAnimalUn - 1].setVie(false);
        }
        else if (animaux[choixAnimalUn - 1].getRegime() == "predateur") { 
            // Les deux combattants sont des prédateurs -> issue aléatoire
            int combattants[2] = { choixAnimalUn, choixAnimalDeux };
            unsigned int choixRandom = rand() % 2;
            animaux[combattants[choixRandom]].setVie(false);
            if (choixRandom == 0) {
                cout << endl << " - " << animaux[choixAnimalDeux - 1].getNom() << " (" << animaux[choixAnimalDeux - 1].getEspece() << ") a battu "
                    << animaux[choixAnimalUn - 1].getNom() << " (" << animaux[choixAnimalUn - 1].getEspece() << ")" << endl;
                break;
            }
            cout << endl << " - " << animaux[choixAnimalUn - 1].getNom() << " (" << animaux[choixAnimalUn - 1].getEspece() << ") a battu "
                << animaux[choixAnimalDeux - 1].getNom() << " (" << animaux[choixAnimalDeux - 1].getEspece() << ")" << endl;
        }
        else { 
            // Les deux combattants sont des proies -> ils se font la paix
            cout << endl << "Les deux proies " << animaux[choixAnimalUn - 1].getNom()   << " (" << animaux[choixAnimalUn - 1].getEspece()   << ") et" 
                                               << animaux[choixAnimalDeux - 1].getNom() << " (" << animaux[choixAnimalDeux - 1].getEspece() << ") se font la paix!" << endl;
        }
        break;
    case 4: // Option : 'Reproduction'
        cout << "Tu as choisi de se faire reproduire entre eux deux animaux\n   - Attention : Reproduction possible uniquement si les deux animaux ont le meme regime alimentaire" << endl;
        afficherInfosSolo(animaux);
        cout << "Quels animaux veux-tu se faire reproduire ? \n\n - Animal 1 > ";
        cin >> choixAnimalUn;
        if (cin.fail() || choixAnimalUn < 1 || choixAnimalUn > animaux.size()) { choixAnimalUn = WhileCinFail(choixAnimalUn, animaux); }
        cout << endl << " - Animal 2 > ";
        cin >> choixAnimalDeux;
        while (cin.fail() || choixAnimalDeux < 1 || choixAnimalDeux > animaux.size() || choixAnimalDeux == choixAnimalUn) {
            if (choixAnimalDeux == choixAnimalUn) { cout << "Un animal ne peut pas se reproduire lui meme\n"; }
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Fais un choix correct, entre 1 et " << animaux.size() << " > ";
            cin >> choixAnimalDeux;
        }
        animauxRandEspece[0] = animaux[choixAnimalUn-1].getEspece(); animauxRandEspece[1] = animaux[choixAnimalDeux-1].getEspece();
        animauxRandRegime[0] = animaux[choixAnimalUn-1].getRegime(); animauxRandRegime[1] = animaux[choixAnimalDeux-1].getRegime();
        choixRandom = rand() % 2; // A fixer
        especeDuBebe = animauxRandEspece[choixRandom];
        regimeDuBebe = animauxRandRegime[choixRandom];
        nomDuBebe = animaux[choixRandom].getNom() + " Jr.";
        animaux.push_back(Animal::Animal(nomDuBebe, especeDuBebe, regimeDuBebe));
        cout << endl << nomDuBebe << " (" << especeDuBebe << ", " << regimeDuBebe << ") est le resultat de l'amour passionnel entre "
            << animaux[choixAnimalUn - 1].getNom() << " et " << animaux[choixAnimalDeux - 1].getNom() << endl;
        break;
    case 5: // Option : 'Creer un animal'
    cout << "Tu as choisis de créer un nouvel animal\n";
    afficherInfosSolo(animaux);
    cout << "Choisis l'animal que tu veux créer" << endl;
    int choix;
    string noms[25] = { "Loup", "Lapin", "Ours", "Biche", "Renard","Chevre", "Cheval", "Lynx", "Panda", "Tigre", "Koala", "Ecureuil", "Puma", "Coyote", "Rat", "Bison", "Lama", "Aigle", "Elephant", "Fennec", "Jaguar", "Zebre", "Castor", "Lion", "Capybara" };
    string nomAnimal;
    for (int i = 0; i < nombreDAnimaux; ++i) {
        for (int i = 0; i < 25; ++i) { // Affichage des choix d'espèces
            if (i < 8)
                cout << " - " << i + 1 << ".  " << noms[i] << endl;
            if (i > 8)
                cout << " - " << i + 1 << ". " << noms[i] << endl;
        }
        // Création de l'animal avec l'espèce choisie
        cout << endl << "Votre choix > ";
        cin >> choix;
        while (cin.fail() || choix < 1 || choix > 25) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << endl << "Veuillez entrer un choix correct, entre 1 et 25 > ";
            cin >> choix;
        }
        cout << endl << "Quel est le nom que vous voulez donner a votre nouveau " << noms[choix - 1] << " ? > ";
        cin >> nomAnimal;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << endl << "Veuillez donner un nom valide a votre animal > ";
            cin >> nomAnimal;
        }
        cout << endl;
        // Ajout de l'animal crée dans le vecteur animaux
        switch (choix) { // A changer mardi avec les noms des espèces (vide pour l'instant)
        case 1: animaux.push_back(Loup(nomAnimal));   break; case 6: animaux.push_back(Chevre(nomAnimal)); break; case 11: animaux.push_back(Koala(nomAnimal));    break; case 16: animaux.push_back(Bison(nomAnimal));    break; case 21: animaux.push_back(Jaguar(nomAnimal));   break;
        case 2: animaux.push_back(Lapin(nomAnimal));  break; case 7: animaux.push_back(Cheval(nomAnimal)); break; case 12: animaux.push_back(Ecureuil(nomAnimal)); break; case 17: animaux.push_back(Lama(nomAnimal));     break; case 22: animaux.push_back(Zebre(nomAnimal));    break;
        case 3: animaux.push_back(Ours(nomAnimal));   break; case 8: animaux.push_back(Lynx(nomAnimal));   break; case 13: animaux.push_back(Puma(nomAnimal));     break; case 18: animaux.push_back(Aigle(nomAnimal));    break; case 23: animaux.push_back(Castor(nomAnimal));   break;
        case 4: animaux.push_back(Biche(nomAnimal));  break; case 9: animaux.push_back(Panda(nomAnimal));  break; case 14: animaux.push_back(Coyote(nomAnimal));   break; case 19: animaux.push_back(Elephant(nomAnimal)); break; case 24: animaux.push_back(Lion(nomAnimal));     break;
        case 5: animaux.push_back(Renard(nomAnimal)); break; case 10: animaux.push_back(Tigre(nomAnimal)); break; case 15: animaux.push_back(Rat(nomAnimal));      break; case 20: animaux.push_back(Fennec(nomAnimal));   break; case 25: animaux.push_back(Capybara(nomAnimal)); break;
        default: break;
    }
    for (unsigned int i = 0; i < animaux.size(); ++i) {
        animaux[i].id = i + 1; // 1, 2, 3... animaux.size()
    }
    break;
     case 6: // Option : 'Rapprocher deux animaux'
     cout << "Tu as choisis de rapprocher deux animaux\n";
     afficherInfosSolo(animaux);
     cout << "Quels animaux veux-tu rapprocher ? \n\n - Animal 1 >";
     cin >> choixAnimalUn;
     if (cin.fail() || choixAnimalUn < 1 || choixAnimalUn > animaux.size()) { choixAnimalUn = WhileCinFail(choixAnimalUn, animaux); }
     cout << endl << " - Animal 2 > ";
     cin >> choixAnimalDeux;
     while (cin.fail() || choixAnimalDeux < 1 || choixAnimalDeux > animaux.size() || choixAnimalDeux == choixAnimalUn) {
         if (choixAnimalDeux == choixAnimalUn) { cout << "Un animal ne peut pas se rapprocher de lui même\n"; }
         cin.clear();
         cin.ignore(9999, '\n');
         cout << "Fais un choix correct, entre 1 et " << animaux.size() << " > ";
         cin >> choixAnimalDeux;
     }
         break;
     case 7: // Option : 'Saison des amours'
        setPeriodeDeReproduction(true);
    case 8:// Option : 'Ne rien faire'
        break;
    case 9: // Option : 'Quitter'
        return 'Q';
    default:
        break;
    }
    return ' ';
}
