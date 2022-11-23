#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "jeu.h"

void jouer() {

  PTR_JEU jeu = malloc(sizeof(JEU));
  debut_partie(jeu);
  system("cls");

  int tour = 0;
  while (victory_check(jeu->joueurs, jeu->plateau, tour) == -1) {
    system("cls");
    advance(jeu, tour);
    flank_attaque(jeu, tour);
    players_actions(jeu, tour);
    pioche(jeu, tour);

    tour += 1;
  }

  if (victory_check(jeu->joueurs, jeu->plateau, tour) == 2) {
    int joueur1_resultat = somme_mort(jeu, tour);
    int joueur2_resultat = somme_mort(jeu, tour + 1);
    if (joueur1_resultat > joueur2_resultat)
      printf("C'est %s qui gagne la partie !\n", jeu->joueurs[tour % 2]->nom);
    if (joueur1_resultat < joueur2_resultat)
      printf("C'est %s qui gagne la partie !\n",
             jeu->joueurs[(tour + 1) % 2]->nom);
    return;
  } else {
    if (jeu->joueurs[(tour + 1) % 2]->nbre_terrain_occupe == 3)
      printf("C'est %s qui gagne la partie avec 3 terrains occupee !\n",
             jeu->joueurs[(tour + 1) % 2]->nom);
    if (jeu->joueurs[(tour) % 2]->nbre_terrain_occupe == 3)
      printf("C'est %s qui gagne la partie avec 3 terrains occupee !\n",
             jeu->joueurs[tour % 2]->nom);
    return;
  }
  printf("Aucun joueur ne gagne la partie !\n");
}

int main() {
  while (1) {
    system("cls");
    int choixMenu;
    printf(" ||--||-Field Of Glory-||--||\n\n");
    printf("-------------Menu-------------\n\n");
    printf("           1.Jouer\n");
    printf("          2.Quitter\n");
    printf("\n");
    printf("------------------------------\n");
    printf("\n -> ");
    scanf("%d", &choixMenu);

    switch (choixMenu) {
    case 1:
      jouer();
      break;
    case 2:
      return 0;
      break;
    default:
      system("cls");
      break;
    }
  }
  return 0;
}
