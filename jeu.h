#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE 5
#define TAILLE_DECK 9

typedef struct carte_jeu {

    char type[10]; //attaque / action / terrain
  char nom[30]; //pike, infantry...
  int n_carte; // par rapport à la bibliotheque au début de la fonction main
  //char *affichage[9]; //visuel de la carte

  //FN_ATTAQUE attaque;  // suggestion affecter le ptr de fonction qui correspond à la carte

  //attaque/action
  int mouvement; //points de mouvement
  int flank; // points de flank
  int attaque; // point d'attaque
  int commandement; //point de commandement
  int victory_points;

  //terrain
  int joueur_controle;
	struct carte_jeu *suivant; //carte suivante
} CARTE_JEU, *PTR_CARTE_JEU;



//typedef void (*AFFICHAGE)(CARTE_JEU);

typedef struct joueur {
  char nom[40];
  int shuffle;
  int nbre_terrain_occupe;
  PTR_CARTE_JEU paquet[48];
  PTR_CARTE_JEU paquet_tirage;
  PTR_CARTE_JEU bonus_card;
  //struct carte_jeu *paquet_tirage;
  PTR_CARTE_JEU deck[TAILLE_DECK];
  int nb_carte_deck;
  //CARTE_ATTAQUE *deck; // suggest : tableau statique[taille]
  PTR_CARTE_JEU paquet_mort_adverse;
  PTR_CARTE_JEU paquet_defausse;
} JOUEUR, *PTR_JOUEUR;

typedef PTR_CARTE_JEU PLATEAU[TAILLE][TAILLE];

typedef int (*PTR_FN_TERRAIN)(PTR_CARTE_JEU, PTR_CARTE_JEU, PTR_CARTE_JEU); // suggestion

typedef int (*PTR_FN_ATTAQUE)(PTR_CARTE_JEU, PTR_CARTE_JEU, PTR_CARTE_JEU); // suggestion

typedef struct elements_du_jeu {
	PTR_JOUEUR joueurs[2];
  PLATEAU plateau;
  PTR_FN_ATTAQUE fonction_attaque[12];
  PTR_FN_TERRAIN fonction_terrain[4];
} JEU, *PTR_JEU;


PTR_CARTE_JEU append(PTR_CARTE_JEU p_tirage, PTR_CARTE_JEU carte);
PTR_CARTE_JEU supprimer_carte_tirage(PTR_CARTE_JEU p_tirage);
void afficher_carte(PTR_CARTE_JEU ligne_carte[], int debut, int taille);
void afficher_carte_terrain(PTR_CARTE_JEU ligne_carte[], int taille);
int calcul_point_attaque(PTR_JEU jeu, int tour, int vrai_tour, int carte_ami, int carte_enn);
int check_name(PTR_JEU);
void creation_affichage(char *aff[9]);
/*
void aff_action(PTR_CARTE_JEU carte);
void aff_attaque(PTR_CARTE_JEU carte);
void aff_terrain(PTR_CARTE_JEU carte);
*/
void initialisation_cartes(PTR_CARTE_JEU *paquet);
PTR_CARTE_JEU creation_carte(char *type, char *nom, int n_carte, int mouv, int flank, int attck, int comm, int vic_pts);
void initialisation_paquet_cartes_terrains(PTR_CARTE_JEU *paquet);
PTR_CARTE_JEU creation_carte_terrain(char *type, char *nom, int n_carte);
void melanger_carte(PTR_CARTE_JEU *paquet, int taille);
void melanger_carte_terrain(PTR_CARTE_JEU paquet, int taille);
void creation_main_tirage(PTR_JOUEUR joueurs);
void choix_paquet_tirage();
void detect_attaque_flank(PTR_JEU jeu, int tour);
void flank_attaque(PTR_JEU jeu, int tour);
void complete_deck(PTR_JOUEUR joueur);
void nb_carte_deck(PTR_JOUEUR joueur);
int somme_mort(PTR_JEU jeu, int tour);
void debut_partie(PTR_JEU jeu);
void tuer_carte(PTR_JEU jeu, int tour, int carte_attaquante);
//{elephant, spear, archers, light_cavalry, light_infantry, medium_infantry, cavalry, heavy_infantry, pike, commander, overlap, reserves}

int victory_check(PTR_JOUEUR joueurs[], PLATEAU plateau, int tour);
void compte_joueur_terrain(PLATEAU plateau, PTR_JOUEUR joueurs[]);
void advance(PTR_JEU jeu, int tour);

