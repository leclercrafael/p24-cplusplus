#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

// Taille du terrain de jeu
const int largeur = 20;
const int hauteur = 20;

// Directions possibles
enum Direction { HAUT, BAS, GAUCHE, DROITE };

// Structure représentant un segment du serpent
struct Position {
    int x, y;
};

class SnakeGame {
private:
    vector<Position> serpent;
    Position nourriture;
    Direction direction;
    bool gameOver;

public:
    // Constructeur
    SnakeGame() {
        serpent.push_back({ largeur / 2, hauteur / 2 }); // Initialisation du serpent au centre
        direction = DROITE;
        gameOver = false;
        genererNourriture();
    }

    // Fonction pour afficher le terrain de jeu
    void afficherTerrain() {
        system("cls"); // Effacer l'écran (fonction spécifique à Windows)
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                if (x == 0 || x == largeur - 1 || y == 0 || y == hauteur - 1) {
                    cout << "#"; // Bordure
                } else if (x == nourriture.x && y == nourriture.y) {
                    cout << "O"; // Nourriture
                } else {
                    bool serpentPartie = false;
                    for (const auto& s : serpent) {
                        if (s.x == x && s.y == y) {
                            cout << "*"; // Corps du serpent
                            serpentPartie = true;
                            break;
                        }
                    }
                    if (!serpentPartie) {
                        cout << " "; // Espace vide
                    }
                }
            }
            cout << endl;
        }
        cout << "Score: " << serpent.size() - 1 << endl;
    }

    // Fonction pour gérer les entrées du clavier
    void traiterInput() {
        if (_kbhit()) {
            char current = _getch();
            if (current == 'w' && direction != BAS) {
                direction = HAUT;
            } else if (current == 's' && direction != HAUT) {
                direction = BAS;
            } else if (current == 'a' && direction != DROITE) {
                direction = GAUCHE;
            } else if (current == 'd' && direction != GAUCHE) {
                direction = DROITE;
            } else if (current == 'q') {
                gameOver = true;
            }
        }
    }

    // Fonction pour déplacer le serpent
    void deplacerSerpent() {
        Position nouvelleTete = serpent.front();
        switch (direction) {
            case HAUT:
                nouvelleTete.y--;
                break;
            case BAS:
                nouvelleTete.y++;
                break;
            case GAUCHE:
                nouvelleTete.x--;
                break;
            case DROITE:
                nouvelleTete.x++;
                break;
        }

        // Vérifier si le serpent se mord
        for (size_t i = 1; i < serpent.size(); i++) {
            if (serpent[i].x == nouvelleTete.x && serpent[i].y == nouvelleTete.y) {
                gameOver = true;
                return;
            }
        }

        // Vérifier si le serpent sort du terrain
        if (nouvelleTete.x == 0 || nouvelleTete.x == largeur - 1 || nouvelleTete.y == 0 || nouvelleTete.y == hauteur - 1) {
            gameOver = true;
            return;
        }

        serpent.insert(serpent.begin(), nouvelleTete);

        // Si le serpent mange de la nourriture
        if (nouvelleTete.x == nourriture.x && nouvelleTete.y == nourriture.y) {
            genererNourriture(); // Générer une nouvelle nourriture
        } else {
            serpent.pop_back(); // Enlever la dernière partie du serpent
        }
    }

    // Fonction pour générer la nourriture
    void genererNourriture() {
        nourriture.x = rand() % (largeur - 2) + 1;
        nourriture.y = rand() % (hauteur - 2) + 1;
    }

    // Fonction pour vérifier si le jeu est terminé
    bool estFini() {
        return gameOver;
    }

    // Fonction pour jouer une boucle du jeu
    void jouer() {
        while (!estFini()) {
            afficherTerrain();
            traiterInput();
            deplacerSerpent();
            Sleep(100); // Pause pour contrôler la vitesse du jeu
        }
        cout << "Game Over!" << endl;
    }
};

int main() {
    SnakeGame jeu;
    jeu.jouer();
    return 0;
}