int elephant(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int spear(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int archers(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int light_cavalry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int light_infantry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int medium_infantry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int cavalry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int heavy_infantry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int pike(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int commander(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int overlap(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int reserves(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);

void creation_flank_test(PTR_JEU jeu);
void afficher_plateau(PTR_JEU jeu, int tour, int etat);
void players_actions(PTR_JEU jeu, int tour);

int plain(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int rough(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int woods(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);
int hill(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn);

int attaque(PLATEAU pleateau, int tour, CARTE_JEU *carte_att, CARTE_JEU *carte_terr);
int detection_victoire(int numero_joueur);
void tour_joueur();
void afficher_HandDeck();
void placement_carte(PTR_JEU jeu,int joueur);
void init(PLATEAU plateau);
void affiche(PLATEAU plateau);
void verif(PTR_JEU jeu,int ntr,int joueur, int carte_res, int i, int j);
void choix_plac(PTR_JEU jeu, int tour);
void enlevement(PTR_JEU jeu,int joueur,int carte_res,int DisM,int ntr);
void pioche(PTR_JEU jeu,int tour);

typedef PTR_CARTE_JEU PLATEAU[TAILLE][TAILLE];

void avance_carte_trou(PTR_JEU jeu){
  printf("Coucou\n");
  for(int i = 0; i < 5; i++){
    if(jeu->plateau[1][i] == NULL && jeu->plateau[0][i] != NULL){
      jeu->plateau[1][i] = jeu->plateau[0][i];
      jeu->plateau[0][i] = NULL;
    }
    if(jeu->plateau[3][i] == NULL && jeu->plateau[4][i] != NULL){
      jeu->plateau[3][i] = jeu->plateau[4][i];
      jeu->plateau[4][i] = NULL;
    }
  }
}

void nb_carte_deck(PTR_JOUEUR joueur) {
  joueur->nb_carte_deck = 0;
  for (int i = 0; i < 9; i++) {
    if (joueur->deck[i] != NULL)
      joueur->nb_carte_deck += 1;
  }
}

void ligne_vide(int taille, int largeur_carte, PTR_CARTE_JEU ligne_carte[]) {
  for (int i = 0; i < taille; i++) {
    if (ligne_carte[i] != NULL)
      printf("|%*c| ", largeur_carte, ' ');
    else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");
}

void afficher_carte_terrain(PTR_CARTE_JEU ligne_carte[], int taille) {
  int largeur_carte = 20;

  for (int i = 0; i < taille; i++) {
    // printf("%d ",ligne_carte[i]->joueur_controle);
    switch (ligne_carte[i]->joueur_controle) {
      case 0: printf("%*c/\\%*c ", largeur_carte / 2, ' ', largeur_carte / 2, ' '); break;
      default: printf("%*c ", largeur_carte + 1, ' '); break;
    }
  }
  printf("\n");

  for (int i = 0; i < taille; i++) {
    printf("+");
    for (int j = 0; j < largeur_carte; j++)
      printf("-");
    printf("+ ");
  }
  printf("\n");

  ligne_vide(taille, largeur_carte, ligne_carte);

  for (int i = 0; i < taille; i++) {
    PTR_CARTE_JEU carte = ligne_carte[i];
    int nombrecaract = strlen(carte->nom);

    int droite = (largeur_carte - nombrecaract) / 2;
    int gauche = (largeur_carte - nombrecaract - droite);

    printf("%c%*c%s%*c| ", '|', droite, ' ', carte->nom, gauche, ' ');
  }
  printf("\n");

  for (int i = 0; i < 2; i++)
    ligne_vide(taille, largeur_carte, ligne_carte);

  for(int i = 0; i < taille; i++){
    PTR_CARTE_JEU carte = ligne_carte[i];
    switch(carte->nom[0]){
      case 'H' : printf("|   +1 to defender   | ");break;
      case 'W' : printf("|  HEAVY INF, SPEAR  | ");break;
      case 'R' : printf("| Pay +1 CP to place | ");break;
      default : printf("|                    | ");break;
    }
  }
  printf("\n");

  for(int i = 0; i < taille; i++){
    PTR_CARTE_JEU carte = ligne_carte[i];
    switch(carte->nom[0]){
      case 'H' : printf("|  (if controlled)   | ");break;
      case 'W' : printf("|   PIKE, CAVALRY    | ");break;
      case 'R' : printf("|    unit in this    | ");break;
      default : printf("|                    | ");break;
    }
  }
  printf("\n");

  for(int i = 0; i < taille; i++){
    PTR_CARTE_JEU carte = ligne_carte[i];
    switch(carte->nom[0]){
      case 'W' : printf("|ELEPHANT -2 in attck| ");break;
      case 'R' : printf("|       column       | ");break;
      default : printf("|                    | ");break;
    }
  }
  printf("\n");

  for(int i = 0; i < taille; i++){
    PTR_CARTE_JEU carte = ligne_carte[i];
    switch(carte->nom[0]){
      case 'W' : printf("|    and defence.    | ");break;
      default : printf("|                    | ");break;
    }
  }
  printf("\n");

  for(int i = 0; i < taille; i++){
    PTR_CARTE_JEU carte = ligne_carte[i];
    switch(carte->nom[0]){
      case 'W' : printf("|  LIGHT INF + 1 in  | ");break;
      default : printf("|                    | ");break;
    }
  }
  printf("\n");

  for(int i = 0; i < taille; i++){
    PTR_CARTE_JEU carte = ligne_carte[i];
    switch(carte->nom[0]){
      case 'W' : printf("| attck and defence  | ");break;
      default : printf("|                    | ");break;
    }
  }
  printf("\n");

  for (int i = 0; i < 3; i++)
    ligne_vide(taille, largeur_carte, ligne_carte);

  for (int i = 0; i < taille; i++) {
    printf("+");
    for (int j = 0; j < largeur_carte; j++)
      printf("-");
    printf("+ ");
  }
  printf("\n");

  for (int i = 0; i < taille; i++) {
    switch (ligne_carte[i]->joueur_controle) {
    case 1:
      printf("%*c\\/%*c ", largeur_carte / 2, ' ', largeur_carte / 2, ' ');
      break;
    default:
      printf("%*c", largeur_carte + 3, ' ');
      break;
    }
  }
  printf("\n");
}

void afficher_carte(PTR_CARTE_JEU ligne_carte[], int debut, int taille) {
  int largeur_carte = 20;
  int space = 0;
  // LIGNE 1
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      printf("+");
      for (int j = 0; j < largeur_carte; j++)
        printf("-");
      printf("+ ");
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL)
      printf("|%*c| ", largeur_carte, ' ');
    else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");
  // LIGNE 2

  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      int nombrecaract = strlen(carte->nom);

      int droite = (largeur_carte - nombrecaract) / 2;
      int gauche = (largeur_carte - nombrecaract - droite);

      printf("%c%*c%s%*c| ", '|', droite, ' ', carte->nom, gauche, ' ');
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 3
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL)
      printf("|%*c| ", largeur_carte, ' ');
    else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 4
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      space = largeur_carte - strlen("PTs MVT :") - 5;
      printf("|PTs MVT : %*d(+%d)| ", space, carte->mouvement, carte->flank);
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 5
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      space = largeur_carte - strlen("PTs COMBAT :") - 5;
      printf("|PTs COMBAT : %*d%*c ", space, carte->attaque, 5, '|');
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 6
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      space = largeur_carte - strlen("PTs COMMAND :") - 5;
      printf("|PTs COMMAND : %*d%*c ", space, carte->commandement, 5, '|');
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 7
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      space = largeur_carte - strlen("PTs VICTOIRE :") - 5;
      printf("|PTs VICTOIRE : %*d%*c ", space, carte->victory_points, 5, '|');
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 8
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL)
      printf("|%*c| ", largeur_carte, ' ');
    else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 9
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      int l = (largeur_carte - strlen("MODIF(s)")) / 2;
      printf("|%*cMODIF(s)%*c| ", l, ' ', l, ' ');
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 10
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL)
      printf("|%*c| ", largeur_carte, ' ');
    else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 11

  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL &&
        strcmp(ligne_carte[i]->type, "terrain") != 0) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      switch (carte->nom[0]) {
      case 'H':
        space = (largeur_carte - strlen("VS CAVALRY -> -2")) / 2;
        printf("|%*c", space, ' ');
        printf("VS CAVALRY -> -2");
        space = (largeur_carte - strlen("VS CAVALRY -> -2")) / 2;
        printf("%*c| ", space, ' ');
        break;
      case 'E':
        space = (largeur_carte - strlen("VS LIGHT INF -> -4")) / 2;
        printf("|%*c", space, ' ');
        printf("VS LIGHT INF -> -4");
        space = (largeur_carte - strlen("VS LIGHT INF -> -4")) / 2;
        printf("%*c| ", space, ' ');
        break;
      case 'S':
        space = (largeur_carte - strlen("VS CAVALRY -> -1")) / 2;
        printf("|%*c", space, ' ');
        printf("VS CAVALRY -> -1");
        space = (largeur_carte - strlen("VS CAVALRY -> -1")) / 2;
        printf("%*c| ", space, ' ');
        break;
      case 'C':
        if (carte->nom[1] == 'A') {
          space = (largeur_carte - strlen("VS ELEPHANTS -> -2")) / 2;
          printf("|%*c", space, ' ');
          printf("VS ELEPHANTS -> -2");
          space = (largeur_carte - strlen("VS ELEPHANTS -> -2")) / 2;
          printf("%*c| ", space, ' ');
        } else
          printf("|%*c| ", largeur_carte, ' ');
        break;
      case 'P':
        space = (largeur_carte - strlen("WITH PIKE -> +1 ")) / 2;
        printf("|%*c", space, ' ');
        printf("WITH PIKE -> +1 ");
        space = (largeur_carte - strlen("WITH PIKE -> +1 ")) / 2;
        printf("%*c| ", space, ' ');
        break;
      case 'A':
        space = (largeur_carte - strlen("CAN BE COMBINED WITH")) / 2;
        printf("|%*c", space, '\0');
        printf("CAN BE COMBINED WITH");
        space = (largeur_carte - strlen("CAN BE COMBINED WITH")) / 2;
        printf("%*c| ", space, '\0');
        break;
      case 'L':
        if (carte->nom[6] == 'I') {
          space = (largeur_carte - strlen("VS ELEPHANT -> +3 ")) / 2;
          printf("|%*c", space, ' ');
          printf("VS ELEPHANT -> +3 ");
          space = (largeur_carte - strlen("VS ELEPHANT -> +3 ")) / 2;
          printf("%*c| ", space, ' ');
        } else
          printf("|%*c| ", largeur_carte, ' ');
        break;
      default:
        printf("|%*c| ", largeur_carte, ' ');
        break;
      }
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }

  printf("\n");

  // LIGNE 12

  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL &&
        strcmp(ligne_carte[i]->type, "terrain") != 0) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      switch (carte->nom[0]) {
      case 'E':
        space = (largeur_carte - strlen("MAY COMBINE WITH")) / 2;
        printf("|%*c", space, ' ');
        printf("MAY COMBINE WITH");
        space = (largeur_carte - strlen("MAY COMBINE WITH")) / 2;
        printf("%*c| ", space, ' ');
        break;
      case 'S':
        space = (largeur_carte - strlen("WIN TIES IF DEF")) / 2 + 1;
        printf("|%*c", space, '\0');
        printf("WIN TIES IF DEF");
        space = (largeur_carte - strlen("WIN TIES IF DEF")) / 2 + 1;
        printf("%*c| ", space, ' ');
        break;
      case 'C':
        if (carte->nom[1] == 'A') {
          space = (largeur_carte - strlen("VS PIKE -> -1 ")) / 2;
          printf("|%*c", space, ' ');
          printf("VS PIKE -> -1 ");
          space = (largeur_carte - strlen("VS PIKE -> -1 ")) / 2;
          printf("%*c| ", space, ' ');
        } else {
          printf("|%*c| ", largeur_carte, ' ');
        }
        break;
      case 'A':
        space = (largeur_carte - strlen("ANY OTHER UNIT TYPE")) / 2;
        printf("|%*c", space, '\0');
        printf("ANY OTHER UNIT TYPE");
        space = (largeur_carte - strlen("ANY OTHER UNIT TYPE")) / 2;
        printf("%*c| ", space, ' ');
        break;
      case 'I':
        space = (largeur_carte - strlen("COMBINE WITH ELEPHANTS")) / 2;
        printf("|%*c", space, ' ');
        printf("COMBINE WITH ELEPHANTS");
        space = (largeur_carte - strlen("COMBINE WITH ELEPHANTS")) / 2;
        printf("%*c| ", space, ' ');
        break;
      default:
        printf("|%*c| ", largeur_carte, ' ');
        break;
      }
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      PTR_CARTE_JEU carte = ligne_carte[i];
      if (carte->nom[0] == 'E') {
        space = (largeur_carte - strlen("LIGHT INF, RAMPAGE")) / 2;
        printf("|%*c", space, ' ');
        printf("LIGHT INF, RAMPAGE");
        space = (largeur_carte - strlen("LIGHT INF, RAMPAGE")) / 2;
        printf("%*c| ", space, ' ');
      } else {
        printf("|%*c| ", largeur_carte, ' ');
      }
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");

  // LIGNE 14
  for (int i = debut; i < taille; i++) {
    if (ligne_carte[i] != NULL) {
      printf("+");
      for (int j = 0; j < largeur_carte; j++)
        printf("-");
      printf("+ ");
    } else
      printf("%*c", largeur_carte + 3, ' ');
  }
  printf("\n");
}

void afficher_num_carte_choix_deck(int debut, int nb_carte, PTR_CARTE_JEU *lst_carte) {
  for (int i = debut; i < debut + nb_carte; i++) {
    if (lst_carte[i - debut] != NULL)
      printf("        ~ %02d ~         ", i + 1);
    else
      printf("                       ");
  }
  printf("\n");
}

void afficher_num_carte_choix_place(int debut, int nb_carte, PTR_CARTE_JEU *lst_carte, int etat) {
  for (int i = debut; i < debut + nb_carte; i++) {
    if ((lst_carte[i - debut] == NULL && etat == 0) || (lst_carte[i - debut] != NULL && (etat == 2 || etat == 1)))
      printf("        ~ 0%d ~         ", i + 1);
    else
      printf("                       ");
  }
  printf("\n");
}

void afficher_plateau(PTR_JEU jeu, int tour, int etat) {
  afficher_carte(jeu->plateau[0], 0, TAILLE);
  if (tour % 2 == 0 && etat != 2)
    afficher_num_carte_choix_place(0, 5, jeu->plateau[0], etat);

  afficher_carte(jeu->plateau[1], 0, TAILLE);
  if (tour % 2 == 0 && etat != 2)
    afficher_num_carte_choix_place(5, 5, jeu->plateau[1], etat);

  afficher_carte_terrain(jeu->plateau[2], TAILLE);
  if (etat == 2)
    afficher_num_carte_choix_place(0, 5, jeu->plateau[2], etat);

  afficher_carte(jeu->plateau[3], 0, TAILLE);
  if (tour % 2 == 1 && etat != 2)
    afficher_num_carte_choix_place(0, 5, jeu->plateau[3], etat);

  afficher_carte(jeu->plateau[4], 0, TAILLE);
  if (tour % 2 == 1 && etat != 2)
    afficher_num_carte_choix_place(5, 5, jeu->plateau[4], etat);
}

// Initialisation début de partie

PTR_CARTE_JEU creation_carte(char *type, char *nom, int n_carte, int mouv, int flank, int attck, int comm, int vic_pts) {
  PTR_CARTE_JEU carte = malloc(sizeof(CARTE_JEU));

  strcpy(carte->type, type);
  strcpy(carte->nom, nom);
  carte->n_carte = n_carte;
  carte->mouvement = mouv;
  carte->flank = flank;
  carte->attaque = attck;
  carte->commandement = comm;
  carte->victory_points = vic_pts;
  carte->suivant = NULL;

  return carte;
}

PTR_CARTE_JEU creation_carte_terrain(char *type, char *nom, int n_carte) {
  PTR_CARTE_JEU carte = malloc(sizeof(CARTE_JEU));

  strcpy(carte->type, type);
  strcpy(carte->nom, nom);
  carte->n_carte = n_carte;
  carte->joueur_controle = -1;
  carte->suivant = NULL;

  return carte;
}

void initialisation_cartes(PTR_CARTE_JEU *paquet) {
  int num_carte = 0;
  int nb_carte = 0;
  char *cartes[] = {"ELEPHANT", "SPEAR", "ARCHERS", "LIGHT CAVALRY", "LIGHT INFANTRY", "MEDIUM INFANTRY", "CAVALRY", "HEAVY INFANTRY", "PIKE", "COMMANDER", "OVERLAP", "RESERVES"};

  //###################
  // Cartes Elephants 0 - 1
  //###################

  for (int i = 2; i < 4; i++) {

    paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 5, 3, 5, i, 3);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Spears 2 - 3
  //###################
  for (int i = 2; i < 5; i++) {
    paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 5, 3, 4, i, 3);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Archer 4 - 6
  //###################

  for (int i = 2; i < 4; i++) {
    paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 2, 0, 0, i, 0);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Light Cavalry 7 - 10
  //###################

  paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 0, 0, 1, 2, 0);
  num_carte += 1;
  paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 0, 0, 1, 3, 0);
  num_carte += 1;
  paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 0, 0, 1, 3, 0);
  num_carte += 1;
  paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 0, 0, 1, 4, 0);
  num_carte += 1;

  nb_carte += 1;
  //###################
  // Cartes Light Infantry 11 - 16
  //###################

  for (int i = 2; i < 5; i++) {
    paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 1, 0, 1, i, 0);
    num_carte += 1;
    paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 1, 0, 1, i, 0);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Medium Infantry 17 - 24
  //###################

  paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 3, 1, 3, 2, 1);
  num_carte += 1;
  paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 3, 1, 3, 2, 1);
  num_carte += 1;

  for (int i = 3; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 3, 1, 3, i, 1);
      num_carte += 1;
    }
  }

  nb_carte += 1;
  //###################
  // Cartes Cavarly 25 - 30
  //###################

  for (int i = 2; i < 5; i++) {
    for (int j = 0; j < 2; j++) {
      paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 2, 0, 3, i, 1);
      num_carte += 1;
    }
  }

  nb_carte += 1;
  //###################
  // Cartes Heavy Infantry 31 -36
  //###################

  for (int i = 2; i < 5; i++) {
    for (int j = 0; j < 2; j++) {
      paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 4, 2, 4, i, 2);
      num_carte += 1;
    }
  }

  nb_carte += 1;
  //###################
  // Cartes Pike 37 - 39
  //###################

  for (int i = 2; i < 5; i++) {
    paquet[num_carte] = creation_carte("attaque", cartes[nb_carte], nb_carte, 5, 3, 4, i, 2);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Commander 40 - 44
  //###################

  for (int i = 0; i < 5; i++) {
    paquet[num_carte] = creation_carte("action", cartes[nb_carte], nb_carte, 0, 0, 0, 5, 0);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Overlap
  //###################

  for (int i = 0; i < 2; i++) {
    paquet[num_carte] = creation_carte("action", cartes[nb_carte], nb_carte, 0, 0, 0, 2, 0);
    num_carte += 1;
  }

  nb_carte += 1;
  //###################
  // Cartes Reserves
  //###################

  paquet[num_carte] = creation_carte("action", cartes[nb_carte], nb_carte, 0, 0, 0, 2, 0);
  num_carte += 1;
}

void initialisation_paquet_cartes_terrains(PTR_CARTE_JEU *paquet) {
  int num_carte = 0;
  int pas_de_controle = -1;
  PTR_CARTE_JEU carte;

  for (int i = 0; i < 6; i++) {
    paquet[num_carte] = creation_carte_terrain("terrain", "PLAIN", 0);
    num_carte += 1;
  }

  paquet[num_carte] = creation_carte_terrain("terrain", "ROUGH", 1);
  num_carte += 1;

  paquet[num_carte] = creation_carte_terrain("terrain", "WOODS", 2);
  num_carte += 1;

  paquet[num_carte] = creation_carte_terrain("terrain", "HILL", 3);
  num_carte += 1;
}

void melanger_carte(PTR_CARTE_JEU *paquet, int taille) {
  for (int i = 0; i < taille; i++) {
    int j = rand() % (taille - i) + i;
    PTR_CARTE_JEU tmp = malloc(sizeof(CARTE_JEU));
    tmp = paquet[j];
    paquet[j] = paquet[i];
    paquet[i] = tmp;
  }
}

PTR_CARTE_JEU append(PTR_CARTE_JEU p_tirage, PTR_CARTE_JEU carte) {
  if (p_tirage == NULL) {
    return carte;
  }
  carte->suivant = p_tirage;
  return carte;
}

void creation_main_tirage(PTR_JOUEUR joueur) {
  int carte_n = 0;
  PTR_CARTE_JEU p_tirage = NULL;
  while (carte_n != 48) {
    printf("\n");
    PTR_CARTE_JEU cartes[4];
    for (int i = 0; i < 4; i++) {

      cartes[i] = joueur->paquet[carte_n + i];
    }
    afficher_carte(cartes,0,4);
    afficher_num_carte_choix_deck(0,4,cartes);
    printf("\n");
    int temp_carte = 0;
    for (int i = 0; i < 2; i++) {
      int carte = 0;
      while (carte > 4 || carte < 1 || carte == temp_carte) {
        printf("Entrez une carte parmis les choix ci-dessus : ");
        fflush(stdout);
        scanf("%d", &carte);
        //carte = rand() % 4 + 1;
      }
      p_tirage = append(p_tirage, joueur->paquet[carte_n + carte - 1]);
      printf("Carte %s enregistree\n", joueur->paquet[carte_n + carte - 1]->nom);
      temp_carte = carte;
    }

    carte_n += 4;
  }
  joueur->paquet_tirage = p_tirage;
}

PTR_CARTE_JEU supprimer_carte_tirage(PTR_CARTE_JEU p_tirage) {
  PTR_CARTE_JEU n_p_tirage = p_tirage->suivant;
  p_tirage->suivant = NULL;
  return n_p_tirage;
}

void complete_deck(PTR_JOUEUR joueur) {
  for (int i = 0; i < 9; i++) {
    if (joueur->deck[i] == NULL) {
      joueur->deck[i] = joueur->paquet_tirage;
      joueur->paquet_tirage = supprimer_carte_tirage(joueur->paquet_tirage);
    }
  }
}

int check_name(PTR_JEU jeu){
  int p = -1;
  char name[5];
  int i = 0;
  while(jeu->joueurs[0]->nom[i] != '\0' || i < 5){
    name[i] = toupper(jeu->joueurs[0]->nom[i]);
  }

  if(strncmp(name, "ILYES",5))
      p = 0;

  i = 0;
  while(jeu->joueurs[1]->nom[i] != '\0' || i < 5){
    name[i] = toupper(jeu->joueurs[0]->nom[i]);
  }

  if(strncmp(name, "ILYES",5))
      p = 1;

  return p;
}

void debut_partie(PTR_JEU jeu) {
  system("cls");

  //=========================
  // INITIALISATION DES CARTES
  //=========================

  PTR_CARTE_JEU paquet9[9];
  PTR_CARTE_JEU paquetTerrain[9];
  PTR_CARTE_JEU paquetBleu[48];
  PTR_CARTE_JEU paquetRouge[48];

  PTR_JOUEUR joueurBleu = malloc(sizeof(JOUEUR));
  PTR_JOUEUR joueurRouge = malloc(sizeof(JOUEUR));
  PLATEAU plateau;

  PTR_FN_ATTAQUE cartes_att[] = {elephant, spear, archers, light_cavalry, light_infantry, medium_infantry, cavalry, heavy_infantry, pike, commander, overlap, reserves};
  PTR_FN_TERRAIN cartes_terr[] = {plain, rough, woods, hill};

  for(int i = 0; i < 12; i++)
    jeu->fonction_attaque[i] = cartes_att[i];

  for(int i = 0; i < 4; i++)
    jeu->fonction_terrain[i] = cartes_terr[i];

  initialisation_cartes(paquetBleu);
  initialisation_cartes(paquetRouge);
  for (int i = 0; i < 48; i++) {
    joueurBleu->paquet[i] = paquetBleu[i];
    joueurRouge->paquet[i] = paquetRouge[i];
  }
  srand(time(NULL));
  for (int i = 0; i < rand() % 500; i += rand() % 5) {
    melanger_carte(joueurBleu->paquet, 48);
  }
  for (int i = 0; i < rand() % 500; i += rand() % 5) {
    melanger_carte(joueurRouge->paquet, 48);
  }

  initialisation_paquet_cartes_terrains(paquet9);
  for (int i = 0; i < 9; i++) {
    paquetTerrain[i] = paquet9[i];
  }
  for (int i = 0; i < rand() % 500; i += rand() % 5) {
    melanger_carte(paquetTerrain, 9);
  }

  //=========================
  // Initialisation du jeu
  //=========================

  jeu->joueurs[0] = joueurBleu;
  jeu->joueurs[1] = joueurRouge;

  //=========================
  // Mise en place des cartes terrains
  //=========================

  int debut = rand() % 5;
  int n_carte = debut;
  int l_terrain = 2;
  int max_carte = 5;

  for (double i = 0; i < max_carte; i++) {
    int new_index = 2 + i - (3.0 / 2.0) * i * (i - 1) +
                    (4.0 / 3.0) * i * (i - 1) * (i - 2) -
                    (5.0 / 6.0) * i * (i - 1) * (i - 2) * (i - 3);
    while (paquetTerrain[n_carte]->nom[0] != 'P' && n_carte < max_carte + debut) {
      n_carte += 1;
    }

    if (n_carte < max_carte + debut) {
      jeu->plateau[l_terrain][new_index] = paquetTerrain[n_carte];

    } else {
      while (paquetTerrain[n_carte - max_carte]->nom[0] == 'P' &&
             n_carte - max_carte < max_carte + debut) {
        n_carte += 1;
      }
      jeu->plateau[l_terrain][new_index] = paquetTerrain[n_carte - max_carte];
    }
    n_carte += 1;
  }

  //=========================
  // NOMS DES JOUEURS
  //=========================

  char nom[40];

  printf("Joueur 0, quel est votre nom ?\n -> ");
  scanf("%s",nom);
  strcpy(jeu->joueurs[0]->nom,nom);

  printf("Joueur 1, quel est votre nom ?\n -> ");
  scanf("%s",nom);
  strcpy(jeu->joueurs[1]->nom,nom);

  //=========================
  // Creation des mains tirage des joueurs
  //=========================

  printf("%s, choisissez votre main de tirage !", jeu->joueurs[0]->nom);
  creation_main_tirage(jeu->joueurs[0]);
  printf("%s, choisissez votre main de tirage !", jeu->joueurs[1]->nom);
  creation_main_tirage(jeu->joueurs[1]);

  complete_deck(jeu->joueurs[0]);
  complete_deck(jeu->joueurs[1]);

  nb_carte_deck(jeu->joueurs[0]);
  nb_carte_deck(jeu->joueurs[1]);
}

// Detection victoire et compte terrain occupé

void compte_joueur_terrain(PLATEAU plateau, PTR_JOUEUR joueurs[]) {
  joueurs[0]->nbre_terrain_occupe = 0;
  joueurs[1]->nbre_terrain_occupe = 0;
  for (int i = 0; i < 5; i++) {
    if (plateau[2][i]->joueur_controle != -1)
      joueurs[plateau[2][i]->joueur_controle]->nbre_terrain_occupe += 1;
  }
}

void advance_i(PTR_JEU jeu, int i, int tour) {
  int partie_plateau_joueur = tour % 2 * 3;

  // Si le joueur tour%2 control la zone
  if ((jeu->plateau[partie_plateau_joueur][i] != NULL ||
       jeu->plateau[partie_plateau_joueur + 1][i] != NULL) &&
      jeu->plateau[4 - partie_plateau_joueur][i] == NULL &&
      jeu->plateau[4 - partie_plateau_joueur - 1][i] == NULL)
    jeu->plateau[2][i]->joueur_controle = tour % 2;
  else
    jeu->plateau[2][i]->joueur_controle = -1;
}

void advance(PTR_JEU jeu, int tour) {
  for (int i = 0; i < 5; i++) {
    advance_i(jeu, i, tour);
  }
  compte_joueur_terrain(jeu->plateau, jeu->joueurs);
}

int victory_check(PTR_JOUEUR joueurs[], PLATEAU plateau, int tour) {
  // compte_joueur_terrain(plateau, joueurs);
  int win = -1;
  if (joueurs[tour % 2]->nbre_terrain_occupe == 3)
    win = tour % 2;
  if (joueurs[0]->shuffle >= 2 && joueurs[1]->shuffle >= 2)
    win = 2;
  return win;
}

////////////////////////
// Flank attack
////////////////////////

int nb_enn(PTR_JEU jeu, int tour, int p_j, int j){
  int nb_en = 0;
  for(int i = 0; i < 3; i++){
    if(jeu->plateau[2-1*p_j][j-i+1] != NULL)
      nb_en += 1;
  }
  return nb_en;
}

int nb_ami(PTR_JEU jeu, int tour, int p_j, int j){
  int nb_am = 0;
  for(int i = 0; i < 3; i++){
    if(jeu->plateau[2+1*p_j][j-i+1] != NULL)
      nb_am += 1;
  }
  return nb_am;
}

int condition1(PTR_JEU jeu, int tour, int j){
  int place_joueur;
  if(tour%2 == 0)
    place_joueur = -1;
  if(tour%2 == 1)
    place_joueur = 1;
  if(jeu->plateau[2 + place_joueur][j] != NULL
    && nb_enn(jeu, tour, place_joueur, j) == 1
    && (jeu->plateau[2 - place_joueur][j-1] != NULL || jeu->plateau[2 - place_joueur][j+1] != NULL)
    && nb_ami(jeu, tour, place_joueur, j) >= 1
    && (jeu->plateau[2 + place_joueur][j-1] != NULL || jeu->plateau[2 + place_joueur][j+1] != NULL)){
    return j;
  }else if(j != 4){
    return condition1(jeu, tour, j+1);
  }else{
    return -1;
  }
}

int calcul_point_attaque(PTR_JEU jeu, int tour, int vrai_tour, int carte_ami, int carte_enn){

  int tot_pts = 0;
  int Snd_carte = 0;

  int i = (carte_ami - 1) / 5 + (tour % 2) * 3;
  int j = (carte_ami - 1) % 5;
  if((carte_ami - 1)/5 == 0)
    Snd_carte = carte_ami + 5;
  else
    Snd_carte = carte_ami - 5;

  int i2 = (carte_enn - 1) / 5 + ((tour+1) % 2) * 3;
  int j2 = (carte_enn - 1) % 5;

  tot_pts += jeu->plateau[i][j]->attaque;

  tot_pts += jeu->joueurs[tour%2]->bonus_card->commandement;

  if(jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j] != NULL)
    tot_pts += 1;

  switch(jeu->plateau[i][j]->n_carte){
    case 0 : tot_pts += elephant(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 1 : tot_pts += spear(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 2 : tot_pts += archers(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 3 : tot_pts += light_cavalry(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 4 : tot_pts += light_infantry(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 5 : tot_pts += medium_infantry(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 6 : tot_pts += cavalry(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 7 : tot_pts += heavy_infantry(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 8 : tot_pts += pike(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 9 : tot_pts += commander(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 10 : tot_pts += overlap(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    case 11 : tot_pts += reserves(jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]); break;
    default : break;
  }

  /*
========
Suite à certains bug, cette partie fut remplacé par le précédent switch

  tot_pts += jeu->fonction_attaque[jeu->plateau[i][j]->n_carte](jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]);

  tot_pts += jeu->fonction_terrain[jeu->plateau[i][j]->n_carte](jeu->plateau[i][j],jeu->plateau[(Snd_carte - 1) / 5 + tour % 2 * 3][j],jeu->plateau[i2][j2]);
========
  */
  if(strcmp(jeu->plateau[2][j]->nom,"HILL") == 0 && tour != vrai_tour && jeu->plateau[2][j]->joueur_controle == tour%2){
    tot_pts += 1;
  }

  return tot_pts;
}

void detect_attaque_flank(PTR_JEU jeu, int tour) {

  int place_joueur;
  if(tour%2 == 0)
    place_joueur = -1;
  if(tour%2 == 1)
    place_joueur = 1;
  printf("%d", tour%2);
  int j_flank = condition1(jeu, tour, 0);
  //printf("flank ou pas ? %d\n", j_flank);
  if(j_flank != -1){
    afficher_plateau(jeu, tour, -1);
    int enn = 0;
    if(jeu->plateau[2-place_joueur][j_flank-1] != NULL)
      enn = (2-place_joueur-(tour+1)%2*3)*5+j_flank;
    else
      enn = (2-place_joueur-(tour+1)%2*3)*5+j_flank+2;

    printf("%s vous pouvez faire une attaque de flank avec votre %s en colonne %d sur l'unité %s ennemi en colonne %d : %d!\n", jeu->joueurs[tour%2]->nom, jeu->plateau[2+place_joueur][j_flank]->nom, j_flank+1, jeu->plateau[(enn-1)/5+((tour+1)%2)*3][(enn-1)%5]->nom, (enn-1)%5, (enn-1)/5+((tour+1)%2)*3);
    int ami = (2+place_joueur-tour%2*3)*5+j_flank+1;
    printf("%d : %d\n", ami, enn);
    printf("Voulez vous le faire ?\n -> ");
    char rep[10];
    scanf("%s", rep);
    printf("%s", rep);
    if(toupper(rep[0]) == 'O'){
      int total_point_attaquant = 0;
      printf("%d", total_point_attaquant);
      total_point_attaquant = calcul_point_attaque(jeu, tour, tour, ami, enn) + 2;
      int total_point_attaquer = calcul_point_attaque(jeu, tour+1, tour, enn, ami);

      printf("%s a une puissance de %d et %s a une puissance de %d\n", jeu->joueurs[tour%2]->nom, total_point_attaquant, jeu->joueurs[(tour+1)%2]->nom, total_point_attaquer);

      if(total_point_attaquant > total_point_attaquer){
        printf("%s gagne en attaquant !\n", jeu->joueurs[tour%2]->nom);
        jeu->plateau[2][(ami-1) % 5]->joueur_controle = tour%2;
        tuer_carte(jeu, tour, enn);
        if(strcmp(jeu->plateau[(enn-1) / 5 + (tour+1)%2*3][(enn-1) % 5]->nom,"ELEPHANT") == 0){
          printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[(tour+1)%2]->nom);
          for(int i = 0; i < 9; i++){
            if(jeu->joueurs[(tour+1)%2]->deck[i] != NULL){
              jeu->joueurs[tour%2]->paquet_mort_adverse = append(jeu->joueurs[tour%2]->paquet_mort_adverse, jeu->joueurs[(tour+1)%2]->deck[i]);
              jeu->joueurs[(tour+1)%2]->deck[i] = NULL;
              return;
            }
          }
        }
        return;
      }

      if(total_point_attaquant < total_point_attaquer){
        printf("%s gagne en defendant !\n", jeu->joueurs[(tour+1)%2]->nom);
        jeu->plateau[2][(enn-1) % 5]->joueur_controle = (tour+1)%2;
        tuer_carte(jeu, tour, ami);
        if(strcmp(jeu->plateau[(ami-1) / 5 + (tour+1)%2*3][(ami-1) % 5]->nom,"ELEPHANT") == 0){
          printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[tour%2]->nom);
          for(int i = 0; i < 9; i++){
            if(jeu->joueurs[tour%2]->deck[i] != NULL){
              jeu->joueurs[(tour+1)%2]->paquet_mort_adverse = append(jeu->joueurs[(tour+1)%2]->paquet_mort_adverse, jeu->joueurs[tour%2]->deck[i]);
              jeu->joueurs[tour%2]->deck[i] = NULL;
              return;
            }
          }
        }
        return;
      }

      if(total_point_attaquant == total_point_attaquer){
        if(jeu->plateau[(ami-1)/5 + tour%2*3][(ami-1)%2] != NULL){
          if(strcmp(jeu->plateau[(ami-1)/5 + tour%2*3][(ami-1)%2]->nom, "PIKE") == 0)
            printf("%s gagne en attaquant grace à son PIKE !\n", jeu->joueurs[tour%2]->nom);
            jeu->plateau[2][(enn-1) % 5]->joueur_controle = tour%2;
            tuer_carte(jeu, tour, enn);
          if(strcmp(jeu->plateau[(enn-1) / 5 + (tour+1)%2*3][(enn-1) % 5]->nom,"ELEPHANT") == 0){
            printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[(tour+1)%2]->nom);
            for(int i = 0; i < 9; i++){
              if(jeu->joueurs[(tour+1)%2]->deck[i] != NULL){
                jeu->joueurs[tour%2]->paquet_mort_adverse = append(jeu->joueurs[tour%2]->paquet_mort_adverse, jeu->joueurs[(tour+1)%2]->deck[i]);
                jeu->joueurs[(tour+1)%2]->deck[i] = NULL;
                return;
              }
            }
          }
          return;
        }else if(jeu->plateau[(enn-1)/2 + (tour + 1)%2*3][(enn-1)%2] != NULL){
          if(strcmp(jeu->plateau[(enn-1)/2 + (tour + 1)%2*3][(enn-1)%2]->nom, "PIKE") == 0)
            printf("%s gagne en defendant grace à son PIKE !\n", jeu->joueurs[(tour+1)%2]->nom);
            tuer_carte(jeu, tour+1, ami);
          if(strcmp(jeu->plateau[(ami-1) / 5 + (tour+1)%2*3][(ami-1) % 5]->nom,"ELEPHANT") == 0){
            printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[tour%2]->nom);
            for(int i = 0; i < 9; i++){
              if(jeu->joueurs[tour%2]->deck[i] != NULL){
                jeu->joueurs[(tour+1)%2]->paquet_mort_adverse = append(jeu->joueurs[(tour+1)%2]->paquet_mort_adverse, jeu->joueurs[tour%2]->deck[i]);
                jeu->joueurs[tour%2]->deck[i] = NULL;
                return;
              }
            }
          }
          return;
        }
      }

      printf("Aucun joueur ne gagne\n");
      tuer_carte(jeu, tour, enn);
      tuer_carte(jeu, tour+1, ami);
  }
}
  }
void flank_attaque(PTR_JEU jeu, int tour) {
  detect_attaque_flank(jeu, tour);
}

//attaque

int elephant(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(strcmp(carte_enn->nom,"LIGHT INFANTRY") == 0)
    mod -= 4;
  return mod;
}

int spear(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(strcmp(carte_enn->nom,"CAVALRY") == 0)
    mod -= 1;
  return mod;
}

//pas de mod
int archers(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

//pas de mod
int light_cavalry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}
int light_infantry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(strcmp(carte_enn->nom,"ELEPHANT") == 0)
    mod = 3;
  return mod;
}

//pas de mod
int medium_infantry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

int cavalry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(strcmp(carte_enn->nom,"CAVALRY") == 0)
    mod -= 2;
  if(strcmp(carte_enn->nom,"PIKE") == 0)
    mod -= 1;
  return mod;
}

int heavy_infantry(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(strcmp(carte_enn->nom,"CAVALRY") == 0)
    mod -= 2;
  return mod;
}

int pike(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(carte_ami2 != NULL)
    if(strcmp(carte_ami2->nom,"PIKE") == 0)
      mod += 1;
  return mod;
}

//action

int commander(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

int overlap(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

int reserves(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

//terrain

int plain(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

int rough(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

int woods(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  return mod;
}

int hill(PTR_CARTE_JEU carte_ami, PTR_CARTE_JEU carte_ami2, PTR_CARTE_JEU carte_enn) {
  int mod = 0;
  if(strcmp(carte_ami->nom, "HEAVY INFANTRY") == 0
    || strcmp(carte_ami->nom, "SPEAR") == 0
    || strcmp(carte_ami->nom, "PIKE") == 0
    || strcmp(carte_ami->nom, "CAVALRY") == 0
    || strcmp(carte_ami->nom, "ELEPHANT") == 0)
    mod = -2;
  if(strcmp(carte_ami->nom, "LIGHT INFANTRY") == 0)
    mod = 1;
  return mod;
}

void init(PLATEAU plateau) {
  int num_cell = 1;
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      PTR_CARTE_JEU case_carte = malloc(sizeof(CARTE_JEU));
      plateau[i][j] = case_carte;
    }
  }
}

void affiche(PLATEAU plateau) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      printf("%s |", plateau[i][j]->nom);
    }
    printf("\n");
  }
  printf("\n");
}

void creation_flank_test(PTR_JEU jeu) {
  for (int i = 0; i < 48; i++) {
    if (strcmp(jeu->joueurs[0]->paquet[i]->nom, "LIGHT CAVALRY") == 0)
      jeu->plateau[1][0] = jeu->joueurs[0]->paquet[i];
    if (strcmp(jeu->joueurs[0]->paquet[i]->nom, "PIKE") == 0)
      jeu->plateau[1][1] = jeu->joueurs[0]->paquet[i];
    if (strcmp(jeu->joueurs[0]->paquet[i]->nom, "LIGHT INFANTRY") == 0)
      jeu->plateau[1][4] = jeu->joueurs[0]->paquet[i];

    if (strcmp(jeu->joueurs[1]->paquet[i]->nom, "CAVALRY") == 0)
      jeu->plateau[3][0] = jeu->joueurs[1]->paquet[i];
    if (strcmp(jeu->joueurs[1]->paquet[i]->nom, "MEDIUM INFANTRY") == 0)
      jeu->plateau[3][1] = jeu->joueurs[1]->paquet[i];
    if (strcmp(jeu->joueurs[1]->paquet[i]->nom, "HEAVY INFANTRY") == 0)
      jeu->plateau[3][2] = jeu->joueurs[1]->paquet[i];
    if (strcmp(jeu->joueurs[1]->paquet[i]->nom, "ELEPHANT") == 0)
      jeu->plateau[3][4] = jeu->joueurs[1]->paquet[i];

    if (strcmp(jeu->joueurs[1]->paquet[i]->nom, "ARCHERS") == 0)
      jeu->plateau[4][1] = jeu->joueurs[1]->paquet[i];
    if (strcmp(jeu->joueurs[1]->paquet[i]->nom, "ARCHERS") == 0)
      jeu->plateau[4][4] = jeu->joueurs[1]->paquet[i];


  }
}

int test_carte_valide(PTR_JEU jeu, PTR_CARTE_JEU carte, int poscase, int tour) {
  int partie_plateau_joueur = tour % 2 * 3;
  int i = (poscase - 1) / 5 + partie_plateau_joueur; // 1
  int j = (poscase - 1) % 5;

  if(strcmp(carte->type,"action") == 0){
    return 0;
  }
  if ((i == 1 || i == 3))
    if (j > 0 && j < 4 && carte->mouvement < jeu->joueurs[tour % 2]->nb_carte_deck) {
      return 1;
      if ((j == 0 || j == 4) && carte->mouvement + carte->flank < jeu->joueurs[tour % 2]->nb_carte_deck)
        return 0;
    }
  if (i == 0 || i == 4){
    if (((j == 0 || j == 4) && carte->mouvement + carte->flank < jeu->joueurs[tour % 2]->nb_carte_deck)
      || (j > 0 && j < 4) && carte->mouvement < jeu->joueurs[tour % 2]->nb_carte_deck){
      if ((i == 0 && (carte->n_carte == jeu->plateau[i + 1][j]->n_carte || jeu->plateau[i + 1][j] == NULL))
        || (i == 4 && (carte->n_carte == jeu->plateau[i + 1][j]->n_carte || jeu->plateau[i + 1][j] == NULL))
        || (strcmp(carte->nom,"LIGHT INFANTRY") == 0 && strcmp(jeu->plateau[i + 1][j]->nom, "ELEPHANT") == 0)
        || (strcmp(carte->nom,"ELEPHANT") == 0 && strcmp(jeu->plateau[i + 1][j]->nom, "LIGHT INFANTRY") == 0)
        || strcmp(carte->nom,"ARCHERS") == 0 || strcmp(jeu->plateau[i + 1][j]->nom, "ARCHERS") == 0)
        return 0;
    }
  }
  return 1;
}

int test_rough(PTR_JEU jeu, int tour, int poscase){
  if(strcmp(jeu->plateau[2][(poscase-1)%5]->nom, "ROUGH") == 0){
    if(((poscase-1)%5 >= 1 && (poscase-1)%5 <= 3)
      && jeu->joueurs[tour%2]->nb_carte_deck < jeu->plateau[(poscase - 1) / 5 + tour % 2 * 3][(poscase - 1) % 5]->mouvement)
      return 1;
    else if(((poscase-1)%5 == 0 || (poscase-1)%5 == 4)
      && jeu->joueurs[tour%2]->nb_carte_deck > jeu->plateau[(poscase - 1) / 5 + tour % 2 * 3][(poscase - 1) % 5]->mouvement + jeu->plateau[(poscase - 1) / 5 + tour % 2 * 3][(poscase - 1) % 5]->flank)
      return 1;
  }
  return 0;
}

int choix_place(PTR_JEU jeu, int tour) {
  printf("%s, sur quelle case voulez vous poser votre troupe (0 pour quitter le placement d'unité) ?\n -> ", jeu->joueurs[tour%2]->nom);
  int poscase;
  scanf("%d", &poscase);
  while (poscase < 1 || poscase > 10) {
    if (poscase == 0)
      return poscase;
    else if (jeu->plateau[(poscase - 1) / 5 + tour % 2 * 3][(poscase - 1) % 5] != NULL || test_rough(jeu, tour, poscase)){
      printf("%s, case invalide, rechoisissez une autre case !\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%d", &poscase);
    }
  }
  return poscase;
}

int choix_carte(PTR_JEU jeu, int tour, int poscase) {
  printf("%s, quelle troupe voulez-vous poser (0 pour changer la case sur laquelle placer l'unité) ?\n -> ", jeu->joueurs[tour%2]->nom);
  int ntr;
  scanf("%d", &ntr);
  while (ntr > 9 || ntr < 1 || test_carte_valide(jeu, jeu->joueurs[tour % 2]->deck[ntr - 1], poscase, tour) == 0) {
    if (ntr == 0)
      return ntr;
    else if (jeu->joueurs[tour % 2]->deck[ntr - 1] == NULL || test_carte_valide(jeu, jeu->joueurs[tour % 2]->deck[ntr - 1], poscase, tour) == 0) {
      printf("%s, choix non valide, chagez le !\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%d", &ntr);
    }
  }
  return ntr;
}

void place_unit(PTR_JEU jeu, int tour) {

  int n_carte = 0;
  int poscase = 0;

  while (n_carte == 0) {
    n_carte = 0;
    poscase = 0;
    // demande de place
    poscase = choix_place(jeu, tour);

    // demande de carte

    if (poscase != 0)
      n_carte = choix_carte(jeu, tour, poscase);
    else
      n_carte = 10;
  }


  // placement de la carte
  if (poscase != 0 && n_carte != 0) {
    int i = (poscase - 1) / 5 + tour % 2 * 3;
    int j = (poscase - 1) % 5;
    jeu->plateau[i][j] = jeu->joueurs[tour % 2]->deck[n_carte - 1];
    jeu->joueurs[tour % 2]->deck[n_carte - 1] = NULL;

    // On eleve x carte
    int carte_a_enlever;
    if (j % 4 == 0)
      carte_a_enlever = jeu->plateau[i][j]->mouvement + jeu->plateau[i][j]->flank;
    else
      carte_a_enlever = jeu->plateau[i][j]->mouvement;

    for (int i = 0; i < carte_a_enlever; i++) {
      system("cls");
      avance_carte_trou(jeu);
      afficher_plateau(jeu, tour, 0);
      afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);
      afficher_num_carte_choix_deck(0, 9, jeu->joueurs[tour % 2]->deck);

      int rep;
      printf("%s, quelle unité voulez vous enlever ? Il vous en reste %d a enlever...\n -> ", jeu->joueurs[tour%2]->nom, carte_a_enlever - i);
      scanf("%d", &rep);
      while (rep < 1 || rep > 9 || jeu->joueurs[tour % 2]->deck[rep - 1] == NULL) {
        printf("%s, carte non valide, choisissez de nouveau une carte !\n -> ", jeu->joueurs[tour%2]->nom);
        scanf("%d", &rep);
      }
      jeu->joueurs[tour % 2]->paquet_defausse = append(jeu->joueurs[tour % 2]->paquet_defausse, jeu->joueurs[tour % 2]->deck[rep - 1]);
      jeu->joueurs[tour % 2]->deck[rep - 1] = NULL;
      nb_carte_deck(jeu->joueurs[tour%2]);
      if(i < carte_a_enlever - 1 && jeu->joueurs[tour%2]->paquet_tirage == NULL){
        jeu->joueurs[tour%2]->paquet_tirage = jeu->joueurs[tour%2]->paquet_defausse;
        jeu->joueurs[tour%2]->paquet_defausse = NULL;
        jeu->joueurs[tour%2]->shuffle += 1;
      }
    }
  }
}

void afficher_attaque(PTR_JEU jeu, int tour, int carte_attaquante){
  afficher_carte(&jeu->plateau[(carte_attaquante - 1) / 5 + tour % 2 * 3][(carte_attaquante - 1) % 5], 0, 1);
}

int choix_carte_d_attaque(PTR_JEU jeu, int tour, int col_attaque) {
  system("cls");
  afficher_plateau(jeu, tour, 1);
  printf("%s, avec quelle carte voulez-vous attaquer ? (0 pour quitter le mode attaque)\n -> ", jeu->joueurs[tour%2]->nom);
  int poscase;
  scanf("%d", &poscase);
  while (poscase < 1 || poscase > 10 || jeu->plateau[(poscase - 1) / 5 + tour % 2 * 3][(poscase - 1) % 5] == NULL || col_attaque - 1 != (poscase - 1)%5) {
    printf("Coucou\n");
    if (poscase == 0)
      return poscase;
    else if (jeu->plateau[(poscase - 1) / 5 + tour % 2 * 3][(poscase - 1) % 5] == NULL || col_attaque - 1 != (poscase - 1)%5) {
      printf("%s, case invalide, rechoisissez une autre case !\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%d", &poscase);
    }
  }
  return poscase;
}

int choix_carte_attaquer(PTR_JEU jeu, int tour, int carte_attaquante, int col_attaque) {
  system("cls");
  afficher_plateau(jeu, tour + 1, 1);
  afficher_attaque(jeu, tour, carte_attaquante);
  printf("%s, quelle troupe voulez-vous attaquer (0 pour changer la case avec laquelle attaquer) ?\n -> ", jeu->joueurs[tour%2]->nom);
  int poscase;
  scanf("%d", &poscase);
  while (poscase > 10 || poscase < 1 || (poscase - 1) % 5 != (carte_attaquante - 1) % 5 || jeu->plateau[(poscase - 1) / 5 + (tour + 1) % 2 * 3][(poscase - 1) % 5] == NULL || col_attaque - 1 != (poscase - 1)%5){

    if (poscase == 0)
      return poscase;
    else if ((poscase - 1) % 5 != (carte_attaquante - 1) % 5 || jeu->plateau[(poscase - 1) / 5 + (tour + 1) % 2 * 3][(poscase - 1) % 5] == NULL || col_attaque - 1 != (poscase - 1)%5) {
      printf("%s, case invalide, rechoisissez une autre case !\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%d", &poscase);
    }
  }
  return poscase;
}

void bonus_card(PTR_JEU jeu, int tour){
  system("cls");
  int b_card = 0;
  char rep[100];
  PTR_CARTE_JEU carte_bonus = malloc(sizeof(CARTE_JEU));
  afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);

  printf("%s, choisissez votre carte bonus !\n", jeu->joueurs[tour%2]->nom);
  while(b_card == 0){
    if(jeu->joueurs[tour%2]->nb_carte_deck != 0){
      printf("%s, voulez-vous tirer votre carte bonus dans votre deck ou la tirer depuis votre pile de carte ? (deck/pile)\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%s", rep);
      if(toupper(rep[0]) == 'D'){
        afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);
        afficher_num_carte_choix_deck(0, 9, jeu->joueurs[tour % 2]->deck);
        printf("%s, choisissez une carte dans votre deck (0 pour de nouveau choisir entre deck/pile) !\n -> ", jeu->joueurs[tour%2]->nom);
        scanf("%d", &b_card);

        while(b_card < 0 || b_card > 9){
          if(jeu->joueurs[tour%2]->deck[b_card-1] != NULL){
            printf("%s, carte invalide, rechoisissez une autre carte !\n -> ", jeu->joueurs[tour%2]->nom);
            scanf("%d", &b_card);
          }

        }
      }

      if(toupper(rep[0]) == 'P'){
        printf("%s, vous voulez vraiment tirer une carte ?\n -> ", jeu->joueurs[tour%2]->nom);
        scanf("%s", rep);
        if(toupper(rep[0]) == 'O'){
          carte_bonus = jeu->joueurs[tour%2]->paquet_tirage;
          jeu->joueurs[tour%2]->paquet_tirage = carte_bonus->suivant;
          carte_bonus->suivant = NULL;
          b_card = 10;
        }
      }

    }else{
      printf("%s, vous n'avez pas le choix de tirer une carte", jeu->joueurs[tour%2]->nom);
      carte_bonus = jeu->joueurs[tour%2]->paquet_tirage;
      jeu->joueurs[tour%2]->paquet_tirage = carte_bonus->suivant;
      carte_bonus->suivant = NULL;
      b_card = 10;
    }
  }

  if(b_card != 10){
    carte_bonus = jeu->joueurs[tour%2]->deck[b_card-1];
  }

  jeu->joueurs[tour%2]->bonus_card = carte_bonus;
  printf("Voici votre carte bonus :\n");
  afficher_carte(&jeu->joueurs[tour%2]->bonus_card, 0, 1);
}

void tuer_carte(PTR_JEU jeu, int tour, int carte_attaquante){
  int snd_carte = 0;

  int i = tour / 2 + tour%2*3;
  int j = tour % 2;

  if (tour%2 == 0)
    snd_carte = -1;
  if (tour%2 == 1)
    snd_carte = 1;

  jeu->joueurs[(tour + 1)%2]->paquet_mort_adverse = append(jeu->joueurs[(tour + 1)%2]->paquet_mort_adverse, jeu->plateau[i][j]);
  if(jeu->plateau[i + snd_carte][j] != NULL)
    jeu->joueurs[(tour + 1)%2]->paquet_mort_adverse = append(jeu->joueurs[(tour + 1)%2]->paquet_mort_adverse, jeu->plateau[i+ snd_carte][j]);

  jeu->plateau[i][j] = NULL;
  jeu->plateau[i + snd_carte][j] = NULL;

}

int demande_defense(PTR_JEU jeu, int tour){
  printf("%s, voulez vous defendre ?\n -> ", jeu->joueurs[tour%2]->nom);
  char rep[100];
  scanf("%s", rep);
  if(toupper(rep[0]) == 'O')
    return 1;
  else
    return 0;
}

void retirer_unit_defense(PTR_JEU jeu, int tour, int carte_attaquante){


  int i = (carte_attaquante - 1) / 5 + tour%2*3;
  int j = (carte_attaquante - 1)%5;

  int snd_carte = 0;

  if (tour%2 == 0)
    snd_carte = -1;
  if (tour%2 == 1)
    snd_carte = 1;

  int id = (tour+1)%2*3;
  int jd = j;

  PTR_CARTE_JEU carte1 = malloc(sizeof(CARTE_JEU));
  PTR_CARTE_JEU carte2 = malloc(sizeof(CARTE_JEU));

  carte1 = jeu->plateau[id][jd];
  carte2 = jeu->plateau[id+1][jd];

  PTR_CARTE_JEU cartes[2] = {carte1,carte2};
  int carte_retire = 0;

  while(cartes[0] != NULL || cartes[1] != NULL){
    system("cls");
    afficher_plateau(jeu, tour, 0);
    afficher_carte(&jeu->plateau[i][j], 0, 1);
    afficher_carte(cartes, 0, 2);
    afficher_num_carte_choix_deck(0,2,cartes);
    printf("%s, choissiez une carte à enlever (0 pour ne pas en enlever de carte)\n -> ", jeu->joueurs[(tour+1)%2]->nom);
    scanf("%d", &carte_retire);

    printf("%d\n", carte_retire);
    while(carte_retire < 0 || carte_retire > 2 || cartes[carte_retire - 1] == NULL || cartes[carte_retire - 1]->mouvement > jeu->plateau[i][j]->mouvement){
      if (carte_retire == 0)
        return;
      if(cartes[carte_retire - 1] == NULL || carte_retire < 1 || carte_retire > 2){
        printf("%s, cette carte n'existe pas, rechoisissez\n -> ", jeu->joueurs[tour%2]->nom);
        scanf("%d", &carte_retire);
      }
      if(cartes[carte_retire - 1]->mouvement > jeu->plateau[i][j]->mouvement){
        printf("%s, son point de mouvement est trop élevé, rechoisissez\n ->", jeu->joueurs[tour%2]->nom);
        if(cartes[2-carte_retire] == NULL){
          printf("Il n'y a plus de carte qui puisse être enlever");
          return;
        }
        scanf("%d", &carte_retire);
      }
    }

    if(carte_retire == 1){
      jeu->joueurs[tour%2]->paquet_defausse = append(jeu->joueurs[tour%2]->paquet_defausse, jeu->plateau[id][jd]);
      cartes[carte_retire - 1] = NULL;
      jeu->plateau[id][jd] = NULL;
    }

    if(carte_retire == 2){
      jeu->joueurs[tour%2]->paquet_defausse = append(jeu->joueurs[tour%2]->paquet_defausse, jeu->plateau[id+1][jd]);
      cartes[carte_retire - 1] = NULL;
      jeu->plateau[id+1][jd] = NULL;
    }
  }
}

void attack_unit(PTR_JEU jeu, int tour){
  int col_attaque = 0;
  afficher_plateau(jeu, tour, 2);
  printf("%s, Sur quelle colonne voulez-vous attaquer ?\n -> ", jeu->joueurs[tour%2]->nom);
  scanf("%d", &col_attaque);

  while(col_attaque > 5 || col_attaque < 1 || jeu->plateau[3][col_attaque-1] == NULL || jeu->plateau[1][col_attaque-1] == NULL){
    printf("%s, colonne non valide, essayez de nouveaux\n -> ", jeu->joueurs[tour%2]->nom);
    scanf("%d", &col_attaque);
  }

  int carte_attaquante = 0;
  carte_attaquante = choix_carte_d_attaque(jeu, tour, col_attaque);
  bonus_card(jeu, tour);

  printf("%s attaquera sur la colonne %d\n", jeu->joueurs[tour%2]->nom, col_attaque);

  //demande_defense(jeu, tour + 1) == 1
  retirer_unit_defense(jeu, tour, carte_attaquante);
  avance_carte_trou(jeu);

  int carte_attaquer = 0;
  carte_attaquer = choix_carte_attaquer(jeu, tour, carte_attaquante, col_attaque);

  system("cls");
  bonus_card(jeu, tour + 1);


  afficher_plateau(jeu, tour, -1);

  int Snd_carte = 0;
  if((carte_attaquante-1) / 5 == 0)
    Snd_carte = carte_attaquante + 5;
  else
    Snd_carte = carte_attaquante - 5;

  PTR_CARTE_JEU cartes_attaque[] = {jeu->joueurs[tour%2]->bonus_card,
                                   jeu->plateau[(carte_attaquante-1) / 5 + tour%2*3][(carte_attaquante-1) % 5],
                                   jeu->plateau[(Snd_carte-1) / 5 + tour%2*3][(Snd_carte-1) % 5]};

  afficher_carte(cartes_attaque, 0, 3);

  printf(" ~ %s ~\n", jeu->joueurs[tour%2]->nom);
  printf("########\n");
  printf("#CONTRE#\n");
  printf("########\n");
  printf(" ~ %s ~\n", jeu->joueurs[(tour+1)%2]->nom);

  if((carte_attaquer-1) / 5 == 0)
    Snd_carte = carte_attaquer + 5;
  else
    Snd_carte = carte_attaquer - 5;

  PTR_CARTE_JEU cartes_attaquer[] = {jeu->joueurs[(tour+1)%2]->bonus_card,
                                    jeu->plateau[(carte_attaquer-1) / 5 + (tour+1)%2*3][(carte_attaquer-1) % 5],
                                    jeu->plateau[(Snd_carte-1) / 5 + (tour+1)%2*3][(Snd_carte-1) % 5]};

  afficher_carte(cartes_attaquer, 0, 3);

  int total_point_attaquant = calcul_point_attaque(jeu, tour, tour, carte_attaquante, carte_attaquer);
  int total_point_attaquer = calcul_point_attaque(jeu, tour+1, tour, carte_attaquer, carte_attaquante);

  printf("%s a une puissance de %d et %s a une puissance de %d\n", jeu->joueurs[tour%2]->nom, total_point_attaquant, jeu->joueurs[(tour+1)%2]->nom, total_point_attaquer);

  if(total_point_attaquant > total_point_attaquer){
    printf("%s gagne en attaquant !\n", jeu->joueurs[tour%2]->nom);
    jeu->plateau[2][(carte_attaquante-1) % 5]->joueur_controle = tour%2;
    tuer_carte(jeu, tour, carte_attaquer);
    if(strcmp(jeu->plateau[(carte_attaquer-1) / 5 + (tour+1)%2*3][(carte_attaquer-1) % 5]->nom,"ELEPHANT") == 0){
      printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[(tour+1)%2]->nom);
      for(int i = 0; i < 9; i++){
        if(jeu->joueurs[(tour+1)%2]->deck[i] != NULL){
          jeu->joueurs[tour%2]->paquet_mort_adverse = append(jeu->joueurs[tour%2]->paquet_mort_adverse, jeu->joueurs[(tour+1)%2]->deck[i]);
          jeu->joueurs[(tour+1)%2]->deck[i] = NULL;
          return;
        }
      }
    }
    return;
  }

  if(total_point_attaquant < total_point_attaquer){
    printf("%s gagne en defendant !\n", jeu->joueurs[(tour+1)%2]->nom);
    jeu->plateau[2][(carte_attaquer-1) % 5]->joueur_controle = (tour+1)%2;
    tuer_carte(jeu, tour, carte_attaquante);
    if(strcmp(jeu->plateau[(carte_attaquante-1) / 5 + (tour+1)%2*3][(carte_attaquante-1) % 5]->nom,"ELEPHANT") == 0){
      printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[tour%2]->nom);
      for(int i = 0; i < 9; i++){
        if(jeu->joueurs[tour%2]->deck[i] != NULL){
          jeu->joueurs[(tour+1)%2]->paquet_mort_adverse = append(jeu->joueurs[(tour+1)%2]->paquet_mort_adverse, jeu->joueurs[tour%2]->deck[i]);
          jeu->joueurs[tour%2]->deck[i] = NULL;
          return;
        }
      }
    }
    return;
  }

  if(total_point_attaquant == total_point_attaquer){
    if(jeu->plateau[(carte_attaquante-1)/5 + tour%2*3][(carte_attaquante-1)%2] != NULL){
      if(strcmp(jeu->plateau[(carte_attaquante-1)/5 + tour%2*3][(carte_attaquante-1)%2]->nom, "PIKE") == 0)
        printf("%s gagne en attaquant grace à son PIKE !\n", jeu->joueurs[tour%2]->nom);
        jeu->plateau[2][(carte_attaquer-1) % 5]->joueur_controle = tour%2;
        tuer_carte(jeu, tour, carte_attaquer);
      if(strcmp(jeu->plateau[(carte_attaquer-1) / 5 + (tour+1)%2*3][(carte_attaquer-1) % 5]->nom,"ELEPHANT") == 0){
        printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[(tour+1)%2]->nom);
        for(int i = 0; i < 9; i++){
          if(jeu->joueurs[(tour+1)%2]->deck[i] != NULL){
            jeu->joueurs[tour%2]->paquet_mort_adverse = append(jeu->joueurs[tour%2]->paquet_mort_adverse, jeu->joueurs[(tour+1)%2]->deck[i]);
            jeu->joueurs[(tour+1)%2]->deck[i] = NULL;
            return;
          }
        }
      }
      return;
    }else if(jeu->plateau[(carte_attaquer-1)/2 + (tour + 1)%2*3][(carte_attaquer-1)%2] != NULL){
      if(strcmp(jeu->plateau[(carte_attaquer-1)/2 + (tour + 1)%2*3][(carte_attaquer-1)%2]->nom, "PIKE") == 0)
        printf("%s gagne en defendant grace à son PIKE !\n", jeu->joueurs[(tour+1)%2]->nom);
        tuer_carte(jeu, tour+1, carte_attaquante);
      if(strcmp(jeu->plateau[(carte_attaquante-1) / 5 + (tour+1)%2*3][(carte_attaquante-1) % 5]->nom,"ELEPHANT") == 0){
        printf("%s, la première carte de votre deck à été tué, RAMPAGE !\n", jeu->joueurs[tour%2]->nom);
        for(int i = 0; i < 9; i++){
          if(jeu->joueurs[tour%2]->deck[i] != NULL){
            jeu->joueurs[(tour+1)%2]->paquet_mort_adverse = append(jeu->joueurs[(tour+1)%2]->paquet_mort_adverse, jeu->joueurs[tour%2]->deck[i]);
            jeu->joueurs[tour%2]->deck[i] = NULL;
            return;
          }
        }
      }
      return;
    }
  }

  printf("Aucun joueur ne gagne\n");
  tuer_carte(jeu, tour, carte_attaquer);
  tuer_carte(jeu, tour+1, carte_attaquante);
}

void players_actions(PTR_JEU jeu, int tour) {
  afficher_plateau(jeu, tour, -1);
  afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);

  printf("%s, voulez-vous placer des unités ?\n -> ", jeu->joueurs[tour%2]->nom);
  char rep[3];
  scanf("%s", rep);

  while (toupper(rep[0]) == 'O') {
    system("cls");
    afficher_plateau(jeu, tour, 0);
    afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);
    afficher_num_carte_choix_deck(0, 9, jeu->joueurs[tour % 2]->deck);
    place_unit(jeu, tour);
    avance_carte_trou(jeu);
    nb_carte_deck(jeu->joueurs[tour%2]);
    if(jeu->joueurs[tour%2]->nb_carte_deck == 0){
      printf("Vous n'avez plus de carte dans votre deck, vous passez à la prochain étape\n");
      rep[0] = 'N';
    }
    else{
      system("cls");
      afficher_plateau(jeu, tour, 0);
      afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);
      afficher_num_carte_choix_deck(0, 9, jeu->joueurs[tour % 2]->deck);
      printf("%s, voulez-vous de nouveaux placer des unités ?\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%s", rep);
    }
  }

  printf("%s, voulez-vous attaquer ?\n -> ", jeu->joueurs[tour%2]->nom);
  scanf("%s", rep);

  while (toupper(rep[0]) == 'O') {
    system("cls");
    attack_unit(jeu, tour);
    printf("%s, voulez-vous attaquer de nouveaux ?\n -> ", jeu->joueurs[tour%2]->nom);
    scanf("%s", rep);
  }
}

void pioche(PTR_JEU jeu, int tour){
  int comm = 3;
  char choix[50];
  printf("%s, voulez-vous piocher 3 ou defausser une carte et pioche le nombre de carte egale au commandement de cette carte ?(def/pio)\n -> ", jeu->joueurs[tour%2]->nom);
  scanf("%s",choix);
  while(toupper(choix[0]) != 'D' && toupper(choix[0]) != 'P'){
    printf("%s, choix invalide !\n -> ", jeu->joueurs[tour%2]->nom);
    scanf("%s",choix);
  }
  if(toupper(choix[0]) == 'D'){
    afficher_carte(jeu->joueurs[tour%2]->deck, 0, 9);
    afficher_num_carte_choix_deck(0, 9, jeu->joueurs[tour%2]->deck);
    int cart;
    printf("%s, choisissez une carte à defausser\n -> ", jeu->joueurs[tour%2]->nom);
    scanf("%d",&cart);
    while(cart < 1 || cart > 9 || jeu->joueurs[tour%2]->deck[cart-1] == NULL){
      printf("%s, choix invalide !\n -> ", jeu->joueurs[tour%2]->nom);
      scanf("%d",&cart);
    }
    comm = jeu->joueurs[tour%2]->deck[cart-1]->commandement;
    jeu->joueurs[tour%2]->paquet_defausse = append(jeu->joueurs[tour%2]->paquet_defausse, jeu->joueurs[tour%2]->deck[cart-1]);
    jeu->joueurs[tour%2]->deck[cart-1] = NULL;
    nb_carte_deck(jeu->joueurs[tour%2]);
  }

  PTR_CARTE_JEU main[14] = {0};
  int n_main = 0;
  for(int i = 0; i < 9; i++){
    if(jeu->joueurs[tour%2]->deck[i] != NULL){
      main[n_main] = jeu->joueurs[tour%2]->deck[i];
      n_main += 1;
    }
  }

  for(int i = 0; i < comm; i++){
    main[n_main] = jeu->joueurs[tour%2]->paquet_tirage;
    jeu->joueurs[tour%2]->paquet_tirage = jeu->joueurs[tour%2]->paquet_tirage->suivant;
    n_main += 1;
  }

  int i_carte;
  for(int i = 0; i < jeu->joueurs[tour%2]->nb_carte_deck + comm - 9;i++){
    system("cls");
    afficher_carte(main, 0, 9);
    afficher_num_carte_choix_deck(0, 9, main);
    afficher_carte(main, 9, 14);
    afficher_num_carte_choix_deck(9, 5, main);
    printf("Il vous reste %d cartes à enlever\n -> ", jeu->joueurs[tour%2]->nb_carte_deck + comm - 9 - i);
    scanf("%d", &i_carte);
    while(i_carte < 1 || i_carte > 14 || main[i_carte-1] == NULL){
      printf("Choix invalide, retentez\n -> ");
      scanf("%d", &i_carte);
    }
    jeu->joueurs[tour%2]->paquet_defausse = append(jeu->joueurs[tour%2]->paquet_defausse, main[i_carte-1]);
    main[i_carte-1] = NULL;
  }

  n_main = 0;
  for(int i = 0; i < 14; i++){
    if(main[i] != NULL){
      jeu->joueurs[tour%2]->deck[n_main] = main[i];
      n_main += 1;
    }
  }

}

int somme_mort(PTR_JEU jeu, int tour){
  int tot = 0;
  PTR_CARTE_JEU tmp = jeu->joueurs[tour%2]->paquet_mort_adverse;
  while(tmp != NULL){
    tot += tmp->victory_points;
    if(tmp->suivant != NULL)
      tmp = tmp->suivant;
    else
      tmp = NULL;
  }
  return tot;
}
